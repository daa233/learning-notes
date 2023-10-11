// Borrowing
pub fn borrowing() {
    #[derive(Debug)]
    struct Point(i32, i32);

    fn add(p1: &Point, p2: &Point) -> Point {
        // The add function borrows two points and returns a new point.
        Point(p1.0 + p2.0, p1.1 + p2.1)
    }

    let p1 = Point(3, 4);
    let p2 = Point(10, 20);
    // the caller retains onwership of the inputs
    let p3 = add(&p1, &p2);
    println!("{p1:?} + {p2:?} = {p3:?}");

    // Rust puts constraints on the ways you can borrow values:
    // - You can have one or more &T values at any given time, or
    // - You can have exactly one &mut T value.
    let mut a: i32 = 10;
    let b: &i32 = &a;
    let d: &i32 = &a;

    // error[E0502]: cannot borrow `a` as mutable because it is also borrowed as immutable
    // {
    //     let c: &mut i32 = &mut a;
    //     *c = 20;
    // }

    println!("a: {a}");
    println!("b: {b}");
    println!("d: {d}");
}
