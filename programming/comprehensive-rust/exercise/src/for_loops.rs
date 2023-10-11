// for loops
pub fn for_loops() {
    let v = vec![10, 20, 30];

    // the same as 'for x in v.into_iter()'
    for x in v {
        println!("x: {x}");
    }

    let mut mut_v = vec![10, 20, 30];
    for x in mut_v.iter_mut() {
        // the type of x here is '&mut {integer}'
        *x += 5;
        println!("x: {x}");
    }
    println!("mut_v: {:?}", mut_v);

    // (0..10) is a range that implements an Iterator trait
    for i in (0..10).step_by(2) {
        println!("i: {i}");
    }
}
