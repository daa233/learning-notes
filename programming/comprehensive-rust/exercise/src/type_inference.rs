fn takes_u32(x: u32) {
    println!("u32: {x}");
}

fn takes_i8(y: i8) {
    println!("i8: {y}");
}

// Type Inference
pub fn type_inference() {
    // Here the variables are not dynamic type, the compiler will inference the type
    let x = 10;
    let y = 20;

    // Rust will look at how the variable is used to determine the type
    takes_u32(x);
    takes_i8(y);

    let mut v = Vec::new();
    v.push((10, false));
    v.push((20, true));
    println!("v: {v:?}");

    // using _ as a placeholder to tell the compiler copy into a certain generic container
    // without explicitly specifying the container type.
    let vv = v.iter().collect::<std::collections::HashSet<_>>();
    println!("vv: {vv:?}");
}
