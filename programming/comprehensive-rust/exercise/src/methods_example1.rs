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

pub fn methods() {
    let mut rect = Rectangle {
        width: 10,
        height: 5,
    };
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
pub fn pick_one<T>(a: T, b: T) -> T {
    if std::process::id() % 2 == 0 {
        a
    } else {
        b
    }
}

pub fn overloading() {
    println!("coin toss: {}", pick_one("heads", "tails"));
    println!("cash prize: {}", pick_one(500, 1000));
}
