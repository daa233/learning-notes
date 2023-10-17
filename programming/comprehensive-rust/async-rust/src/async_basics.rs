use futures::executor::block_on;

async fn count_to(count: i32) {
    for i in 1..=count {
        println!("Count is {i}!");
    }
}

async fn async_main(count: i32) {
    count_to(count).await;
}

pub fn async_await_example() {
    // async_main returns a type which implements the `Future` trait
    block_on(async_main(10));
}

use tokio::time;

async fn tokio_count_to(count: i32) {
    for i in 1..=count {
        println!("Count is {i}!");
    }
    time::sleep(time::Duration::from_millis(1000)).await;
}

#[tokio::main]
pub async fn tokio_example() {
    tokio::spawn(tokio_count_to(10));

    for i in 1..5 {
        println!("Main task: {i}");
        time::sleep(time::Duration::from_millis(5)).await;
    }
}
