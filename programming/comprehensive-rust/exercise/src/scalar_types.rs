// scalar types
pub fn scalar_types() {
    // signed integers
    let x1: i8 = -10;
    let x2: i16 = 0;
    let x3: i32 = 1_000; // the same as 1000. All underscores in numbers can be left out, they are for legibility only.
    let x4: i64 = 123_i64; // the same as 123i64
    println!("signed integers: {x1} {x2} {x3} {x4}");

    // unsigned integers
    let u1: u32 = 123;
    println!("unsigned integers: {u1}");

    // floating point numbers
    let f1: f32 = 3.14;
    let f2: f64 = -10.0e20;
    println!("floating point numbers: {f1} {f2}");

    // strings
    let s1: &str = "foo";
    let s2: &str = "two\nlines";
    println!("strings: {s1} {s2}");

    // chars (32 bits wide), unicode scalar values
    // NOTE: use single-quote for the char type
    let ch: char = '∞';
    println!("chars (32 bits wide), unicode scalar values: {ch}");

    // booleans (8 bits wide)
    let b0: bool = false;
    let b1: bool = true;
    println!("booleans: {b0} vs {b1}");
}
