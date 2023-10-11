// while loops
pub fn while_loops() {
    let mut x = 10;
    print!("x: {x}");
    while x != 1 {
        x = if x % 2 == 0 { x / 2 } else { 3 * x + 1 };
        print!(" -> {x}");
    }
    println!();
}
