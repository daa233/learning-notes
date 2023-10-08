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
    println!("a (debug): {:?}", a); // the same as 'println!("a: {a:?}");'
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

    // dangling references
    /* Error: error[E0597]: `y` does not live long enough
    let ref_y: &i32;
    {
        let y: i32 = 10;
        ref_y = &y;
    }
    println!("ref_y: {ref_y}");
    */
}

// Slices
fn slices() {
    let mut a: [i32; 6] = [10, 20, 30, 40, 50, 60];
    a[2] = 35;
    println!("a: {a:?}");

    let s: &[i32] = &a[2..4];

    // error[E0506]: cannot assign to `a[_]` because it is borrowed
    // a[3] = 45;

    println!("s: {s:?}");
}

// String
fn string() {
    // &str: an immutable reference to a string slice
    let s1: &str = "World";
    println!("s1: {s1}");

    // String: a mutable string buffer
    let mut s2: String = String::from("Hello ");
    println!("s2: {s2}");
    s2.push_str(s1);
    println!("s2: {s2}");

    let s3: &str = &s2[6..];
    println!("s3: {s3}");
}

// Functions
fn functions() {
    print_fizzbuzz_to(5);
}

// All language items in Rust can be documented using special /// syntax.
/// Determine whether the first argument is divisible by the second argument.
///
/// If the second argument is zero, the result is false.
///
/// # Example
/// ```
/// assert!(is_divisible_by(42, 2));
/// ```
fn is_divisible(n: u32, divisor: u32) -> bool {
    if divisor == 0 {
        return false;
    }

    // The last expression in a function body (or any block) becomes the return value.
    // Simply omit the ; at the end of the expression.
    n % divisor == 0
}

fn fizzbuzz(n: u32) -> String {
    let fizz = if is_divisible(n, 3) { "fizz" } else { "" };
    let buzz = if is_divisible(n, 5) { "buzz" } else { "" };
    if fizz.is_empty() && buzz.is_empty() {
        return format!("{n}");
    }
    format!("{fizz}{buzz}")
}

fn print_fizzbuzz_to(n: u32) {
    // Some functions have no return value, and return the ‘unit type’, ().
    // The compiler will infer this if the -> () return type is omitted.

    // the i loops in range [1, n)
    for i in 1..n {
        println!("{}", fizzbuzz(i));
    }

    // the i loops in range [1, n]
    for i in 1..=n {
        println!("{}", fizzbuzz(i));
    }
}

struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    // Methods are functions associated with a type.
    // The self argument of a method is an instance of the type it is associated with
    fn area(&self) -> u32 {
        self.width * self.height
    }

    fn inc_width(&mut self, delta: u32) {
        self.width += delta;
    }

    // custom constructor
    fn new(width: u32, height: u32) -> Rectangle {
        Rectangle { width, height }
    }

    // custom constructor
    fn square(width: u32) -> Rectangle {
        let height: u32 = width;
        Rectangle { width, height }
    }
}

fn methods() {
    let mut rect = Rectangle { width: 10, height: 5 };
    println!("old area: {}", rect.area());
    rect.inc_width(5);
    println!("new area: {}", rect.area());

    let rect2 = Rectangle::new(5, 4);
    println!("rect2 area: {}", rect2.area());

    let square = Rectangle::square(4);
    println!("square area: {}", square.area());
}

// Fuction overloading
// Overloading is not supported:
//   - Each function has a single implementation:
//     - Always takes a fixed number of parameters.
//     - Always takes a single set of parameter types.
//   - Default values are not supported:
//     - All call sites have the same number of arguments.
//     - Macros are sometimes used as an alternative.
// Function parameters can be generic.

fn pick_one<T>(a: T, b: T) -> T {
    if std::process::id() % 2 == 0 { a } else { b }
}
fn overloading() {
    println!("coin toss: {}", pick_one("heads", "tails"));
    println!("cash prize: {}", pick_one(500, 1000));
}

fn multiply(x: i16, y: i16) -> i16 {
    x * y
}

fn implicit_conversions() {
    let x: i8 = 15;
    let y: i16 = 1000;

    // Rust will not automatically apply implicit conversions between types (unlike C++).
    // error[E0308]: mismatched types
    // println!("{x} * {y} = {}", multiply(x, y));

    println!("{x} * {y} = {}", multiply(i16::from(x), y));
    println!("{x} * {y} = {}", multiply(x.into(), y));
}

fn array_and_for_loops() {
    let array = [10, 20, 30];
    println!("array: {array:?}");

    print!("Iterating over array:");
    for n in &array {
        print!(" {n}");
    }
    println!();

    print!("Iterating over range:");
    for i in 0..3 {
        print!(" {}", array[i]);
    }
    println!();
}

fn transpose(matrix: [[i32; 3]; 3]) -> [[i32; 3]; 3] {
    let mut transposed: [[i32; 3]; 3] = [[0; 3]; 3];
    for i in 0..matrix.len() {
        for j in 0..matrix[i].len() {
            transposed[i][j] = matrix[j][i];
        }
    }
    transposed
}

fn pretty_print(matrix: &[[i32; 3]; 3]) {
    print!("[");
    for i in 0..matrix.len() {
        if i != 0 {
            print!(" ");
        }
        print!("{:?}", matrix[i]);
        if i != matrix.len() - 1 {
            print!("\n");
        }
    }
    println!("]")
}

fn print_matrix() {
    let matrix = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9],
    ];

    println!("matrix:");
    pretty_print(&matrix);

    let transposed = transpose(matrix);
    println!("transposed:");
    pretty_print(&transposed);
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

    println!("\n# Slices");
    slices();

    println!("\n# String vs str");
    string();

    println!("\n# Functions");
    functions();

    println!("\n# Methods");
    methods();

    println!("\n# Overloading");
    overloading();

    println!("\n# Implicit Conversions");
    implicit_conversions();

    println!("\n# Arrays and for Loops");
    array_and_for_loops();
    print_matrix();
}
