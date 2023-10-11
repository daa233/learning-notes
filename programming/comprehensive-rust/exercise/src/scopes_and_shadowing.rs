// Scopes and Shadowing
pub fn scopes_and_shadowing() {
    let a = 10;
    println!("before: {a}");

    {
        let a = "hello";
        println!("inner scope: {a}");

        let a = true;
        println!("shadowed in inner scope: {a}");
    }

    // after shadowing, both variable's memory location exist at the same time
    println!("after: {a}");

    let a = 1;
    let b = &a;
    let a = a + 1;
    println!("{a} {b}");
    // 2 1
}
