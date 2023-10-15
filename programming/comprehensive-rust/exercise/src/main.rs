mod array_and_for_loops;
mod blocks;
mod borrowing;
mod box_demo;
mod break_and_continue;
mod collatz_conjecture;
mod compound_types;
mod const_and_static;
mod copying_and_cloning;
mod enums;
mod error_handling;
mod expression_evaluation;
mod for_loops;
mod functions;
mod generics;
mod hash_map;
mod health_statistics;
mod hello_world;
mod if_expressions;
mod if_let_expressions;
mod implicit_conversions;
mod important_traits;
mod iterator_and_ownership;
mod lifetimes;
mod loop_expressions;
mod luhn_algorithm;
mod match_expressions;
mod methods_example1;
mod methods_example2;
mod modules;
mod move_semantics;
mod option_and_result;
mod ownership;
mod pattern_matching;
mod polygon_struct;
mod prefix_matches;
mod rc;
mod reference;
mod scalar_types;
mod scopes_and_shadowing;
mod simple_gui;
mod slices;
mod stack_and_heap;
mod storing_books;
mod string_demo;
mod structs_and_methods;
mod traits;
mod type_inference;
mod variables;
mod vec;
mod while_let_expressions;
mod while_loops;

use crate::array_and_for_loops::{array_and_for_loops, print_matrix};
use crate::blocks::blocks;
use crate::borrowing::borrowing;
use crate::box_demo::box_demo;
use crate::break_and_continue::break_and_continue;
use crate::collatz_conjecture::collatz_conjecture;
use crate::compound_types::compound_types;
use crate::const_and_static::{const_variables, static_variables};
use crate::copying_and_cloning::copying_and_cloning;
use crate::enums::{enum_sizes, enums, variant_payloads};
use crate::error_handling::{
    catch_stack_unwinding, converting_error_types, structred_error_handling,
};
use crate::expression_evaluation::run_eval;
use crate::for_loops::for_loops;
use crate::functions::functions;
use crate::generics::{generic_data_types, generic_methods};
use crate::hash_map::hash_map;
use crate::health_statistics::health_statistics;
use crate::hello_world::hello_world;
use crate::if_expressions::if_expressions;
use crate::if_let_expressions::if_let_expressions;
use crate::implicit_conversions::implicit_conversions;
use crate::important_traits::{
    closure_traits, default_trait, drop_trait, from_and_into_trait, from_iterator_trait,
    iterator_trait, operator_overloading, read_example, write_example,
};
use crate::iterator_and_ownership::iterator_and_ownership;
use crate::lifetimes::lifetimes;
use crate::loop_expressions::loop_expressions;
use crate::luhn_algorithm::run_luhn_algirithm;
use crate::match_expressions::match_expressions;
use crate::methods_example1::{methods, overloading};
use crate::methods_example2::methods_example;
use crate::modules::modules;
use crate::move_semantics::{move_semantics, moves_in_function_calls};
use crate::option_and_result::option_and_result;
use crate::ownership::ownership;
use crate::pattern_matching::{
    destructing_arrays, destructing_structs, destructuring_enums, match_guards,
};
use crate::polygon_struct::polygon_struct;
use crate::prefix_matches::run_prefix_matches;
use crate::rc::rc;
use crate::reference::references;
use crate::scalar_types::scalar_types;
use crate::scopes_and_shadowing::scopes_and_shadowing;
use crate::simple_gui::simple_gui;
use crate::slices::slices;
use crate::stack_and_heap::stack_and_heap;
use crate::storing_books::storing_books;
use crate::string_demo::string;
use crate::structs_and_methods::structs_and_methods;
use crate::traits::{
    blanket_implementation, default_methods, deriving_traits, trait_bounds, trait_objects,
    traits_example,
};
use crate::type_inference::type_inference;
use crate::variables::variables;
use crate::vec::vec;
use crate::while_let_expressions::while_let_expressions;
use crate::while_loops::while_loops;

