// Dereferencing Raw Pointers
pub fn dereference_raw_pointers() {
    let mut num = 5;

    let r1 = &mut num as *mut i32;
    let r2 = r1 as *const i32;

    // Safe because r1 and r2 were obtained from references and so are
    // guaranteed to be non-null and properly aligned, the objects underlying
    // the references from which they were obtained are live throughout the
    // whole unsafe block, and they are not accessed either through the
    // references or concurrently through any other pointers.
    unsafe {
        println!("r1 is {}", *r1);
        *r1 = 10;
        println!("r2 is {}", *r2);
    }
}

// Mutable Static Variables
static mut COUNTER: u32 = 0;

fn add_to_counter(inc: u32) {
    // It is safe because it is single-threaded
    unsafe {
        COUNTER += inc;
    } // Potential data race!
}

pub fn mutable_static_variables() {
    add_to_counter(42);
    // It is safe because it is single-threaded
    unsafe {
        println!("COUNTER: {COUNTER}");
    } // Potential data race!
}

// A `union` looks like a `struct` in terms of declaration, but
// all of its fields exist in the same memory, superimposed over
// one another.
// It means we can interpret the same memory block according different types
// of each field.
#[repr(C)]
union MyUnion {
    i: u8,
    b: bool,
}

pub fn union_example() {
    let u = MyUnion { i: 42 };
    println!("int: {}", unsafe { u.i });
    println!("bool: {}", unsafe { u.b });
}

fn count_chars(s: &str) -> usize {
    s.chars().map(|_| 1).sum()
}

pub fn calling_unsafe_functions() {
    let emojis = "🗻∈🌏";

    // Callers of the `str.get_unchecked` function are responsible that
    // these preconditions are satisfied:
    // - The starting index must not exceed the ending index;
    // - Indexes must be within bounds of the original slice;
    // - Indexes must lie on UTF-8 sequence boundaries.
    unsafe {
        println!("emoji: {}", emojis.get_unchecked(0..4));
        println!("emoji: {}", emojis.get_unchecked(4..7));
        println!("emoji: {}", emojis.get_unchecked(7..11));
    }

    println!(
        "char count: {}",
        count_chars(unsafe { emojis.get_unchecked(0..7) })
    );
}

/// Swaps the values pointed to by the given pointers.
///
/// # Safety
///
/// The pointers must be valid and properly aligned.
unsafe fn swap(a: *mut u8, b: *mut u8) {
    let temp = *a;
    *a = *b;
    *b = temp;
}

pub fn writing_unsafe_functions() {
    let mut a = 42;
    let mut b = 66;

    // Safe because the pointers are valid and properly
    unsafe {
        swap(&mut a, &mut b);
    }

    println!("a = {}, b = {}", a, b);
}

extern "C" {
    fn abs(input: i32) -> i32;
}

pub fn calling_external_code() {
    unsafe {
        // Undefined behavior if abs misbehaves.
        println!("Absolute value of -3 according to C: {}", abs(-3));
    }
}

use std::mem::size_of_val;
use std::slice;

// NOTE: There should be a # Safety section on the Rustdoc for the trait explaining the requirements for the trait to be safely implemented.
/// ...
/// # Safety
/// The type must have a defined representation and no padding.
pub unsafe trait AsBytes {
    fn as_bytes(&self) -> &[u8] {
        unsafe { slice::from_raw_parts(self as *const Self as *const u8, size_of_val(self)) }
    }
}

// Safe because u32 has a defined representation and no padding
unsafe impl AsBytes for u32 {}

pub fn implementing_unsafe_traits() {
    let a: u32 = 65536;
    println!("a (u32) with value {} as bytes: {:?}", a, a.as_bytes());
}
