// while let expressions
pub fn while_let_expressions() {
    let v = vec![10, 20, 30];
    let mut iter = v.into_iter();

    // the iterator returned by v.into_iter() will return a Option<i32> on
    // every call to next().
    // It returns Some(x) until it is done, after which it will return None.
    while let Some(x) = iter.next() {
        println!("x: {x}");
    }
}
