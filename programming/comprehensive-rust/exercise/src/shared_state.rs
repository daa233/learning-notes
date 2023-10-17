use std::sync::{Arc, Mutex};
use std::thread;

pub fn arc_example() {
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..10 {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap();

            *num += 1;
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Result: {}", *counter.lock().unwrap());

    let v = Arc::new(Mutex::new(vec![10, 20, 30]));
    let v2 = Arc::clone(&v);
    let handle = thread::spawn(move || {
        let mut v2 = v2.lock().unwrap();
        // dereferencing is automatic when behind a `.` so `*` is not necessary
        // refers to https://stackoverflow.com/questions/56624004/rustlings-thread-exercise-why-do-i-not-dereference-mutexstruct
        // (*v2).push(10);
        v2.push(10);
    });

    {
        let mut v = v.lock().unwrap();
        v.push(1000);
    }

    handle.join().unwrap();

    println!("v: {v:?}");
}

pub fn mutex_example() {
    let m = Mutex::new(5);
    println!("m = {:?}", m.lock().unwrap());

    {
        // if not use scope here, the MutexGuard will not go out of
        // the scope and not release the lock!
        let mut guard = m.lock().unwrap();
        *guard = 6;
    }

    println!("m = {:?}", m.lock().unwrap());
}
