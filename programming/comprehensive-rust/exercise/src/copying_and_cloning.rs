// Copying and Cloning
pub fn copying_and_cloning() {
    // Certian types (which implement the 'Copy' trait) are copied by default.
    let x = 42;
    let y = x;
    println!("x: {x}");
    println!("y: {y}");

    // opt-in your own types to use copy semantics
    #[derive(Copy, Clone, Debug)]
    struct Point(i32, i32);

    let p1 = Point(3, 4);
    let p2 = p1;
    println!("p1: {p1:?}");
    println!("p2: {p2:?}");
}
