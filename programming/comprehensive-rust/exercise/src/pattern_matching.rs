enum MyResult {
    Ok(i32),
    Err(String),
}

fn divide_in_two(n: i32) -> MyResult {
    if n % 2 == 0 {
        MyResult::Ok(n / 2)
    } else {
        MyResult::Err(format!("cannot divide {n} into two equal parts"))
    }
}

// Destructuring Enums
pub fn destructuring_enums() {
    let n = 100;
    match divide_in_two(n) {
        MyResult::Ok(half) => println!("{n} divided in two is {half}"),
        MyResult::Err(msg) => println!("sorry, an error happened: {msg}"),
    }
}

struct FooStruct {
    x: (u32, u32),
    y: u32,
}

// Destructuring Structs
#[rustfmt::skip]
pub fn destructing_structs() {
    let foo = FooStruct { x: (1, 2), y: 3 };
    match foo {
        FooStruct { x: (1, b), y }  => println!("x.0 = 1, b = {b}, y = {y}"),
        FooStruct { y: 2, x: i }    => println!("y = 2, x = {i:?}"),
        FooStruct { y, .. }         => println!("y = {y}, other fields were ignored"),
    }
}

#[rustfmt::skip]
fn inspect_array(slice: &[i32]) {
    println!("Tell me about {slice:?}");
    match slice {
        [0, y, z]   => println!("First is 0, y = {y}, and z = {z}"),
        [1, ..]     => println!("First is 1 and the rest were ignored"),
        _           => println!("All elements were ignored"),
    }
}

// Destructuring Arrays
pub fn destructing_arrays() {
    inspect_array(&[0, -2, 3]);
    inspect_array(&[0, -2, 3, 4]);
}

// Match Guards
#[rustfmt::skip]
pub fn match_guards() {
    // Use match gurads when you wish to concisely express more complex ideas than patterns alone
    let pair = (2, -2);
    println!("Tell me about {pair:?}");
    match pair {
        (x, y) if x == y        => println!("There are twins"),
        (x, y) if x + y == 0    => println!("Antimatter, kaboom"),
        (x, y) if x % 2 == 1    => println!("The first one is odd"),
        _                       => println!("No correlation..."),
    }
}
