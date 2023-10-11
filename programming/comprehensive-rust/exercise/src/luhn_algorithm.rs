// Luhn Algorithm
pub fn luhn(cc_number: &str) -> bool {
    let mut sum: u32 = 0;
    let mut count: u32 = 0;
    for c in cc_number.chars().rev() {
        if c == ' ' {
            continue;
        } else if !c.is_digit(10) {
            return false;
        }
        count += 1;
        let addend: u32;
        let digit = c.to_string().parse::<u32>().unwrap();
        if count % 2 == 0 {
            let doubled = digit * 2;
            if doubled > 9 {
                addend = 1 + (doubled % 10);
            } else {
                addend = doubled;
            }
        } else {
            addend = digit;
        }
        sum += addend;
    }
    count >= 2 && sum % 10 == 0
}

#[test]
fn test_non_digit_cc_number() {
    assert!(!luhn("foo"));
    assert!(!luhn("foo 0 0"));
}

#[test]
fn test_empty_cc_number() {
    assert!(!luhn(""));
    assert!(!luhn(" "));
    assert!(!luhn("  "));
    assert!(!luhn("    "));
}

#[test]
fn test_single_digit_cc_number() {
    assert!(!luhn("0"));
}

#[test]
fn test_two_digit_cc_number() {
    assert!(luhn(" 0 0 "));
}

#[test]
fn test_valid_cc_number() {
    assert!(luhn("4263 9826 4026 9299"));
    assert!(luhn("4539 3195 0343 6467"));
    assert!(luhn("7992 7398 713"));
}

#[test]
fn test_invalid_cc_number() {
    assert!(!luhn("4223 9826 4026 9299"));
    assert!(!luhn("4539 3195 0343 6476"));
    assert!(!luhn("8273 1232 7352 0569"));
}

pub fn run_luhn_algirithm() {
    let cc_number_array = ["4263 9826 4026 9299", "4223 9826 4026 9299"];
    for cc_number in &cc_number_array {
        let valid_or_not: &str = if luhn(cc_number) { "valid" } else { "invalid" };
        println!("The credit card number '{cc_number}' is {valid_or_not}");
    }
}
