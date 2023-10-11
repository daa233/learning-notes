// Box
pub fn box_demo() {
    // `Box` is an owned pointer to data on the heap
    // `Box` is like `std::unique_ptr` in C++, except that it's guaranteed to be not null
    let five = Box::new(5);
    println!("five: {}", *five);

    // Box with recursive data structures
    // If `Box` was not used and we attempted to embed a `List` directly into the `List`,
    // the compiler would not compute a fixed size of the struct in memory (`List` would
    // be infinite size).
    #[derive(Debug)]
    enum List<T> {
        Cons(T, Box<List<T>>),
        Nil,
    }

    let list: List<i32> = List::Cons(1, Box::new(List::Cons(2, Box::new(List::Nil))));
    println!("{list:?}");
}
