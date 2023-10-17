mod async_basics;

use async_basics::{async_await_example, tokio_example};

fn main() {
    println!("\n# async/await");
    async_await_example();

    println!("\n# Tokio example");
    tokio_example();
}
