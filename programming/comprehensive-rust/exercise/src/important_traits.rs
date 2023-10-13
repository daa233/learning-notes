use std::io::{BufRead, BufReader, Read, Result, Write};

struct Fibonacci {
    curr: u32,
    next: u32,
}

impl Iterator for Fibonacci {
    type Item = u32;

    fn next(&mut self) -> Option<Self::Item> {
        let new_next = self.curr + self.next;
        self.curr = self.next;
        self.next = new_next;
        Some(self.curr)
    }
}

// Iterator trait
pub fn iterator_trait() {
    let fib = Fibonacci { curr: 0, next: 1 };

    // the `for` llop syntax is acutally sugar for `IntoIterator`
    // https://doc.rust-lang.org/core/iter/index.html#for-loops-and-intoiterator
    for (i, n) in fib.enumerate().take(5) {
        println!("fib({i}): {n}");
    }
}

// FromIterator trait
pub fn from_iterator_trait() {
    let primes = vec![2, 3, 5, 7];
    // `Iterator::collect()` is implemented by `FromIterator::from_iter()`
    // use the 'turbofish' `collect::<Vec<_>>` to specify the return type
    let prime_squares = primes
        .into_iter()
        .map(|prime| prime * prime)
        .collect::<Vec<_>>();
    println!("prime_squares: {prime_squares:?}");
}

// From and Into trait
pub fn from_and_into_trait() {
    // Types implement `From` and `Into` to facilitate type conversions
    let s = String::from("hello");
    let addr = std::net::Ipv4Addr::from([127, 0, 0, 1]);
    let one = i16::from(true);
    let bigger = i32::from(123i16);
    println!("{s}, {addr}, {one}, {bigger}");

    // `Into` is automatically implemented when `From` is implemented
    let s: String = "hello".into();
    let addr: std::net::Ipv4Addr = [127, 0, 0, 1].into();
    let one: i16 = true.into();
    let bigger: i32 = (123i16).into();
    println!("{s}, {addr}, {one}, {bigger}");
}

// `R: Read` is a trait bound to require that the parameter type `R` implements the `Read` trait
fn count_lines<R: Read>(reader: R) -> usize {
    let buf_reader = BufReader::new(reader);
    buf_reader.lines().count()
}

// `W: Write` is a trait bound to require that the parameter type `W` implements the `Write` trait
fn log<W: Write>(writer: &mut W, msg: &str) -> Result<()> {
    writer.write_all(msg.as_bytes())?;
    writer.write_all("\n".as_bytes())
}

// Read and Write
pub fn read_example() -> Result<()> {
    let slice: &[u8] = b"foo\nbar\nbaz\n";
    println!("lines in slice: {}", count_lines(slice));

    // `?` is used at the end of an expression returning a Result, and is equivalent to a
    // match expression, where the Err(err) branch expands to an early return
    // Err(From::from(err)), and the Ok(ok) branch expands to an ok expression.
    // Reference: https://doc.rust-lang.org/rust-by-example/std/result/question_mark.html

    let current_exe = std::env::current_exe()?;
    let file = std::fs::File::open(&current_exe)?;
    println!(
        "lines in file '{}': {}",
        current_exe.display(),
        count_lines(file)
    );
    Ok(())
}

pub fn write_example() -> Result<()> {
    let mut buffer = Vec::new();
    log(&mut buffer, "Hello")?;
    log(&mut buffer, "World")?;
    println!("Logged: {:?}", buffer);

    // Create a path to the desired file
    let path = std::path::Path::new("hello.txt");
    let mut file = std::fs::File::create(&path)?;

    file.write_all("Hello, World!".as_bytes())?;
    let abs_path = match std::fs::canonicalize(&path) {
        Ok(v) => v,
        Err(msg) => {
            return Err(msg);
        }
    };
    println!("Already write to the file '{:?}'", abs_path);

    Ok(())
}

struct Droppable {
    name: &'static str,
}

// Drop trait
impl Drop for Droppable {
    fn drop(&mut self) {
        println!("Dropping {}", self.name);
    }
}

pub fn drop_trait() {
    let a = Droppable { name: "a" };
    {
        let b = Droppable { name: "b" };
        {
            let c = Droppable { name: "c" };
            let d = Droppable { name: "d" };
            println!("Exiting block B");
        }
        println!("Exiting block A");
    }
    drop(a); // call `drop(a)` here to early drop `a`, before exiting main

    // error[E0040]: explicit use of destructor method
    // a.drop();

    println!("Exiting main");
}

// The `Default` trait can be derived via #[derive(Default)]
#[derive(Debug, Default)]
struct Dog {
    age: u32,
    name: DogName,
}

#[derive(Debug)]
struct DogName(String);

impl Default for DogName {
    fn default() -> Self {
        Self("XiaoGou".into())
    }
}

// Default trait
pub fn default_trait() {
    let dog = Dog::default();
    println!("{dog:#?}");

    let another_dog = Dog {
        age: 3,
        // '..' here refers to struct update syntax, note NO ',' after it
        ..Dog::default()
    };
    println!("{another_dog:#?}");

    let virtual_dog: Option<Dog> = None;
    println!("{:#?}", virtual_dog.unwrap_or_default());
}

#[derive(Debug, Copy, Clone)]
struct Point {
    x: i32,
    y: i32,
}

// use default type parameter: `Self`, which will be the type we’re implementing Add on.
// See the `Add` trait definition: `pub trait Add<Rhs = Self> {...}`
impl std::ops::Add for Point {
    // the associated type name is 'Output', which is defined by the 'Add' trait
    type Output = Self;

    fn add(self, rhs: Self) -> Self {
        Self {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
        }
    }
}

// Set the `Rhs` type parameter to `(i32, i32)` instead of using the default of `Self`.
impl std::ops::Add<(i32, i32)> for Point {
    type Output = Point;

    fn add(self, rhs: (i32, i32)) -> Point {
        Point {
            x: self.x + rhs.0,
            y: self.y + rhs.1,
        }
    }
}

// Operator overloading
pub fn operator_overloading() {
    let p1 = Point { x: 10, y: 20 };
    let p2 = Point { x: 100, y: 200 };
    println!("{:?} + {:?} = {:?}", p1, p2, p1 + p2);

    let p3 = (5, 5);
    println!("{:?} + {:?} = {:?}", p1, p3, p1 + p3);
}

fn apply_with_log(func: impl FnOnce(i32) -> i32, input: i32) -> i32 {
    println!("Calling function on {input}");
    func(input)
}

// Closures
pub fn closure_traits() {
    // Closures or lambda expressions have types which cannot be named.
    // However, they implement special `Fn`, `FnMut` and `FnOnce` traits.

    let add_3 = |x| x + 3;
    println!("add_3: {}", apply_with_log(add_3, 10));
    println!("add_3: {}", apply_with_log(add_3, 20));

    let mut v = Vec::new();
    let mut accumulate = |x: i32| {
        v.push(x);
        v.iter().sum::<i32>()
    };
    println!("accumulate: {}", apply_with_log(&mut accumulate, 4));
    println!("accumulate: {}", apply_with_log(&mut accumulate, 5));

    let multiply_sum = |x| x * v.into_iter().sum::<i32>();
    println!("multiply_sum: {}", apply_with_log(multiply_sum, 3));
}
