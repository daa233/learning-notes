// Constant Variables
// Constant variables are evaluated at compile time and their values are inlined wherever they are used
const DIGEST_SIZE: usize = 3;
// 'Some' means some value of type T
const ZERO: Option<u8> = Some(42);
fn compute_digest(text: &str) -> [u8; DIGEST_SIZE] {
    // 'unwrap_or' returns the contained Some value or a provided default.
    let mut digest = [ZERO.unwrap_or(0); DIGEST_SIZE];
    for (idx, &b) in text.as_bytes().iter().enumerate() {
        // 'wrapping_add' computes 'self + rhs'
        digest[idx % DIGEST_SIZE] = digest[idx % DIGEST_SIZE].wrapping_add(b);
    }
    digest
}

pub fn const_variables() {
    let s: &str = "Hello";
    let digest = compute_digest(s);
    println!("digest: {digest:?}");
    println!("s.as_bytes(): {:?}", s.as_bytes());
}

// Static Varaibles
// Static variables will live during the whole execution of the program, and therefore will not move
static BANNER: &str = "Welcome to RustOS 3.14";
pub fn static_variables() {
    println!("{BANNER}");
}
