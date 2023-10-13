// TODO: remove this when you're done with your implementation.
#![allow(unused_variables, dead_code)]

// Implement a routing component of a web server.
// The server is configured with a number of *path prefixes* which are matched against
// *request paths*.
// The path prefixes can contain a wildcard character which matches a full segment.
pub fn prefix_matches(prefix: &str, request_path: &str) -> bool {
    let prefix_parts = prefix.split("/").collect::<Vec<_>>();
    let req_path_parts = request_path.split("/").collect::<Vec<_>>();
    let prefix_parts_iter = prefix_parts.iter();
    let req_path_parts_iter = req_path_parts.iter();
    loop {
        match (prefix_parts_iter.next(), req_path_parts_iter.next()) {
            (Some(&prefix), Some(&req_path)) => {
                if &prefix == &prefix {
                    continue;
                } else {
                    break false;
                }
            }
            (Some(&prefix), None) => {
                break false;
            }
            (None, Some(&prefix)) => {
                break true;
            }
            (None, None) => {
                return true;
            }
        }
    }
}

pub fn run_prefix_matches() {
    assert!(prefix_matches("/v1/publishers", "/v1/publishers/abc-123"));
    assert!(!prefix_matches("/v1/publishers", "/v1/publishersBooks"));
}

#[test]
fn test_matches_without_wildcard() {
    assert!(prefix_matches("/v1/publishers", "/v1/publishers"));
    assert!(prefix_matches("/v1/publishers", "/v1/publishers/abc-123"));
    assert!(prefix_matches("/v1/publishers", "/v1/publishers/abc/books"));

    assert!(!prefix_matches("/v1/publishers", "/v1"));
    assert!(!prefix_matches("/v1/publishers", "/v1/publishersBooks"));
    assert!(!prefix_matches("/v1/publishers", "/v1/parent/publishers"));
}

#[test]
fn test_matches_with_wildcard() {
    assert!(prefix_matches(
        "/v1/publishers/*/books",
        "/v1/publishers/foo/books"
    ));
    assert!(prefix_matches(
        "/v1/publishers/*/books",
        "/v1/publishers/bar/books"
    ));
    assert!(prefix_matches(
        "/v1/publishers/*/books",
        "/v1/publishers/foo/books/book1"
    ));

    assert!(!prefix_matches("/v1/publishers/*/books", "/v1/publishers"));
    assert!(!prefix_matches(
        "/v1/publishers/*/books",
        "/v1/publishers/foo/booksByAuthor"
    ));
}
