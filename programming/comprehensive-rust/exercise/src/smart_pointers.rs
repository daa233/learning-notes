use std::{
    cell::RefCell,
    ops::{Deref, Drop},
    rc::Rc,
};

#[derive(Debug)]
enum BoxList {
    Cons(i32, Box<BoxList>),
    Nil,
}

enum RcList {
    Cons(i32, Rc<RcList>),
    Nil,
}

#[derive(Debug)]
enum List {
    Cons(Rc<RefCell<i32>>, Rc<List>),
    Nil,
}

use crate::smart_pointers::List::{Cons, Nil};

pub fn box_list_example() {
    let list = BoxList::Cons(
        1,
        Box::new(BoxList::Cons(
            2,
            Box::new(BoxList::Cons(3, Box::new(BoxList::Nil))),
        )),
    );
    println!("List: {:?}", list);
}

pub fn rc_list_example() {
    let a = Rc::new(RcList::Cons(
        5,
        Rc::new(RcList::Cons(10, Rc::new(RcList::Nil))),
    ));
    println!("count after creating a = {}", Rc::strong_count(&a));
    let b = RcList::Cons(3, Rc::clone(&a));
    println!("count after creating b = {}", Rc::strong_count(&a));
    {
        let c = RcList::Cons(4, Rc::clone(&a));
        println!("count after creating c = {}", Rc::strong_count(&a));
    }
    println!("count after c goes out of scope = {}", Rc::strong_count(&a));
}

pub fn rc_ref_list_example() {
    let value = Rc::new(RefCell::new(5));

    let a = Rc::new(Cons(Rc::clone(&value), Rc::new(Nil)));

    let b = Cons(Rc::new(RefCell::new(6)), Rc::clone(&a));
    let c = Cons(Rc::new(RefCell::new(10)), Rc::clone(&a));

    *value.borrow_mut() += 10;

    println!("a after = {:?}", a);
    println!("b after = {:?}", b);
    println!("c after = {:?}", c);
}

#[derive(Debug)]
struct MyBox<T: std::fmt::Debug>(T);

impl<T: std::fmt::Debug> MyBox<T> {
    fn new(x: T) -> MyBox<T> {
        MyBox(x)
    }
}

impl<T: std::fmt::Debug> Deref for MyBox<T> {
    type Target = T;

    fn deref(&self) -> &T {
        &self.0
    }
}

impl<T: std::fmt::Debug> Drop for MyBox<T> {
    fn drop(&mut self) {
        println!("Dropping MyBox with data `{:?}`!", self.0);
    }
}

pub fn my_box_example() {
    let x = 5;
    let y = MyBox::new(x);

    assert_eq!(5, x);
    assert_eq!(5, *y);

    let c = MyBox(String::from("my stuff"));
    let d = MyBox(String::from("other stuff"));
    println!("MyBox with string data created");
    std::mem::drop(c);
}
