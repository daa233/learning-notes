// Lifetimes

use std::fmt::Debug;

// `print_refs` takes two references to `i32` which have different
// lifetimes `'a` and `'b`. These two lifetimes must both be at
// least as long as the function `print_refs`.
fn print_refs<'a, 'b>(x: &'a i32, y: &'b i32) {
    println!("x is {} and y is {}", x, y);
}

// One input reference with lifetime `'a` which must live
// at least as long as the function.
fn print_one<'a>(x: &'a i32) {
    println!("`print_one`: x is {}", x);
}

// Multiple elements with different lifetimes. In this ase, it
// would be fine for both to have the same lifetime `'a`, but
// in more complex cases, different lifetimes may be required.
fn print_multi<'a, 'b>(x: &'a i32, y: &'b i32) {
    println!("`print_multi`: x is {}, y is {}", x, y);
}

// Returning references that have been passed in in acceptable.
// However, the correct lifetime must be returned.
fn pass_x<'a, 'b>(x: &'a i32, _: &'b i32) -> &'a i32 {
    x
}

// Mutable reference are possible with lifetimes as well
fn add_one<'a>(x: &'a mut i32) {
    *x += 1;
}

// lifetime in funtion
fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

struct Owner(i32);

impl Owner {
    // Annotate lifetimes as in a standalone function.
    fn add_one<'a>(&'a mut self) {
        self.0 += 1;
    }
    fn print<'a>(&'a self) {
        println!("`print`: {}", self.0);
    }
}

// A type `Borrowed` which houses a reference to an
// `i32`. The reference to `i32` must outlive `Borrowed`.
#[derive(Debug)]
struct Borrowed<'a> {
    x: &'a i32,
}

// Annotate lifetimes to impl.
impl<'a> Default for Borrowed<'a> {
    fn default() -> Self {
        Self { x: &10 }
    }
}

// Similarly, both references here must outlive this structure.
#[derive(Debug)]
struct NamedBorrowed<'a> {
    x: &'a i32,
    y: &'a i32,
}

// An enum which is either an `i32` or a reference to one.
#[derive(Debug)]
enum Either<'a> {
    Num(i32),
    Ref(&'a i32),
}

#[derive(Debug)]
struct Ref<'a, T: 'a>(&'a T);
// `Ref` contains a reference to a generic type `T` that has
// an unknown lifetime `'a`. `T` is bounded such that any
// *references* in `T` must outlive `'a`. Additionally, the lifetime
// of `Ref` may not exceed `'a`.

// A gneeric function which prints using the `Debug` trait.
fn print<T>(t: T)
where
    T: Debug,
{
    println!("`print`: t is {:?}", t);
}

// Here a reference to `T` is taken where `T` implements
// `Debug` and all *references* in `T` outlives `'a`. In
// addition, `'a` must outlive the function.
fn print_ref<'a, T>(t: &'a T)
where
    T: Debug + 'a,
{
    println!("`print_ref`: t is {:?}", t);
}

// Here, Rust infers a lifetime that is as short as possible.
// The two references are then coerced to that lifetime.
fn multiply<'a>(first: &'a i32, second: &'a i32) -> i32 {
    first * second
}

// `<'a: 'b, 'b>` reads as lifetime `'a` is at least as long as `'b`.
// Here, we take in an `&'a i32` and return a `&'b i32` as a result of coercion.
fn choose_first<'a: 'b, 'b>(first: &'a i32, _: &'b i32) -> &'b i32 {
    first
}

// A reference with 'static lifetime, the data pointed to by the reference lives
// for the entire lifetime of the running program.
static HELLO_WORLD: &'static str = "hello world";
static NUM: i32 = 18;

// 'static as part of a trait bound
fn generic<T>(x: T)
where
    T: 'static + Debug,
{
    println!("`x` is {:?}", x);
}

// Returns a reference to `NUM` where its `'static`
// lifetime is coerced to that of the input argument.
fn coerce_static<'a>(_: &'a i32) -> &'a i32 {
    &NUM
}

pub fn lifetimes() {
    let (four, nine) = (4, 9);

    // Borrows (`&`) of both variables are passed into the function.
    print_refs(&four, &nine);
    // Any input which is borrowed must outlive the borrower.
    // In other words, the lifetime of `four` and `nine` must
    // be longer than that of `print_refs`.

    // Functions
    print_one(&four);
    print_multi(&four, &nine);

    let z = pass_x(&four, &nine);
    print_one(z);

    let mut t = 5;
    add_one(&mut t);
    print_one(&t);

    let string1 = String::from("long string is long");

    {
        let string2 = String::from("xyz");
        let result = longest(string1.as_str(), string2.as_str());
        println!("The longest string is {}", result);
    }

    // Methods
    let mut owner = Owner(18);
    owner.add_one();
    owner.print();

    // Structs
    let x = 18;
    let y = 15;
    let single = Borrowed { x: &x };
    let double = NamedBorrowed { x: &x, y: &y };
    let reference = Either::Ref(&x);
    let number = Either::Num(y);
    println!("x is borrowed in {:?}", single);
    println!("x and y are borrowed in {:?}", double);
    println!("x is borrowed in {:?}", reference);
    println!("y is *not* borrowed in {:?}", number);

    // Traits
    let b: Borrowed = Default::default();
    println!("b is {:?}", b);

    // Bounds
    let ref_x = Ref(&x);
    print_ref(&ref_x);
    print(ref_x);

    // Coercion
    let first = 2; // Longer lifetime
    {
        let second = 3; // Shorter lifetime
        println!("The product is {}", multiply(&first, &second));
        println!("{} is the first", choose_first(&first, &second));
    }

    // Static
    generic(&HELLO_WORLD);
    {
        // Make a `string` literal and print it:
        let static_string = "I'm in read-only memory";
        println!("static_string: {}", static_string);

        // When `static_string` goes out of scope, the reference
        // can no longer be used, but the data remains in the binary.
    }
    {
        // Make an integer to use for `coerce_static`:
        let lifetime_num = 9;
        // Coerce `NUM` to lifetime of `lifetime_num`:
        let coerced_static = coerce_static(&lifetime_num);

        println!("coerced_statc: {}", coerced_static);
        // the value of `coerced_static` is `NUM`'s value. However,
        // `coerced_static` is not accessible when goes out of the scope.
    }

    println!("NUM: {} stays accessible!", NUM);
}
