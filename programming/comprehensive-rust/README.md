# Comprehensive Rust

学习 [Comprehensive Rust](https://google.github.io/comprehensive-rust/)。

## 安装

参考 [Rust 官方教程](https://doc.rust-lang.org/book/ch01-01-installation.html) 安装 Rust。

Rust 官方教程是通过 rustup 来安装 Rust 的，也提供了其他的安装方法。rustup 是一个管理 Rust 版本和相关工具的命令行工具。

安装命令：
```bash
$ curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh
```

此命令运行完成后，会安装 Rust 的编译器（rustc）、包管理器 Cargo。安装成功后，终端会显示：
```
Rust is installed now. Great!
```

验证 rustc 版本：
```bash
$ rustc --version
rustc 1.73.0 (cc66ad468 2023-10-03)
$ cargo --version
cargo 1.73.0 (9c4383fb5 2023-08-26)
```

## Rust 是什么？

Rust 是 2015 年首次发布的新的编程语言。

Rust 具有以下特点：
- 和 C++ 类似，Rust 是静态编译语言。
    - rustc 使用 LLVM 作为它的后端
- Rust 支持多种平台和架构
    - x86、ARM、WebAssembly……
    - Linux、Mac、Windows……
- Rust 被广泛用于各种设备
    - 固件、bootloader
    - 智能显示设备
    - 手机
    - 家用电脑
    - 服务器

## 使用 Cargo


### Rust 生态

- `rustc`：Rust 编译器，将 `.rs` 文件编译为二进制文件或其他中间格式。
- `cargo`：Rust 的依赖管理工具和构建工具。在构建项目时，Cargo 知道如何下载相关的依赖并将它们传递给 rustc。相关的依赖一般托管在 https://crates.io 上。Cargo 还自带了一个执行单元测试的 test runner。
- `rustup`：Rust 工具链安装和更新工具，用来安装、更新 rustc、cargo，还可以安装标准库文档、管理多个不同版本的 Rust。 

### 在本地运行 Cargo

1. 可以通过 `cargo new exercise` 创建一个名为 `exercise` 的 cargo 样例包，其目录如下：
```
.
├── Cargo.toml
└── src
    └── main.rs
```

2. 在 `exercise/` 目录下，执行 `cargo run`，会构建并运行二进制文件：
```bash
$ cargo run         
   Compiling exercise v0.1.0 (/home/duangang/projects/tmp/learning-notes/programming/comprehensive-rust/exercise)
    Finished dev [unoptimized + debuginfo] target(s) in 0.25s
     Running `target/debug/exercise`
Hello, world!
```

3. `cargo check` 可以用于快速检查项目是否有错误；`cargo build` 会编译项目但不运行，输出目录为 `target/debug`；`cargo build --release` 会在构建时进行优化，输出目录在 `target/release`。

4. 可以通过修改 `Cargo.toml` 来增加项目依赖。在执行 `cargo` 命令时，它会自动下载和编译缺少的依赖。

## 为什么用 Rust？

Rust 一些独特的卖点：
- 编译时内存安全
- 运行时不会有未定义行为
- 具有现代语言的一些特性

TODO


## 基本语法


### Structs vs. Enums
- In both, you can have a simple version without fields (unit struct) or one with different types of fields (variant payloads).
- In both, associated functions are defined within an impl block.
- You could even implement the different variants of an enum with separate structs but then they wouldn’t be the same type as they would if they were all defined in an enum.


## 内存管理

编程语言的内存管理方法：
- 手动管理内存：如 C、C++、Pascal……
- 通过垃圾回收机制（GC）在运行时定期检查管理内存：如 Java、Python、Go、Haskell……
- 使用包含特定规则的所有权系统管理内存，编译器在编译过程中执行检查工作：如 Rust……

### 栈与堆
- 栈：用于存放局部变量的连续内存
    - 对应值在编译时大小固定
    - 速度极快：只需要移动栈顶指针
    - 容易管理
    - 局部性好，数据排布紧密
- 堆：存放函数调用外的值
    - 值的大小是运行时动态决定的
    - 速度比访问栈要慢
    - 不会保证内存的局部性，数据排布稀疏

### Rust 中的内存管理

- 像 Java 一样安全且正确，但是没有垃圾回收机制。
- 像 C++ 一样基于作用域（scope），但是通过编译器来强制遵守。
- Rust 用户可以根据使用场景选择合适的抽象，某些情况下甚至像 C 一样在运行时没有成本。

## 所有权 Ownership
变量（variable）绑定着具体的值（value），我们会说这个变量“拥有”（owns）这个值。

所有的变量绑定都有一个有效的作用域（scope），超出作用域使用该变量会导致错误。

在作用域的最后，变量会被弃用（dropped）并且对应的数据会被释放（freed），可以在此时调用析构（destructor）来实现。

### Move Semantics

> There is always *exactly* one variable binding which owns a value.

任何时刻，一个值（value）有且仅有一个变量（variable binding）拥有（owns）它。

变量之间的赋值会转移对值的所有权（ownership）。

```rust
fn move_semantics() {
    let s1: String = String::from("Hello!");

    // An assignment will transfer ownership between variables
    // There is always *exactly* one variable binding which owns a value.
    let s2: String = s1;
    println!("s2: {s2}");

    // error[E0382]: borrow of moved value: `s1`
    // println!("s1: {s1}");
}
```

如上面的代码，将 `s1` 赋值给 `s2` 会转移对 string 数据的所有权，所有权从 `s1` 转移到了 `s2`。当超出 `s1` 的作用域时，不会做任何操作，因为 `s1` 不拥有任何东西；当超出 `s2` 的作用域时，对应的 string 数据会被释放掉。

在执行完 `let s2: String = s1;` 之后，`s1` 就不可用了。

### C++ 中的移动语义
参考 [Defensive Copies in Modern C++](https://google.github.io/comprehensive-rust/ownership/double-free-modern-cpp.html) 在现代 C++ 中，`=` 默认是拷贝构造：
```c++
std::string s1 = "Cpp";
std::string s2 = s1;    // Duplicate the data in s1
```

在执行完赋值语句后，`s2` 和 `s1` 会各自拥有一份堆上的内存。

C++ 中也支持 move 语义（`std::move`）。在 C++ 中，如果执行 `s2 = std::move(s1)`，就不会在堆上新建内存。move 之后，`s1` 会处在一个可用但是不明确的状态（unspecified state）。而在 Rust 中，`s1` 被 move 之后就不可用了。

### 函数调用中的 move

在函数调用时，将一个值传给一个函数，值会被赋值给函数的参数，就发生了所有权的转移。

```rust
fn say_hello(name: String) {
    println!("Hello {name}")
}

fn main() {
    let name = String::from("Alice");

    // With the first call to 'say_hello', the current function gives up
    // onwership of 'name'. Afterwards, 'name' cannot be used anymore within
    // the current function.
    say_hello(name);

    // error[E0382]: use of moved value: `name`
    // say_hello(name);
}
```

例如上面的代码，在第一次调用 `say_hello` 之后，`main` 会放弃对 `name` 的所有权。在这之后，`main` 中就不能再使用 `name` 了。

如果希望在 `main` 中继续使用 `name`，则可以在调用时写 `say_hello(name.clone())`。与 C++ 不同，Rust 需要开发者显式地声明克隆操作。


### Copying and Cloning

但是对于某些数据类型来说，实现了 `Copy` 特性（trait），会默认执行拷贝操作。

在 Rust 中，拷贝（copying）和克隆（cloning）是不同的：
- 拷贝（copying）指的是按位复制内存区域，不是任意的对象都支持。
- 拷贝（copying）不允许自定义逻辑（与 C++ 中的拷贝构造函数不同）。
- 克隆（cloning）是一个更广义的操作，在实现 `Clone` 特性（trait）时允许自定义行为。
- 对于实现了 `Drop` 特性的类型来说，拷贝（copying）不生效。

### 借用（Borrowing）
在调用函数时，如果不想转移所有权，可以通过借用的方式实现：

```rust
#[derive(Debug)]
struct Point(i32, i32);

fn add(p1: &Point, p2: &Point) -> Point {
    Point(p1.0 + p2.0, p1.1 + p2.1)
}

fn main() {
    let p1 = Point(3, 4);
    let p2 = Point(10, 20);
    let p3 = add(&p1, &p2);
    println!("{p1:?} + {p2:?} = {p3:?}");
}
```

`add` 函数会借用 `p1`、`p2` 并且返回一个新的 point，调用者（`main`）仍然保有对输入参数的所有权。

### 共享的借用与唯一的借用

Rust 对值的借用做了限制，只能选择下面的一种：
- 任何时候拥有一个或多个 `&T` 的值，或者
- 拥有且仅拥有一个 `&mut T` 的值

```rust
fn main() {
    let mut a: i32 = 10;
    let b: &i32 = &a;

    {
        let c: &mut i32 = &mut a;
        *c = 20;
    }

    println!("a: {a}");
    println!("b: {b}");
}
```

上面的代码会报错 `error[E0502]: cannot borrow `a` as mutable because it is also borrowed as immutable`。

### 借用值的生命周期（lifetime）

借用值的生命周期可以是隐式的，例如函数调用的参数；

借用值的生命周期也可以是显式的，例如 `&'a Point`，指的是借用的 `Point` 至少在 `a` 的生命周期内有效。

生命周期总是由编译器自动推导出来的，不能自行赋值一个生命周期。
