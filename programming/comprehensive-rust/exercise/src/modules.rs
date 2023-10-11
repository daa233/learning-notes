// Modules
// `mod` let us namespace types and functions
mod foo {
    pub fn do_something() {
        println!("In the foo module");
    }
}

mod bar {
    pub fn do_something() {
        println!("In the bar module");
    }
}

mod outer {
    fn private() {
        println!("outer::private");
    }

    pub fn public() {
        println!("outer::public");
    }

    mod private_inner {
        fn private() {
            println!("outer::private_inner::private");
        }

        pub fn public() {
            println!("outer::private_inner::public");
            super::private();
        }
    }

    pub mod public_inner {
        fn private() {
            println!("outer::public_inner::private");
        }

        pub fn public() {
            println!("outer::public_inner::public");
            super::private();
        }
    }
}

pub fn modules() {
    foo::do_something();
    bar::do_something();

    outer::public();
    outer::public_inner::public();

    // error[E0603]: module `private_inner` is private
    // outer::private_inner::public();
}
