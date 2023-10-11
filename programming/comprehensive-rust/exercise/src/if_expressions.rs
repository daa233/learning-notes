// if expressions
pub fn if_expressions() {
    let mut x = 10;

    // use if statements
    if x % 2 == 0 {
        x = x / 2;
    } else {
        x = 3 * x + 1;
    }
    println!("x = {x}");

    // use if as an expression
    // the last expression of each block becomes the value of the if expression
    x = 10;
    x = if x % 2 == 0 {
        x / 2 // NOTE: there must NOT be a ';' here to return the value
    } else {
        3 * x + 1
    }; // NOTE: there must be a ';' here
    println!("x = {x}");
}
