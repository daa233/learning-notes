// https://doc.rust-lang.org/book/ch13-01-closures.html#capturing-references-or-moving-ownership

use std::thread;

pub fn closure_example() {
    let x = vec![1, 2, 3];

    let equal_to_x = move |z| z == x;

    // error[E0382]: borrow of moved value: `x`
    // println!("can't use x here: {:?}", x);

    let y = vec![1, 2, 3];

    assert!(equal_to_x(y));

    let v = vec![1, 2, 3];

    // By adding the move keyword before the closure, we force the closure to take ownership of
    // the values it’s using rather than allowing Rust to infer that it should borrow the values.
    let handle = thread::spawn(move || {
        println!("Here's a vector: {:?}", v);
    });

    handle.join().unwrap();

    // error[E0382]: use of moved value: `v`
    // drop(v);
}

pub fn moving_ownership() {
    let mut list = vec![1, 2, 3];
    println!("Before defining closure: {:?}", list);

    let only_borrows = || println!("From closure: {:?}", list);

    println!("Before calling 'only_borrows' closure: {:?}", list);
    only_borrows();
    println!("After calling 'only_borrows' closure: {:?}", list);

    let mut borrows_mutably = || list.push(7);

    // error[E0502]: cannot borrow `list` as immutable because it is also borrowed as mutable
    // println!("Before calling 'borrows_mutably' closure: {:?}", list);

    borrows_mutably();
    println!("After calling 'borrows_mutably' closure: {:?}", list);

    thread::spawn(move || println!("From thread: {:?}", list))
        .join()
        .unwrap();
}
