fn multiply(x: i16, y: i16) -> i16 {
    x * y
}

// Implicit Conversions
pub fn implicit_conversions() {
    let x: i8 = 15;
    let y: i16 = 1000;

    // Rust will not automatically apply implicit conversions between types (unlike C++).
    // error[E0308]: mismatched types
    // println!("{x} * {y} = {}", multiply(x, y));

    println!("{x} * {y} = {}", multiply(i16::from(x), y));
    println!("{x} * {y} = {}", multiply(x.into(), y));
}
