// hello world
fn hello_world() {
    println!("Hello, 🌍!");
}

// the Collatz conjecture, a small example program in rust
fn collatz_conjecture() {
    let mut x: i32 = 6; // Mutable variable binding
    print!("{x}"); // Macro for printing, like printf
    while x != 1 {
        // No parenthesis around expression
        if x % 2 == 0 {
            x = x / 2;
        } else {
            x = 3 * x + 1;
        }
        print!(" -> {x}");
    }
    println!();
}

// scalar types
fn scalar_types() {
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

// compound types
fn compound_types() {
    // array assignment and access
    // [T; N] holds N (a compile-time constant) elements of the same type T
    // NOTE: the length of the array is the part of its type, which meas
    // [u8; 3] and [u8; 4] are considered two different types.
    let mut a: [i8; 10] = [42; 10];
    a[5] = 0;
    println!("array assignment and access");
    // {} gives the default output
    // {:?} gives the debug output
    // {a:#?} invokes a pretty printing format, for easier to read
    // println!("a: {}", a);    // Error: `[i8; 10]` cannot be formatted with the default formatter
    println!("a (debug): {:?}", a);     // the same as 'println!("a: {a:?}");'
    println!("a (pretty printing debug): {a:#?}");

    let t: (i8, bool) = (7, true);
    println!("tuple: ({}, {})", t.0, t.1);
    println!("tuple (debug): {:?}", t);

    let empty_t: () = ();
    println!("emplty tuple (unit type): {:?}", empty_t);
}

// References
fn references() {
    let mut x: i32 = 10;
    println!("original x: {x}");
    
    let ref_x: &mut i32 = &mut x;

    // Error: error[E0502]: cannot borrow `x` as immutable because it is also borrowed as mutable
    // println!("original x: {x}");

    *ref_x = 7;
    println!("ref_x.count_ones(): {}", ref_x.count_ones());
    println!("after modify by reference x: {x}");
}

fn main() {
    // Program entry point
    println!("\n# Hello World");
    hello_world();

    println!("\n# Small Example: the Collatz conjecture");
    collatz_conjecture();

    println!("\n# Scalar Types");
    scalar_types();

    println!("\n# Compound Types");
    compound_types();

    println!("\n# References");
    references();
}
