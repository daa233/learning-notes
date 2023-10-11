// Option and Result
pub fn option_and_result() {
    let numbers = vec![10, 20, 30];
    let first: Option<&i8> = numbers.first();
    println!("first: {first:?}");

    // Result is the standard type to implement error handling
    // - If the vector has the right size, Result::Ok is returned with the array.
    // - Otherwise, Result::Err is returned with the original vector.
    let arr: Result<[i8; 3], Vec<i8>> = numbers.try_into();
    println!("arr: {arr:?}");
}
