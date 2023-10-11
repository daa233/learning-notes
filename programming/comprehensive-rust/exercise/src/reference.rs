// References
pub fn references() {
    let mut x: i32 = 10;
    println!("original x: {x}");

    let ref_x: &mut i32 = &mut x;

    // Error: error[E0502]: cannot borrow `x` as immutable because it is also borrowed as mutable
    // println!("original x: {x}");

    *ref_x = 7;
    println!("ref_x.count_ones(): {}", ref_x.count_ones());
    println!("after modify by reference x: {x}");

    // dangling references
    /* Error: error[E0597]: `y` does not live long enough
    let ref_y: &i32;
    {
        let y: i32 = 10;
        ref_y = &y;
    }
    println!("ref_y: {ref_y}");
    */
}
