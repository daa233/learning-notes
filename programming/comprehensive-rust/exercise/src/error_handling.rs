use std::io::Read;
use std::panic;
use std::{fs, io};

pub fn catch_stack_unwinding() {
    // use the following line to set the panic hook to empty and suppress the panic outputs
    // panic::set_hook(Box::new(|_| {}));

    // Here `||` means a lambda expression without parameters
    let result = panic::catch_unwind(|| {
        println!("hello!");
    });
    assert!(result.is_ok());

    let result = panic::catch_unwind(|| {
        panic!("oh no!");
    });
    assert!(result.is_err());

    let v = vec![10, 20, 30];
    let result = panic::catch_unwind(|| {
        println!("v[100]: {}", v[100]);
    });
    assert!(result.is_err());

    println!("after catch unwinding")
}

fn read_username(path: &str) -> Result<String, io::Error> {
    let username_file_result = fs::File::open(path);
    let mut username_file = match username_file_result {
        Ok(file) => file,
        Err(err) => {
            return Err(err);
        }
    };

    let mut username = String::new();
    match username_file.read_to_string(&mut username) {
        Ok(_) => Ok(username),
        Err(err) => Err(err),
    }
}

pub fn structred_error_handling() {
    fs::write("config.dat", "alice").unwrap();
    let username = read_username("config.dat");
    println!("username or error: {username:?}");
}

pub fn converting_error_types() {
    use std::error::Error;
    use std::fmt::{self, Display, Formatter};
    use std::fs::{self, File};
    use std::io::{self, Read};

    #[derive(Debug)]
    enum ReadUsernameError {
        IoError(io::Error),
        EmptyUsername(String),
    }

    impl Error for ReadUsernameError {}

    impl Display for ReadUsernameError {
        fn fmt(&self, f: &mut Formatter) -> fmt::Result {
            match self {
                Self::IoError(e) => write!(f, "IO error: {e}"),
                Self::EmptyUsername(filename) => write!(f, "Found no username in {filename}"),
            }
        }
    }

    impl From<io::Error> for ReadUsernameError {
        fn from(err: io::Error) -> ReadUsernameError {
            ReadUsernameError::IoError(err)
        }
    }

    fn read_username(path: &str) -> Result<String, ReadUsernameError> {
        let mut username = String::with_capacity(100);
        File::open(path)?.read_to_string(&mut username)?;
        if username.is_empty() {
            return Err(ReadUsernameError::EmptyUsername(String::from(path)));
        }
        Ok(username)
    }

    let username = read_username("config.dat");
    println!("username or error: {username:?}");
}
