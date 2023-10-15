// Rc
pub fn rc() {
    use std::rc::Rc;

    // `Rc` is a reference-counted shared pointer. It is like `std::shared_ptr` in C++.
    // Use this when you need to refer to the same data from multiple places
    let mut a = Rc::new(10);
    let mut b = Rc::clone(&a);

    println!("a: {a}");
    println!("b: {b}");
}
