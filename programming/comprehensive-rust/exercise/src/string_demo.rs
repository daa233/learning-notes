// String
pub fn string() {
    // &str: an immutable reference to a string slice
    let s1: &str = "World";
    println!("s1: {s1}");

    // String: a mutable string buffer
    let mut s2: String = String::from("Hello ");
    println!(
        "s2: {s2}, len = {}, number of chars = {}",
        s2.len(),
        s2.chars().count()
    );
    s2.push_str(s1);
    println!("s2: {s2}");

    let s3: &str = &s2[6..];
    println!("s3: {s3}");

    let mut s4 = String::new(); // String::new() returns a new empty string
    s4.push_str("Hello");
    println!("s4: len = {}, capacity = {}", s4.len(), s4.capacity());

    let mut s5 = String::with_capacity(s4.len() + 1);
    s5.push_str(&s4);
    s5.push('!');
    println!("s5: len = {}, capacity = {}", s5.len(), s5.capacity());
    // s5: len = 6, capacity = 6
    s5.push('#'); // the capacity of string increases automatically
    println!("s5: len = {}, capacity = {}", s5.len(), s5.capacity());
    // s5: len = 7, capacity = 12
}
