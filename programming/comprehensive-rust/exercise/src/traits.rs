use std::fmt::Display;

struct Dog {
    name: String,
    age: i8,
}
struct Cat {
    lives: i8,
} // No name needed, cats won't respond anyway

trait Pet {
    fn talk(&self) -> String;
}

impl Pet for Dog {
    fn talk(&self) -> String {
        format!("Woof, my name is {}!", self.name)
    }
}

impl Pet for Cat {
    fn talk(&self) -> String {
        String::from("Miau!")
    }
}

fn greet<P: Pet>(pet: &P) {
    println!("Oh you're a cutie! What's your name? {}", pet.talk());
}

pub fn traits_example() {
    let captain_floof = Cat { lives: 9 };
    let fido = Dog {
        name: String::from("Fido"),
        age: 5,
    };

    greet(&captain_floof);
    greet(&fido);
}

// Stack                             Heap
// .- - - - - - - - - - - - - -.     .- - - - - - - - - - - - - - - - - - - - - - -.
// :                           :     :                                             :
// :    pets                   :     :                     +----+----+----+----+   :
// :   +-----------+-------+   :     :   +-----+-----+  .->| F  | i  | d  | o  |   :
// :   | ptr       |   o---+---+-----+-->| o o | o o |  |  +----+----+----+----+   :
// :   | len       |     2 |   :     :   +-|-|-+-|-|-+  `---------.                :
// :   | capacity  |     2 |   :     :     | |   | |    data      |                :
// :   +-----------+-------+   :     :     | |   | |   +-------+--|-------+        :
// :                           :     :     | |   | '-->| name  |  o, 4, 4 |        :
// :                           :     :     | |   |     | age   |        5 |        :
// `- - - - - - - - - - - - - -'     :     | |   |     +-------+----------+        :
//                                   :     | |   |                                 :
//                                   :     | |   |      vtable                     :
//                                   :     | |   |     +----------------------+    :
//                                   :     | |   '---->| "<Dog as Pet>::talk" |    :
//                                   :     | |         +----------------------+    :
//                                   :     | |                                     :
//                                   :     | |    data                             :
//                                   :     | |   +-------+-------+                 :
//                                   :     | '-->| lives |     9 |                 :
//                                   :     |     +-------+-------+                 :
//                                   :     |                                       :
//                                   :     |      vtable                           :
//                                   :     |     +----------------------+          :
//                                   :     '---->| "<Cat as Pet>::talk" |          :
//                                   :           +----------------------+          :
//                                   :                                             :
//                                   '- - - - - - - - - - - - - - - - - - - - - - -'
pub fn trait_objects() {
    // `dyn Pet` is a way to tell the compiler about a dynamically sized type
    // that implements `Pet`.
    let pets: Vec<Box<dyn Pet>> = vec![
        Box::new(Cat { lives: 9 }),
        Box::new(Dog {
            name: String::from("Fido"),
            age: 5,
        }),
    ];
    for pet in pets {
        println!("Hello, who are you? {}", pet.talk());
    }

    println!(
        "{} {}",
        std::mem::size_of::<Dog>(),
        std::mem::size_of::<Cat>()
    );
    println!(
        "{} {}",
        std::mem::size_of::<&Dog>(),
        std::mem::size_of::<&Cat>()
    );
    // the pointer here is a 'fat pointer', which is a double-width pointer.
    // The fat pointer has two components: a pointer to the acutal object and
    // a pointer to the virtual method table (vtable) for the `Pet` implementation
    // of that particular object.
    println!("{}", std::mem::size_of::<&dyn Pet>());
    println!("{}", std::mem::size_of::<Box<dyn Pet>>());
}

// Rust derive macros work by automatically generating code that implements the specified
// traits for a data structure.
#[derive(Debug, Clone, PartialEq, Eq, Default)]
struct Player {
    name: String,
    strength: u8,
    hit_point: u8,
}

pub fn deriving_traits() {
    let p1 = Player::default();
    let p2 = p1.clone();
    println!(
        "Is {:?}\nequal to {:?}?\nThe answer is {}!",
        &p1,
        &p2,
        if p1 == p2 { "yes" } else { "no" }
    );
}

trait Equals {
    fn equals(&self, other: &Self) -> bool;
    fn approx(&self, other: &Self) -> bool {
        self.equals(other)
    }
}

trait NotEquals {
    fn not_equals(&self, other: &Self) -> bool;
}

#[derive(Debug)]
struct Centimeter(i16);

impl Equals for Centimeter {
    fn equals(&self, other: &Centimeter) -> bool {
        self.0 == other.0
    }
    // will use the default method of 'approx'
}

// The blanket implementation of `NotEquals` for `Equals`.
// It means that it implements `NotEquals` for all types that
// implements the `Equals` trait.
// The `where` clause here is the traits bound to stipulate what
// functionality the type should implements.
impl<T> NotEquals for T
where
    T: Equals,
{
    fn not_equals(&self, other: &Self) -> bool {
        !self.equals(other)
    }
}

pub fn default_methods() {
    let a = Centimeter(10);
    let b = Centimeter(20);
    println!("{a:?} equals {b:?}: {}", a.equals(&b));
    println!("{a:?} approx {b:?}: {}", a.approx(&b));
}

pub fn blanket_implementation() {
    let a = Centimeter(10);
    let b = Centimeter(20);
    println!("{a:?} equals {b:?}: {}", a.equals(&b));
    println!("{a:?} not equals {b:?}: {}", a.not_equals(&b));
}

// The `T: Clone` here indicates we require the type T implements `Clone` trait
fn duplicate<T: Clone>(a: T) -> (T, T) {
    (a.clone(), a.clone())
}

// The `impl Into<i32>` here indicates we require the type T implements `Into<i32>` trait
// Syntactic sugar for:
//   fn add_42_millions<T: Into<i32>>(x: T) -> i32 {
fn add_42_millions(x: impl Into<i32>) -> i32 {
    x.into() + 42_000_000
}

// Here are two `impl Display`s:
// - for a parameter, `impl Trait` s like an anonymous generic parameter with a trait bound.
// - for a return type, t means that the return type is some concrete type that implements
//   the trait, without naming the type.
// In other words, the parameter and the return value may not be in the same type, but requires
//  both of the types implement the `Display` trait.
fn get_x(name: impl Display) -> impl Display {
    format!("Hello {name}")
}

pub fn trait_bounds() {
    // When working with generics, the type parameters often must use traits as bounds to
    // stipulate what functionality a type implements.

    let foo = String::from("foo");
    let pair = duplicate(foo);
    println!("{pair:?}");

    // let cat = Cat { lives: 1 };
    // error[E0277]: the trait bound `Cat: Clone` is not satisfied
    // let cat_pair = duplicate(cat);

    let many = add_42_millions(42_i8);
    println!("{many}");
    let many_more = add_42_millions(10_000_000);
    println!("{many_more}");

    println!("{}", get_x(1));
    let s = String::from("World");
    println!("{}", get_x(s));

    // error[E0277]: `Cat` doesn't implement `std::fmt::Display`
    // println!("{}", get_x(Cat { lives: 1 }));
}
