// if let expressions
pub fn if_let_expressions() {
    // The if let expression lets you execute different code depending on
    // whether a value matches a pattern
    let arg = std::env::args().next();
    if let Some(value) = arg {
        println!("Program name: {value}");
    } else {
        println!("Missing name?");
    }

    let test: Option<std::env::Args> = None;
    if let Some(value) = test {
        println!("value: {value:?}");
    } else {
        println!("the value is None");
    }

    let dish = ("Ham", "Eggs");

    // this body will be skipped because the pattern is refuted
    if let ("Bacon", b) = dish {
        println!("Bacon is served with {}", b);
    } else {
        // This block is evaluated instead.
        println!("No bacon will be served");
    }

    // this body will execute
    if let ("Ham", b) = dish {
        println!("Ham is served with {}", b);
    }

    if let _ = 5 {
        println!("Irrefutable patterns are always true");
    }
}
