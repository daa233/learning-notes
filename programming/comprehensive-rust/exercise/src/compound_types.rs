// compound types
pub fn compound_types() {
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
