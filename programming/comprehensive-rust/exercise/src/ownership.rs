// Ownership
pub fn ownership() {
    struct Point(i32, i32);

    {
        let p = Point(3, 4);
        println!("x: {}", p.0);
    }

    // it is an error to use a variable outside its scope
    // error[E0425]: cannot find value `p` in this scope
    // println!("y: {}", p.1);
}
