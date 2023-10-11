fn double(x: i32) -> i32 {
    // the value of the function body is the return value
    x + x
}

// Blocks
pub fn blocks() {
    // A block in Rust contains a sequence of expressions.
    // Each block has a value and a type, which are those of the last expression of the block
    let x = {
        let y = 10;
        println!("y: {y}");
        let z = {
            let w = { 3 + 4 };
            println!("w: {w}");
            y * w
        };
        println!("z: {z}");
        z - y
    };
    // If the last expression ends with ;, then the resulting value and type is ().
    println!("x: {x}");

    println!("double: {}", double(7));
}
