// Move Semantics
pub fn move_semantics() {
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
pub fn moves_in_function_calls() {
    let name = String::from("Alice");

    // With the first call to 'say_hello', the current function gives up
    // onwership of 'name'. Afterwards, 'name' cannot be used anymore within
    // the current function.
    say_hello(name);

    // error[E0382]: use of moved value: `name`
    // say_hello(name);
}
