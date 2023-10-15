use std::error::Error;
use std::thread;
use std::time::Duration;

pub fn threads_example() {
    let handle = thread::spawn(|| {
        for i in 1..10 {
            println!("Count in thread: {i}!");
            thread::sleep(Duration::from_millis(5));
        }
    });

    for i in 1..5 {
        println!("Main thread: {i}");
        thread::sleep(Duration::from_millis(5));
    }

    // wait for the sub-thread to finish
    handle.join().expect("Error in the sub thread!");
}

pub fn scoped_threads() {
    let s = String::from("Hello");

    // The scope guarantees all threads will be joined at the end of the scope.
    thread::scope(|scope| {
        scope.spawn(|| {
            println!("In thread 0: Length: {}", s.len());
        });
        scope.spawn(|| {
            for i in 1..10 {
                println!("Count in thread 1: {i}!");
                thread::sleep(Duration::from_millis(5));
            }
        });
        scope.spawn(|| {
            for i in 1..4 {
                println!("Count in thread 2: {i}!");
                thread::sleep(Duration::from_millis(5));
            }
        });
    });

    for i in 1..5 {
        println!("Main thread: {i}");
        thread::sleep(Duration::from_millis(5));
    }
}
