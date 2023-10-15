use std::sync::mpsc; // `mpsc` stands for Multi-Producer, Single-Consumer
use std::thread;
use std::time::Duration;

pub fn channels_example() {
    // Creates a new asynchronous channel, returning the sender/receiver halves.
    // All data sent on the Sender will become available on the Receiver in
    // the same order as it was sent, and no send will block the calling thread.
    let (tx, rx) = mpsc::channel();

    tx.send(10).unwrap();
    tx.send(20).unwrap();

    println!("Received: {:?}", rx.recv());
    println!("Received: {:?}", rx.recv());

    // use `clone` to make multiple producers
    let tx2 = tx.clone();
    tx2.send(30).unwrap();
    println!("Received: {:?}", rx.recv());
}

pub fn unbounded_channels() {
    // synchronous channels means unbounded channels means, provide
    // non-blocking operations for sending and receiving values.

    let (tx, rx) = mpsc::channel();

    // `move` converts any variables captured by reference or mutable
    // reference to variables captured by value.
    // `move` is often used when threads are involved.
    thread::spawn(move || {
        let thread_id = thread::current().id();
        for i in 1..10 {
            tx.send(format!("Message {i}")).unwrap();
            println!("{thread_id:?}: send Message {i}");
            thread::sleep(Duration::from_millis(100));
        }
        println!("{thread_id:?} done");
    });
    thread::sleep(Duration::from_millis(100));

    // the main thread may receive message before the sub-thread finishes
    for msg in rx.iter() {
        println!("Main: got {msg}");
    }
}

pub fn bounded_channels() {
    // Creates a new synchronous, bounded channel. All data sent on the
    // SyncSender will become available on the Receiver in the same order
    // as it was sent.
    // This channel has an internal buffer on which messages will be queued.
    // `bound` specifies the buffer size. When the internal buffer becomes full,
    // future sends will block waiting for the buffer to open up.
    let (tx, rx) = mpsc::sync_channel(3);

    thread::spawn(move || {
        let thread_id = thread::current().id();
        for i in 1..10 {
            // Calling send will block the current thread until there is space in the
            // channel for the new message. The thread can be blocked indefinitely if
            // there is nobody who reads from the channel.
            tx.send(format!("Message {i}")).unwrap();
            println!("{thread_id:?}: send Message {i}");
        }
        println!("{thread_id:?} done");
    });
    thread::sleep(Duration::from_millis(100));

    for msg in rx.iter() {
        println!("Main: got {msg}");
    }
}
