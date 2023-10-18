// Create a multi-threaded link checker.
// It should start at a webpage and check that links on the page are valid.
// It should recursively check other pages on the same domain and keep doing
// this until all pages have been validated.
//
// Tasks
// - Use threads to check the links in parallel: send the URLs to be checked
//   to a channel and let a few threads check the URLs in parallel.
// - Extend this to recursively extract links from all pages on the
//   www.google.org domain. Put an upper limit of 100 pages or so so that you
//   don’t end up being blocked by the site.
use reqwest::{blocking::Client, Url};
use scraper::{Html, Selector};
use std::collections::{HashMap, HashSet};
use std::sync::mpsc::{Receiver, Sender};
use std::sync::{mpsc, Arc, Mutex};
use std::thread;
use thiserror::Error;

#[derive(Error, Debug)]
enum Error {
    #[error("request error: {0}")]
    ReqwestError(#[from] reqwest::Error),
    #[error("bad http response: {0}")]
    BadResponse(String),
}

#[derive(Debug)]
struct CrawlCommand {
    url: Url,
    extract_links: bool,
}

#[derive(Debug)]
struct CrawlState {
    domain: String,
    visited: HashMap<String, bool>,
}

impl CrawlState {
    fn new(url: &Url) -> CrawlState {
        CrawlState {
            domain: url.as_str().to_string(),
            visited: HashMap::new(),
        }
    }

    fn should_extract_links(&self, url: &Url) -> bool {
        match url.domain() {
            Some(url_domain) => url_domain == self.domain,
            None => false,
        }
    }

    fn visit(&mut self, url: &Url, valid: bool) {
        if self.check_visited(&url) {
            println!(
                "Warning: url {:#?} already visited before, now update its state",
                url.as_str()
            );
        }
        self.visited.insert(url.as_str().to_string(), valid);
    }

    fn check_visited(&self, url: &Url) -> bool {
        self.visited.contains_key(url.as_str())
    }

