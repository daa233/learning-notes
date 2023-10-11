// Functions
pub fn functions() {
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
