// Structs and Methods
pub fn structs_and_methods() {
    #[derive(Debug)]
    struct Person {
        name: String,
        age: u8,
    }

    let mut peter = Person {
        name: String::from("Peter"),
        age: 27,
    };
    println!("{} is {} years old", peter.name, peter.age);

    peter.age = 28;
    println!("{} is {} years old", peter.name, peter.age);

    let jackie = Person {
        name: String::from("Jackie"),
        ..peter // copy the majority of the fields from struct 'peter'
    };
    println!("{} is {} years old", jackie.name, jackie.age);

    // tuple structs
    struct Point(i32, i32);

    let p = Point(17, 23);
    println!("({}, {})", p.0, p.1);

    // tuple structs are often used for single-field wrappers (called newtypes)
    // - the number is measured in some units: e.g. Newtons
    // - the value passed some validation when it was created, so you no longer have
    //   to validate it again.
    struct Newtons(f64);
    let force = Newtons(10.0);
    println!("the force is {} Newtons", force.0);

    impl Person {
        fn new(name: String, age: u8) -> Self {
            Self { name, age }
        }

        // NOTE: use `&self` instead of `self` here to support multiple-times calling
        // - `&self`: borrows the object from the caller using a shared and
        //     immutable reference
        // - `&mut self`: borrows the object from the caller using a unique
        //     and mutable reference
        // - `self`: takes ownership of the object and moves it away from the caller
        // - `mut self`: same as above, but the method can mutate the object.
        // - No receiver: this becomes a static method on the struct.
        //     Typically used to create constructors which are called new by convention.
        fn say_hello(&self) {
            println!("Hello, my name is {}", self.name);
        }
    }

    impl Default for Person {
        fn default() -> Person {
            Person {
                name: "Bot".to_string(),
                age: 0,
            }
        }
    }

    let tmp = Person::new(String::from("Peter"), 27);
    println!("{tmp:?}");
    tmp.say_hello();
    tmp.say_hello();

    let tmp = Person {
        name: "Sam".to_string(),
        ..Person::default()
    };
    println!("{tmp:#?}");
}
