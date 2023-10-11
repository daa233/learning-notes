// Lifetimes
pub fn lifetimes() {
    #[derive(Debug)]
    struct Point(i32, i32);

    fn left_most<'a>(p1: &'a Point, p2: &'a Point) -> &'a Point {
        if p1.0 < p2.0 {
            p1
        } else {
            p2
        }
    }

    let p1 = Point(10, 10);
    let p2 = Point(20, 20);
    let p3: &Point = left_most(&p1, &p2);
    println!("p3: {p3:?}");
}