fn main() {
    // Program entry point
    println!("\n# Hello World");
    hello_world();

    println!("\n# Small Example: the Collatz conjecture");
    collatz_conjecture();

    println!("\n# Scalar Types");
    scalar_types();

    println!("\n# Compound Types");
    compound_types();

    println!("\n# References");
    references();

    println!("\n# Slices");
    slices();

    println!("\n# String vs str");
    string();

    println!("\n# Functions");
    functions();

    println!("\n# Methods");
    methods();

    println!("\n# Overloading");
    overloading();

    println!("\n# Implicit Conversions");
    implicit_conversions();

    println!("\n# Arrays and for Loops");
    array_and_for_loops();
    print_matrix();

    println!("\n# Blocks");
    blocks();

    println!("\n# if expressions");
    if_expressions();

    println!("\n# for loops");
    for_loops();

    println!("\n# while loops");
    while_loops();

    println!("\n# break and continue");
    break_and_continue();

    println!("\n# loop expressions");
    loop_expressions();

    println!("\n# Variables");
    variables();

    println!("\n# Type Inference");
    type_inference();

    println!("\n# Constant Variables");
    const_variables();

    println!("\n# Static Variables");
    static_variables();

    println!("\n# Scopes and Shadowing");
    scopes_and_shadowing();

    println!("\n# Enums");
    enums();

    println!("\n# Variant Payloads");
    variant_payloads();

    println!("\n# Enum Sizes");
    enum_sizes();

    println!("\n# if let expressions");
    if_let_expressions();

    println!("\n# while let expressions");
    while_let_expressions();

    println!("\n# match expressions");
    match_expressions();

    println!("\n# Destructuring Enums");
    destructuring_enums();

    println!("\n# Destructuring Structs");
    destructing_structs();

    println!("\n# Destructuring Arrays");
    destructing_arrays();

    println!("\n# Match Gurads");
    match_guards();

    println!("\n# Luhn Algorithm");
    run_luhn_algirithm();

    println!("\n# Expression Evaluation");
    run_eval();

    println!("\n# Stack and Heap");
    stack_and_heap();

    println!("\n# Ownership");
    ownership();

    println!("\n# Move Semantics");
    move_semantics();

    println!("\n# Moves in Function Calls");
    moves_in_function_calls();

    println!("\n# Copying and Cloning");
    copying_and_cloning();

    println!("\n# Borrowing");
    borrowing();

    println!("\n# Lifetimes");
    lifetimes();

    println!("\n# Structs and Methods");
    structs_and_methods();

    println!("\n# Methods Example");
    methods_example();

    println!("\n# Exercise: Storing Books");
    storing_books();

    println!("\n# Exercise: Health Statistics");
    health_statistics();

    println!("\n# Option and Result");
    option_and_result();

    println!("\n# Vec");
    vec();

    println!("\n# HashMap");
    hash_map();

    println!("\n# Box");
    box_demo();

    println!("\n# Rc");
    rc();

    println!("\n# Modules");
    modules();

    println!("\n# Exercise: Iterators and Onwership");
    iterator_and_ownership();

    println!("\n# Exercise: String and Iterators");
    run_prefix_matches();

    println!("\n# Generic Data Types");
    generic_data_types();

    println!("\n# Generic Methods");
    generic_methods();

    println!("\n# Traits");
    traits_example();

    println!("\n# Trait Objects");
    trait_objects();

    println!("\n# Deriving Traits");
    deriving_traits();

    println!("\n# Default Methods");
    default_methods();

    println!("\n# Blanket Implementation");
    blanket_implementation();

    println!("\n# Trait Bounds");
    trait_bounds();

    println!("\n# Iterator Trait");
    iterator_trait();

    println!("\n# FromIterator Trait");
    from_iterator_trait();

    println!("\n# From and Into Trait");
    from_and_into_trait();

    println!("\n# Read and Write");
    if let Err(why) = read_example() {
        panic!("Error when execute the read example: {}", why);
    }
    if let Err(why) = write_example() {
        panic!("Error when execute the write example: {}", why);
    }

    println!("\n# Drop Trait");
    drop_trait();

    println!("\n# Default Trait");
    default_trait();

    println!("\n# Operator Overloading");
    operator_overloading();

    println!("\n# Closures");
    closure_traits();

    println!("\n# Exercise: Simple GUI");
    simple_gui();

    println!("\n# Exercise: Polygon Struct");
    polygon_struct();

    println!("\n# Catch the Stack Unwinding");
    catch_stack_unwinding();

    println!("\n# Structured Error Handling with Result");
    structred_error_handling();

    println!("\n# Converting Error Types");
    converting_error_types();
}
