// Variables
pub fn variables() {
    // Rust provides type safety via static typing.
    // Variable bindings are immutable by default
    let x: i32 = 10;
    println!("x: {x}");

    // error[E0384]: cannot assign twice to immutable variable `x`
    // x = 20;
    // println!("x: {x}");
}
