#[derive(Debug)]
struct Point<T> {
    x: T,
    y: T,
}

pub fn generic_data_types() {
    let integer = Point { x: 5, y: 10 };
    let float = Point { x: 1.0, y: 4.0 };
    println!("{integer:?} and {float:?}");
}

struct TuplePoint<T>(T, T);

// Here use `impl<T>` to implement for generic types.
// `impl` can also be used for a single type, e.g. `impl Point<u32>`.
impl<T> TuplePoint<T> {
    fn x(&self) -> &T {
        &self.0
    }
}

pub fn generic_methods() {
    let p = TuplePoint(5, 10);
    println!("p.x = {}", p.x());

    // Monomorphization: Generic code is turned into non-generic code based on the call sites
    let integer = Some(5);
    let float = Some(5.0);
    println!("{integer:?} and {float:?}");
}