    fn get_urls(&self, valid: bool) -> Vec<String> {
        let mut urls = Vec::new();
        for (k, v) in self.visited.clone() {
            if v == valid {
                urls.push(k);
            }
        }
        urls
    }
}

fn visit_page(client: &Client, command: &CrawlCommand) -> Result<Vec<Url>, Error> {
    println!("Checking {:#}", command.url);
    let response = client.get(command.url.clone()).send()?;
    if !response.status().is_success() {
        return Err(Error::BadResponse(response.status().to_string()));
    }

    let mut link_urls = Vec::new();
    if !command.extract_links {
        return Ok(link_urls);
    }

    let base_url = response.url().to_owned();
    let body_text = response.text()?;
    let document = Html::parse_document(&body_text);

    let selector = Selector::parse("a").unwrap();
    let href_values = document
        .select(&selector)
        .filter_map(|element| element.value().attr("href"));
    for href in href_values {
        match base_url.join(href) {
            Ok(link_url) => {
                link_urls.push(link_url);
            }
            Err(err) => {
                println!("On {base_url:#}: ignored unparsable {href:?}: {err}");
            }
        }
    }
    Ok(link_urls)
}

type CrawlResult = Result<(Url, Vec<Url>), (Url, Error)>;
fn spawn_crawler_threads(
    command_receiver: Receiver<CrawlCommand>,
    result_sender: Sender<CrawlResult>,
    worker_num: u32,
) {
    let command_receiver = Arc::new(Mutex::new(command_receiver));
    for _ in 0..worker_num {
        let client = Client::new();
        let command_receiver = command_receiver.clone();
        let result_sender = result_sender.clone();
        thread::spawn(move || {
            loop {
                let crawl_command_result = {
                    let receiver_guard = command_receiver.lock().unwrap();
                    receiver_guard.recv()
                };
                // check if crawl_command_result is valid and assign the Ok's value to crawl_command
                let Ok(crawl_command) = crawl_command_result else {
                    break;
                };
                let crawl_result = match visit_page(&client, &crawl_command) {
                    Ok(links) => Ok((crawl_command.url, links)),
                    Err(err) => Err((crawl_command.url, err)),
                };
                if let Err(msg) = result_sender.send(crawl_result) {
                    println!("Error: when send the crawl result, {:?}", msg);
                }
            }
        });
    }
}

fn control_flow(
    start_url: Url,
    crawl_state: &mut CrawlState,
    command_sender: Sender<CrawlCommand>,
    result_receiver: Receiver<CrawlResult>,
    max_pages: u32,
) {
    assert_eq!(crawl_state.check_visited(&start_url), false);

    let crawl_command = CrawlCommand {
        url: start_url.clone(),
        extract_links: true,
    };

    if let Err(msg) = command_sender.send(crawl_command) {
        panic!("Error: when send the start crawl command, {:?}", msg);
    }

    let mut total_num: u32 = 0;
    let mut pending_num: u32 = 1;

    let mut bad_urls = Vec::new();
    loop {
        let recv_reuslt = result_receiver.recv();
        match recv_reuslt {
            Ok(crawl_result) => {
                match crawl_result {
                    Ok((url, links)) => {
                        // the current crawl url is valid
                        total_num += 1;
                        pending_num -= 1;
                        crawl_state.visit(&url, true);

                        // for the new links, check recursively
                        let mut hash_set = HashSet::new();
                        for link in links {
                            // remove the already visited urls
                            if crawl_state.check_visited(&link) {
                                continue;
                            } else if hash_set.contains(link.as_str()) {
                                // remove the repeat links in this page
                                continue;
                            } else {
                                hash_set.insert(link.as_str().to_string());
                            }
                            let should_extract_links_flag = crawl_state.should_extract_links(&link);
                            let crawl_command = CrawlCommand {
                                url: link,
                                extract_links: should_extract_links_flag,
                            };
                            if let Err(msg) = command_sender.send(crawl_command) {
                                println!("Error: when send crawl command, {:?}", msg);
                            } else {
                                pending_num += 1;
                            }
                        }
                    }
                    Err((url, _err)) => {
                        crawl_state.visit(&url, false);
                        bad_urls.push(url);
                    }
                }
            }
            Err(msg) => {
                println!("Error: when get the crawl result from receiver, {:?}", msg)
            }
        }

        // exit
        if pending_num == 0 {
            println!(
                "All pages on {:?} have been visited, exit.",
                start_url.as_str()
            );
            break;
        } else if total_num >= max_pages {
            println!(
                "Already crawled {:?} pages which reachs the max limit, exit.",
                total_num
            );
            break;
        }
    }
}

fn check_links(
    start_url: Url,
    command_sender: Sender<CrawlCommand>,
    command_receiver: Receiver<CrawlCommand>,
    result_sender: Sender<CrawlResult>,
    result_receiver: Receiver<CrawlResult>,
    crawl_worker_num: u32,
    max_pages: u32,
) -> (Vec<String>, Vec<String>) {
    let mut crawl_state = CrawlState::new(&start_url);
    spawn_crawler_threads(command_receiver, result_sender, crawl_worker_num);
    control_flow(
        start_url,
        &mut crawl_state,
        command_sender,
        result_receiver,
        max_pages,
    );
    let valid_urls = crawl_state.get_urls(true);
    let invalid_urls = crawl_state.get_urls(false);
    (valid_urls, invalid_urls)
}

fn main() {
    let start_url = Url::parse("https://www.google.org").unwrap();
    let crawl_worker_num = 5;
    let max_pages = 100;

    let (result_sender, result_receiver) = mpsc::channel();
    let (command_sender, command_receiver) = mpsc::channel();

    let (valid_urls, invalid_urls) = check_links(
        start_url,
        command_sender,
        command_receiver,
        result_sender,
        result_receiver,
        crawl_worker_num,
        max_pages,
    );

    println!("\n# Result:");
    println!("Valid urls ({}): {:#?}", valid_urls.len(), valid_urls);
    println!("Invalid urls ({}): {:#?}", invalid_urls.len(), invalid_urls);
}
