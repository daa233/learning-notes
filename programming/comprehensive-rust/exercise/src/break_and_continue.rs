// break and continue
pub fn break_and_continue() {
    let x: u32 = 5;
    let mut i: u32 = 0;
    while i < 10000 {
        if i == 0 {
            i += 1;
            // use continue to immediately start the next iteration
            continue;
        }
        println!("i: {i}");
        if i >= x {
            // use break to exit a loop early
            break;
        }
        i += 1;
    }
}
