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
    // A slice gives you a view into a larger collection
    let mut a: [i32; 6] = [10, 20, 30, 40, 50, 60];
    a[2] = 35;
    println!("a: {a:?}");

    // NOTE: the type of s (&[i32]) no longer mentions the array length.
    // This allows us to perform computation on slices of different sizes.
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

fn double(x: i32) -> i32 {
    // the value of the function body is the return value
    x + x
}

// Blocks
fn blocks() {
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

// if expressions
fn if_expressions() {
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

// for loops
fn for_loops() {
    let v = vec![10, 20, 30];

    // the same as 'for x in v.into_iter()'
    for x in v {
        println!("x: {x}");
    }

    let mut mut_v = vec![10, 20, 30];
    for x in mut_v.iter_mut() {
        // the type of x here is '&mut {integer}'
        *x += 5;
        println!("x: {x}");
    }
    println!("mut_v: {:?}", mut_v);

    // (0..10) is a range that implements an Iterator trait
    for i in (0..10).step_by(2) {
        println!("i: {i}");
    }
}

// while loops
fn while_loops() {
    let mut x = 10;
    print!("x: {x}");
    while x != 1 {
        x = if x % 2 == 0 { x / 2 } else { 3 * x + 1 };
        print!(" -> {x}");
    }
    println!();
}

// break and continue
fn break_and_continue() {
    let x: u32 = 5;
    let mut i: u32 = 0;
    while i < 10000 {
        if i == 0 {
            i += 1;
            // use continue to immediately start the next iteration
            continue;
        }
        println!("i: {i}");
        if i >= x {
            // use break to exit a loop early
            break;
        }
        i += 1;
    }
}

// loop expressions
fn loop_expressions() {
    let mut x = 10;
    print!("x: {x}");
    // loop == while true, which creates an endless loop
    // you must either break or return to stop the loop
    loop {
        x = if x % 2 == 0 { x / 2 } else { 3 * x + 1 };
        print!(" -> {x}");
        if x == 1 {
            break;
        }
    }
    println!();

    // returning from loops
    let mut counter = 0;
    let result = loop {
        counter += 1;

        if counter == 10 {
            // put the value after break to return by the loop expression
            break counter * 2;
        }
    };
    println!("result of loop: {result}");
}

// Variables
fn variables() {
    // Rust provides type safety via static typing.
    // Variable bindings are immutable by default
    let x: i32 = 10;
    println!("x: {x}");

    // error[E0384]: cannot assign twice to immutable variable `x`
    // x = 20;
    // println!("x: {x}");
}

fn takes_u32(x: u32) {
    println!("u32: {x}");
}

fn takes_i8(y: i8) {
    println!("i8: {y}");
}

// Type Inference
fn type_inference() {
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

// Constant Variables
// Constant variables are evaluated at compile time and their values are inlined wherever they are used
const DIGEST_SIZE: usize = 3;
// 'Some' means some value of type T
const ZERO: Option<u8> = Some(42);
fn compute_digest(text: &str) -> [u8; DIGEST_SIZE] {
    // 'unwrap_or' returns the contained Some value or a provided default.
    let mut digest = [ZERO.unwrap_or(0); DIGEST_SIZE];
    for (idx, &b) in text.as_bytes().iter().enumerate() {
        // 'wrapping_add' computes 'self + rhs'
        digest[idx % DIGEST_SIZE] = digest[idx % DIGEST_SIZE].wrapping_add(b);
    }
    digest
}

fn const_variables() {
    let s: &str = "Hello";
    let digest = compute_digest(s);
    println!("digest: {digest:?}");
    println!("s.as_bytes(): {:?}", s.as_bytes());
}

// Static Varaibles
// Static variables will live during the whole execution of the program, and therefore will not move
static BANNER: &str = "Welcome to RustOS 3.14";
fn static_variables() {
    println!("{BANNER}");
}

// Scopes and Shadowing
fn scopes_and_shadowing() {
    let a = 10;
    println!("before: {a}");

    {
        let a = "hello";
        println!("inner scope: {a}");

        let a = true;
        println!("shadowed in inner scope: {a}");
    }

    // after shadowing, both variable's memory location exist at the same time
    println!("after: {a}");

    let a = 1;
    let b = &a;
    let a = a + 1;
    println!("{a} {b}");
    // 2 1
}

// Enums
#[derive(Debug)]
enum CoinFlip {
    Heads,
    Tails,
}

fn enums() {
    println!("You got: {:?}", pick_one(CoinFlip::Heads, CoinFlip::Tails));
}

#[rustfmt::skip]
// define richer enums where the variants carry data
enum WebEvent {
    PageLoad,                   // Variant without payload
    KeyPress(char),             // Tuple struct variant
    Click { x: i64, y: i64 },   // Full struct variant
}

#[rustfmt::skip]
fn inspect(event: WebEvent) {
    // use the match statement to extract the data from each variant
    match event {
        WebEvent::PageLoad          => println!("page loaded"),
        WebEvent::KeyPress(c)       => println!("pressed '{c}'"),
        WebEvent::Click { x, y }    => println!("clicked at x={x}, y={y}"),
    }
}

// Variant Payloads
fn variant_payloads() {
    let load = WebEvent::PageLoad;
    let press = WebEvent::KeyPress('x');
    let click = WebEvent::Click { x: 20, y: 80 };

    inspect(load);
    inspect(press);
    inspect(click);
}

use std::any::type_name;
use std::mem::{ align_of, size_of };

fn dbg_size<T>() {
    println!(
        "{}: size {} bytes, align: {} bytes",
        type_name::<T>(),
        size_of::<T>(),
        align_of::<T>()
    );
}

enum Foo {
    A,
    B,
}

enum Bar {
    A, // 0
    B = 10000, // e.g., you can control the discriminant if needed
    C, // 10001
}

// Enum Sizes
fn enum_sizes() {
    // Rust enums are packed tightly, taking constraints due to alignment into account
    // You can control the discriminant if needed.
    dbg_size::<Foo>(); // size 1 bytes, align: 1 bytes
    println!("Foo::A: {}", Foo::A as u32);
    println!("Foo::B: {}", Foo::B as u32);
    dbg_size::<Bar>(); // size 2 bytes, align: 2 bytes
    println!("Bar::A: {}", Bar::A as u32);
    println!("Bar::B: {}", Bar::B as u32);
    println!("Bar::C: {}", Bar::C as u32);

    dbg_size::<bool>(); // size 1 bytes, align: 1 bytes
    dbg_size::<Option<bool>>(); // size 1 bytes, align: 1 bytes
    dbg_size::<&i32>(); // size 8 bytes, align: 8 bytes
    dbg_size::<Option<&i32>>(); // size 8 bytes, align: 8 bytes
}

// if let expressions
fn if_let_expressions() {
    // The if let expression lets you execute different code depending on
    // whether a value matches a pattern
    let arg = std::env::args().next();
    if let Some(value) = arg {
        println!("Program name: {value}");
    } else {
        println!("Missing name?");
    }

    let test: Option<std::env::Args> = None;
    if let Some(value) = test {
        println!("value: {value:?}");
    } else {
        println!("the value is None");
    }

    let dish = ("Ham", "Eggs");

    // this body will be skipped because the pattern is refuted
    if let ("Bacon", b) = dish {
        println!("Bacon is served with {}", b);
    } else {
        // This block is evaluated instead.
        println!("No bacon will be served");
    }

    // this body will execute
    if let ("Ham", b) = dish {
        println!("Ham is served with {}", b);
    }

    if let _ = 5 {
        println!("Irrefutable patterns are always true");
    }
}

// while let expressions
fn while_let_expressions() {
    let v = vec![10, 20, 30];
    let mut iter = v.into_iter();

    // the iterator returned by v.into_iter() will return a Option<i32> on
    // every call to next().
    // It returns Some(x) until it is done, after which it will return None.
    while let Some(x) = iter.next() {
        println!("x: {x}");
    }
}

// match expressions
fn match_expressions() {
    // The match keyword is used to match a value against one or more patterns
    // similarly to 'switch' in C and C++
    match std::env::args().next().as_deref() {
        Some("cat") => println!("Will do cat things"),
        Some("ls") => println!("Will ls some files"),
        Some("mv") => println!("Let's move some files"),
        Some("rm") => println!("Uh, dangerous!"),
        None => println!("Hmm, no program name?"),
        // The _ pattern is a wildcard pattern which matches any value.
        _ => println!("Unknown program name!"),
    }

    let input = 'x';
    match input {
        'q' => println!("Quitting"),
        'a' | 's' | 'w' | 'd' => println!("Moving around"),
        '0'..='9' => println!("Number input"),
        _ => println!("Something else"),
    }
}

enum Result {
    Ok(i32),
    Err(String),
}

fn divide_in_two(n: i32) -> Result {
    if n % 2 == 0 {
        Result::Ok(n / 2)
    } else {
        Result::Err(format!("cannot divide {n} into two equal parts"))
    }
}

// Destructuring Enums
fn destructuring_enums() {
    let n = 100;
    match divide_in_two(n) {
        Result::Ok(half) => println!("{n} divided in two is {half}"),
        Result::Err(msg) => println!("sorry, an error happened: {msg}"),
    }
}

struct FooStruct {
    x: (u32, u32),
    y: u32,
}

// Destructuring Structs
#[rustfmt::skip]
fn destructing_structs() {
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
fn destructing_arrays() {
    inspect_array(&[0, -2, 3]);
    inspect_array(&[0, -2, 3, 4]);
}

// Match Guards
#[rustfmt::skip]
fn match_guards() {
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

// Luhn Algorithm
pub fn luhn(cc_number: &str) -> bool {
    let mut sum: u32 = 0;
    let mut count: u32 = 0;
    for c in cc_number.chars().rev() {
        if c == ' ' {
            continue;
        } else if !c.is_digit(10) {
            return false;
        }
        count += 1;
        let addend: u32;
        let digit = c.to_string().parse::<u32>().unwrap();
        if count % 2 == 0 {
            let doubled = digit * 2;
            if doubled > 9 {
                addend = 1 + (doubled % 10);
            } else {
                addend = doubled;
            }
        } else {
            addend = digit;
        }
        sum += addend;
    }
    count >= 2 && sum % 10 == 0
}

#[test]
fn test_non_digit_cc_number() {
    assert!(!luhn("foo"));
    assert!(!luhn("foo 0 0"));
}

#[test]
fn test_empty_cc_number() {
    assert!(!luhn(""));
    assert!(!luhn(" "));
    assert!(!luhn("  "));
    assert!(!luhn("    "));
}

#[test]
fn test_single_digit_cc_number() {
    assert!(!luhn("0"));
}

#[test]
fn test_two_digit_cc_number() {
    assert!(luhn(" 0 0 "));
}

#[test]
fn test_valid_cc_number() {
    assert!(luhn("4263 9826 4026 9299"));
    assert!(luhn("4539 3195 0343 6467"));
    assert!(luhn("7992 7398 713"));
}

#[test]
fn test_invalid_cc_number() {
    assert!(!luhn("4223 9826 4026 9299"));
    assert!(!luhn("4539 3195 0343 6476"));
    assert!(!luhn("8273 1232 7352 0569"));
}

fn run_luhn_algirithm() {
    let cc_number_array = ["4263 9826 4026 9299", "4223 9826 4026 9299"];
    for cc_number in &cc_number_array {
        let valid_or_not: &str = if luhn(cc_number) { "valid" } else { "invalid" };
        println!("The credit card number '{cc_number}' is {valid_or_not}");
    }
}

/// An operation to perform on two subexpressions.
#[derive(Debug)]
enum Operation {
    Add,
    Sub,
    Mul,
    Div,
}

/// An expression, in tree form.
#[derive(Debug)]
enum Expression {
    /// An operation on two subexpressions.
    Op {
        op: Operation,
        // the Box type here is a smart pointer, unboxed it by '*boxed_expr' when use it
        left: Box<Expression>,
        right: Box<Expression>,
    },

    /// A literal value
    Value(i64),
}

/// The result of evaluating an expression.
#[derive(Debug, PartialEq, Eq)]
enum Res {
    /// Evaluation was successful, with the given result.
    Ok(i64),
    /// Evaluation failed, with the given error message.
    Err(String),
}
// Allow `Ok` and `Err` as shorthands for `Res::Ok` and `Res::Err`.
use Res::{ Err, Ok };

/// A simple recursive evaluator for arithmetic expressions.
fn eval(e: Expression) -> Res {
    match e {
        // NOTE: using destructing here
        Expression::Op { op, left, right } => {
            let left = match eval(*left) {
                Ok(v) => v,
                Err(msg) => {
                    return Err(msg);
                }
            };
            let right = match eval(*right) {
                Ok(v) => v,
                Err(msg) => {
                    return Err(msg);
                }
            };
            let res = match op {
                Operation::Add => left + right,
                Operation::Sub => left - right,
                Operation::Mul => left * right,
                Operation::Div => {
                    if right == 0 {
                        return Err(String::from("division by zero"));
                    } else {
                        left / right
                    }
                }
            };
            Ok(res)
        }
        Expression::Value(value) => Ok(value),
    }
}

fn run_eval() {
    let res = eval(Expression::Op {
        op: Operation::Add,
        left: Box::new(Expression::Value(10)),
        right: Box::new(Expression::Value(20)),
    });
    match res {
        Ok(value) => {
            println!("eval 10 + 20 = {:?}", value);
        }
        Err(msg) => {
            println!("Error: {msg:?}");
        }
    }
}

#[test]
fn test_value() {
    assert_eq!(eval(Expression::Value(19)), Ok(19));
}

#[test]
fn test_sum() {
    assert_eq!(
        eval(Expression::Op {
            op: Operation::Add,
            left: Box::new(Expression::Value(10)),
            right: Box::new(Expression::Value(20)),
        }),
        Ok(30)
    );
}

#[test]
fn test_recursion() {
    let term1 = Expression::Op {
        op: Operation::Mul,
        left: Box::new(Expression::Value(10)),
        right: Box::new(Expression::Value(9)),
    };
    let term2 = Expression::Op {
        op: Operation::Mul,
        left: Box::new(Expression::Op {
            op: Operation::Sub,
            left: Box::new(Expression::Value(3)),
            right: Box::new(Expression::Value(4)),
        }),
        right: Box::new(Expression::Value(5)),
    };
    assert_eq!(
        eval(Expression::Op {
            op: Operation::Add,
            left: Box::new(term1),
            right: Box::new(term2),
        }),
        Ok(85)
    );
}

#[test]
fn test_error() {
    assert_eq!(
        eval(Expression::Op {
            op: Operation::Div,
            left: Box::new(Expression::Value(99)),
            right: Box::new(Expression::Value(0)),
        }),
        Err(String::from("division by zero"))
    );
}

// Creating a String puts fixed-sized metadata on the stack and dynamically sized data,
// the actual string, on the heap
// ```bob
// Stack                             Heap
// .- - - - - - - - - - - - - -.     .- - - - - - - - - - - - - - - -.
// :                           :     :                               :
// :    s1                     :     :                               :
// :   +-----------+-------+   :     :   +----+----+----+----+----+  :
// :   | ptr       |   o---+---+-----+-->| H  | e  | l  | l  | o  |  :
// :   | len       |     5 |   :     :   +----+----+----+----+----+  :
// :   | capacity  |     5 |   :     :                               :
// :   +-----------+-------+   :     :                               :
// :                           :     `- - - - - - - - - - - - - - - -'
// `- - - - - - - - - - - - - -'
// ```
fn stack_and_heap() {
    let s1 = String::from("Hello");
    println!("s1: {s1}");
}

// Ownership
fn ownership() {
    struct Point(i32, i32);

    {
        let p = Point(3, 4);
        println!("x: {}", p.0);
    }

    // it is an error to use a variable outside its scope
    // error[E0425]: cannot find value `p` in this scope
    // println!("y: {}", p.1);
}

// Move Semantics
fn move_semantics() {
    let s1: String = String::from("Hello!");

    // An assignment will transfer ownership between variables
    // There is always *exactly* one variable binding which owns a value.
    let s2: String = s1;
    println!("s2: {s2}");

    // error[E0382]: borrow of moved value: `s1`
    // println!("s1: {s1}");

    let s3: String = s2.clone();
    println!("s2: {s2}"); // since s3 is copied from s2, not transfers the ownership
    println!("s3: {s3}");
}

fn say_hello(name: String) {
    println!("Hello {name}");
}

// Moves in Function Calls
fn moves_in_function_calls() {
    let name = String::from("Alice");

    // With the first call to 'say_hello', the current function gives up
    // onwership of 'name'. Afterwards, 'name' cannot be used anymore within
    // the current function.
    say_hello(name);

    // error[E0382]: use of moved value: `name`
    // say_hello(name);
}

// Copying and Cloning
fn copying_and_cloning() {
    // Certian types (which implement the 'Copy' trait) are copied by default.
    let x = 42;
    let y = x;
    println!("x: {x}");
    println!("y: {y}");

    // opt-in your own types to use copy semantics
    #[derive(Copy, Clone, Debug)]
    struct Point(i32, i32);

    let p1 = Point(3, 4);
    let p2 = p1;
    println!("p1: {p1:?}");
    println!("p2: {p2:?}");
}

// Borrowing
fn borrowing() {
    #[derive(Debug)]
    struct Point(i32, i32);

    fn add(p1: &Point, p2: &Point) -> Point {
        // The add function borrows two points and returns a new point.
        Point(p1.0 + p2.0, p1.1 + p2.1)
    }

    let p1 = Point(3, 4);
    let p2 = Point(10, 20);
    // the caller retains onwership of the inputs
    let p3 = add(&p1, &p2);
    println!("{p1:?} + {p2:?} = {p3:?}");

    // Rust puts constraints on the ways you can borrow values:
    // - You can have one or more &T values at any given time, or
    // - You can have exactly one &mut T value.
    let mut a: i32 = 10;
    let b: &i32 = &a;
    let d: &i32 = &a;

    // error[E0502]: cannot borrow `a` as mutable because it is also borrowed as immutable
    // {
    //     let c: &mut i32 = &mut a;
    //     *c = 20;
    // }

    println!("a: {a}");
    println!("b: {b}");
    println!("d: {d}");
}

fn lifetimes() {
    #[derive(Debug)]
    struct Point(i32, i32);

    fn left_most<'a>(p1: &'a Point, p2: &'a Point) -> &'a Point {
        if p1.0 < p2.0 { p1 } else { p2 }
    }

    let p1 = Point(10, 10);
    let p2 = Point(20, 20);
    let p3: &Point = left_most(&p1, &p2);
    println!("p3: {p3:?}");
}

// Structs and Methods
fn structs_and_methods() {
    #[derive(Debug)]
    struct Person {
        name: String,
        age: u8,
    }

    let mut peter = Person {
        name: String::from("Peter"),
        age: 27,
    };
    println!("{} is {} years old", peter.name, peter.age);

    peter.age = 28;
    println!("{} is {} years old", peter.name, peter.age);

    let jackie = Person {
        name: String::from("Jackie"),
        ..peter // copy the majority of the fields from struct 'peter'
    };
    println!("{} is {} years old", jackie.name, jackie.age);

    // tuple structs
    struct Point(i32, i32);

    let p = Point(17, 23);
    println!("({}, {})", p.0, p.1);

    // tuple structs are often used for single-field wrappers (called newtypes)
    // - the number is measured in some units: e.g. Newtons
    // - the value passed some validation when it was created, so you no longer have
    //   to validate it again.
    struct Newtons(f64);
    let force = Newtons(10.0);
    println!("the force is {} Newtons", force.0);

    impl Person {
        fn new(name: String, age: u8) -> Self {
            Self { name, age }
        }

        // NOTE: use `&self` instead of `self` here to support multiple-times calling
        // - `&self`: borrows the object from the caller using a shared and
        //     immutable reference
        // - `&mut self`: borrows the object from the caller using a unique
        //     and mutable reference
        // - `self`: takes ownership of the object and moves it away from the caller
        // - `mut self`: same as above, but the method can mutate the object.
        // - No receiver: this becomes a static method on the struct.
        //     Typically used to create constructors which are called new by convention.
        fn say_hello(&self) {
            println!("Hello, my name is {}", self.name);
        }
    }

    impl Default for Person {
        fn default() -> Person {
            Person {
                name: "Bot".to_string(),
                age: 0,
            }
        }
    }

    let tmp = Person::new(String::from("Peter"), 27);
    println!("{tmp:?}");
    tmp.say_hello();
    tmp.say_hello();

    let tmp = Person {
        name: "Sam".to_string(),
        ..Person::default()
    };
    println!("{tmp:#?}");
}

// Methods Example
fn methods_example() {
    #[derive(Debug)]
    struct Race {
        name: String,
        laps: Vec<i32>,
    }

    impl Race {
        fn new(name: &str) -> Race {
            // No receiver, a static method
            Race { name: String::from(name), laps: Vec::new() }
        }

        fn add_lap(&mut self, lap: i32) {
            // Exclusive borrowed read-write access to self
            self.laps.push(lap);
        }

        fn print_laps(&self) {
            // Shared and read-only borrowed access to self
            println!("Recorded {} laps for {}:", self.laps.len(), self.name);
            for (idx, lap) in self.laps.iter().enumerate() {
                println!("Lap {idx}: {lap} sec");
            }
        }

        fn finish(self) {
            // Exclusive ownership of self
            let total = self.laps.iter().sum::<i32>();
            println!("Race {} is finished, total lap time: {}", self.name, total);
        }
    }

    let mut race = Race::new("Monaco Grand Prix");
    race.add_lap(70);
    race.add_lap(68);
    race.print_laps();
    race.add_lap(71);
    race.print_laps();
    race.finish();

    // error[E0382]: borrow of moved value: `race`
    // race.add_lap(42);
}

struct Book {
    title: String,
    year: u16,
}

struct Library {
    books: Vec<Book>,
}

impl Book {
    // Constructor
    fn new(title: &str, year: u16) -> Book {
        Book {
            title: String::from(title),
            year,
        }
    }
}

impl Library {
    fn new() -> Library {
        Library { books: Vec::new() }
    }

    fn len(&self) -> usize {
        self.books.len()
    }

    fn is_empty(&self) -> bool {
        self.books.len() == 0
    }

    fn add_book(&mut self, book: Book) {
        self.books.push(book);
    }

    fn print_books(&self) {
        for (idx, book) in self.books.iter().enumerate() {
            println!("No.{}: {}, published in {}", idx + 1, book.title, book.year);
        }
    }

    fn oldest_book(&self) -> Option<&Book> {
        let mut _oldest_book: Option<&Book> = None;
        for book in &self.books {
            _oldest_book = match _oldest_book {
                Some(old_book) => {
                    if book.year < old_book.year { Some(book) } else { Some(old_book) }
                }
                None => Some(book),
            };
        }
        _oldest_book
    }
}

// Exercise: Storing Books
fn storing_books() {
    let mut library = Library::new();

    println!("The library is empty: library.is_empty() -> {}", library.is_empty());

    library.add_book(Book::new("Lord of the Rings", 1954));
    library.add_book(Book::new("Alice's Adventures in Wonderland", 1865));

    println!("The library is no longer empty: library.is_empty() -> {}", library.is_empty());

    library.print_books();

    match library.oldest_book() {
        Some(book) => println!("The oldest book is {}, published in {}", book.title, book.year),
        None => println!("The library is empty!"),
    }

    println!("The library has {} books", library.len());
    library.print_books();
}

pub struct User {
    name: String,
    age: u32,
    height: f32,
    visit_count: usize,
    last_blood_pressure: Option<(u32, u32)>,
}

pub struct Measurements {
    height: f32,
    blood_pressure: (u32, u32),
}

pub struct HealthReport<'a> {
    patient_name: &'a str,
    visit_count: u32,
    height_change: f32,
    blood_pressure_change: Option<(i32, i32)>,
}

impl User {
    pub fn new(name: String, age: u32, height: f32) -> Self {
        Self {
            name: name,
            age: age,
            height: height,
            visit_count: 0,
            last_blood_pressure: None,
        }
    }

    pub fn name(&self) -> &str {
        &self.name
    }

    pub fn age(&self) -> u32 {
        self.age
    }

    pub fn height(&self) -> f32 {
        self.height
    }

    pub fn doctor_visits(&self) -> u32 {
        self.visit_count.try_into().unwrap()
    }

    pub fn set_age(&mut self, new_age: u32) {
        self.age = new_age;
    }

    pub fn set_height(&mut self, new_height: f32) {
        self.height = new_height;
    }

    pub fn visit_doctor(&mut self, measurements: Measurements) -> HealthReport {
        let height_change = measurements.height - self.height;
        let blood_pressure_change = match self.last_blood_pressure {
            Some((low, high)) =>
                Some((
                    (measurements.blood_pressure.0 as i32) - (low as i32),
                    (measurements.blood_pressure.1 as i32) - (high as i32),
                )),
            None => None,
        };
        // Update the user's statistics
        self.visit_count += 1;
        self.set_height(measurements.height);
        self.last_blood_pressure = Some(measurements.blood_pressure);
        HealthReport {
            patient_name: &self.name,
            visit_count: self.visit_count as u32,
            height_change: height_change,
            blood_pressure_change: blood_pressure_change,
        }
    }
}

// Exercise: Health Statistics
fn health_statistics() {
    let bob = User::new(String::from("Bob"), 32, 155.2);
    println!("I'm {} and my age is {}", bob.name(), bob.age());
}

#[test]
fn test_height() {
    let bob = User::new(String::from("Bob"), 32, 155.2);
    assert_eq!(bob.height(), 155.2);
}

#[test]
fn test_set_age() {
    let mut bob = User::new(String::from("Bob"), 32, 155.2);
    assert_eq!(bob.age(), 32);
    bob.set_age(33);
    assert_eq!(bob.age(), 33);
}

#[test]
fn test_visit() {
    let mut bob = User::new(String::from("Bob"), 32, 155.2);
    assert_eq!(bob.doctor_visits(), 0);
    let report = bob.visit_doctor(Measurements {
        height: 156.1,
        blood_pressure: (120, 80),
    });
    assert_eq!(report.patient_name, "Bob");
    assert_eq!(report.visit_count, 1);
    assert_eq!(report.blood_pressure_change, None);

    let report = bob.visit_doctor(Measurements {
        height: 156.1,
        blood_pressure: (115, 76),
    });

    assert_eq!(report.visit_count, 2);
    assert_eq!(report.blood_pressure_change, Some((-5, -4)));
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

    println!("\n# Blocks");
    blocks();

    println!("\n# if expressions");
    if_expressions();

    println!("\n# for loops");
    for_loops();

    println!("\n# while loops");
    while_loops();

    println!("\n# break and continue");
    break_and_continue();

    println!("\n# loop expressions");
    loop_expressions();

    println!("\n# Variables");
    variables();

    println!("\n# Type Inference");
    type_inference();

    println!("\n# Constant Variables");
    const_variables();

    println!("\n# Static Variables");
    static_variables();

    println!("\n# Scopes and Shadowing");
    scopes_and_shadowing();

    println!("\n# Enums");
    enums();

    println!("\n# Variant Payloads");
    variant_payloads();

    println!("\n# Enum Sizes");
    enum_sizes();

    println!("\n# if let expressions");
    if_let_expressions();

    println!("\n# while let expressions");
    while_let_expressions();

    println!("\n# match expressions");
    match_expressions();

    println!("\n# Destructuring Enums");
    destructuring_enums();

    println!("\n# Destructuring Structs");
    destructing_structs();

    println!("\n# Destructuring Arrays");
    destructing_arrays();

    println!("\n# Match Gurads");
    match_guards();

    println!("\n# Luhn Algorithm");
    run_luhn_algirithm();

    println!("\n# Expression Evaluation");
    run_eval();

    println!("\n# Stack and Heap");
    stack_and_heap();

    println!("\n# Ownership");
    ownership();

    println!("\n# Move Semantics");
    move_semantics();

    println!("\n# Moves in Function Calls");
    moves_in_function_calls();

    println!("\n# Copying and Cloning");
    copying_and_cloning();

    println!("\n# Borrowing");
    borrowing();

    println!("\n# Lifetimes");
    lifetimes();

    println!("\n# Structs and Methods");
    structs_and_methods();

    println!("\n# Methods Example");
    methods_example();

    println!("\n# Exercise: Storing Books");
    storing_books();

    println!("\n# Exercise: Health Statistics");
    health_statistics();
}
