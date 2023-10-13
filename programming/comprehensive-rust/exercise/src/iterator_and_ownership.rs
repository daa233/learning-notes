// Iterators and Ownership
pub fn iterator_and_ownership() {
    // Iterator
    let v: Vec<i8> = vec![10, 20, 30];
    let mut iter = v.iter(); // yield `&T` by convention

    // the return value type is `Option<&i8>`
    let v0 = iter.next();
    println!("v[0]: {:?}", v0);
    println!("No more items: {:?}", iter.next());

    // IntoInterator
    let v: Vec<String> = vec![String::from("foo"), String::from("bar")];
    let mut iter = v.into_iter(); // may yield `T`, `&T` or `&mut T` depending on the context

    // the return value type is `Option<String>`
    let v0 = iter.next();
    println!("v[0]: {:?}", v0);

    // for Loops
    let v: Vec<String> = vec![String::from("foo"), String::from("bar")];
    // the return value type is &String
    for word in &v {
        println!("word: {word}");
    }
    // the return value type is String
    for word in v {
        println!("word: {word}");
    }
}
