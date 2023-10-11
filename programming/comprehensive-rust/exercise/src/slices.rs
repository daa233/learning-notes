// Slices
pub fn slices() {
    // A slice gives you a view into a larger collection
    let mut a: [i32; 6] = [10, 20, 30, 40, 50, 60];
    a[2] = 35;
    println!("a: {a:?}");

    // NOTE: the type of s (&[i32]) no longer mentions the array length.
    // This allows us to perform computation on slices of different sizes.
    let s: &[i32] = &a[2..4];

    // error[E0506]: cannot assign to `a[_]` because it is borrowed
    // a[3] = 45;

    println!("s: {s:?}");
}
