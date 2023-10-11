// loop expressions
pub fn loop_expressions() {
    let mut x = 10;
    print!("x: {x}");
    // loop == while true, which creates an endless loop
    // you must either break or return to stop the loop
    loop {
        x = if x % 2 == 0 { x / 2 } else { 3 * x + 1 };
        print!(" -> {x}");
        if x == 1 {
            break;
        }
    }
    println!();

    // returning from loops
    let mut counter = 0;
    let result = loop {
        counter += 1;

        if counter == 10 {
            // put the value after break to return by the loop expression
            break counter * 2;
        }
    };
    println!("result of loop: {result}");
}
