// Five philosophers dine together at the same table. Each philosopher has
// their own plate at the table. There is a fork between each plate. The
// dish served is a kind of spaghetti which has to be eaten with two forks.
// Each philosopher can only alternately think and eat. Moreover, a
// philosopher can only eat their spaghetti when they have both a left and
// right fork. Thus two forks will only be available when their two nearest
// neighbors are thinking, not eating. After an individual philosopher
// finishes eating, they will put down both forks.

use std::sync::{mpsc, Arc, Mutex};
use std::thread;
use std::time::Duration;

struct Fork {}

struct Philosopher {
    name: String,
    // left_fork
    left_fork: Arc<Mutex<Fork>>,
    // right_fork
    right_fork: Arc<Mutex<Fork>>,
    // thoughts
    thoughts: mpsc::Sender<String>,
}

impl Philosopher {
    fn think(&self, index: u32) {
        self.thoughts
            .send(format!(
                "Eureka! {} has a new idea (No. {})!",
                &self.name, index
            ))
            .unwrap();
    }

    fn eat(&self) {
        // Pick up forks
        loop {
            let left_fork = self.left_fork.try_lock();
            let right_fork = self.right_fork.try_lock();
            match (left_fork, right_fork) {
                (Ok(_), Ok(_)) => {
                    // both forks are picked up, start eat
                    println!("{} is eating...", &self.name);
                    thread::sleep(Duration::from_millis(10));
                    // break and go out of scope to put down both forks
                    break;
                }
                _ => {
                    // release the possible single fork (lock) if not getting both forks (locks)
                    continue;
                }
            }
        }
    }
}

static PHILOSOPHERS: &[&str] = &["Socrates", "Hypatia", "Plato", "Aristotle", "Pythagoras"];

pub fn dining_philosophers() {
    let num_of_philosophers = PHILOSOPHERS.len();

    // Create forks
    let mut forks = Vec::new();
    for _ in 0..num_of_philosophers {
        forks.push(Arc::new(Mutex::new(Fork {})));
    }

    let (tx, rx) = mpsc::channel();

    // Create philosophers
    let mut philosophers = Vec::new();
    for (i, &name) in PHILOSOPHERS.iter().enumerate() {
        let left_fork_rc = forks[(i + 1) % forks.len()].clone();
        let right_fork_rc = forks[i % forks.len()].clone();
        philosophers.push(Philosopher {
            name: name.to_string(),
            left_fork: left_fork_rc,
            right_fork: right_fork_rc,
            thoughts: tx.clone(),
        });
    }

    // Make each of them think and eat 100 times
    let mut handles = Vec::new();
    let times: u32 = 100;
    for philosopher in philosophers {
        handles.push(thread::spawn(move || {
            for i in 0..times {
                philosopher.eat();
                philosopher.think(i + 1);
            }
        }));
    }

    // Drop the *original* `tx` here to close the channel.
    // All other `tx` clones will be dropped after the threads finish.
    drop(tx);

    // Output their thoughts
    for msg in rx.iter() {
        println!("{msg}");
    }
}
