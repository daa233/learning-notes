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


## 

