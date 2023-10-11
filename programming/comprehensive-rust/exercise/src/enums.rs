// use `super::foo` refers to `foo` in the parent module.
use super::methods_example1::pick_one;

// Enums
#[derive(Debug)]
enum CoinFlip {
    Heads,
    Tails,
}

pub fn enums() {
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
pub fn variant_payloads() {
    let load = WebEvent::PageLoad;
    let press = WebEvent::KeyPress('x');
    let click = WebEvent::Click { x: 20, y: 80 };

    inspect(load);
    inspect(press);
    inspect(click);
}

use std::any::type_name;
use std::mem::{align_of, size_of};

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
    A,         // 0
    B = 10000, // e.g., you can control the discriminant if needed
    C,         // 10001
}

// Enum Sizes
pub fn enum_sizes() {
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
