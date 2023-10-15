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

## 方法（methods）
方法与函数十分相似：它们都使用 `fn` 关键字及一个名称来进行声明；它们都可以拥有参数和返回值；另外，它们都包含了一段在调用时执行的代码。但是，方法与函数依然是两个不同的概念，因为方法总是被定义在某个结构体（或者枚举类型、trait对象）的上下文中，并且它们的第一个参数永远都是self，用于指代调用该方法的结构体实例。

选择方法的 self 参数签名类型：
- `&self`：既不用获得数据的所有权也不需要写入数据，而只需要读取数据即可
- `&mut self`：想要在调用方法时改变实例的某些数据
- `self`：在调用过程中取得实例的所有权，这种用法并不常见。可能会被用于那些需要将 self 转换为其他类型，且在转换后想要阻止调用者访问原始实例的场景。

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

总结：
- Rust中的每一个值都有一个对应的变量作为它的所有者。
- 在同一时间内，值有且仅有一个所有者。
- 当所有者离开自己的作用域时，它持有的值就会被释放掉。

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

## Modules

- 包（package）: 一个用于构建、测试并分享单元包的 Cargo 功能。一个包可以拥有多个二进制单元包（crate）以及一个可选的库单元包。
- 单元包（crate）：一个用于生成库或可执行文件的树形模块结构。
- 模块（module）：和 `use` 一起控制文件结构、作用域（scope）及路径的私有性。
- 路径（path）：一种用于命名条目的方法，这些条目包括结构体、函数和模块。

### 可见性

模块（module）是私有性的边界：
- 模块中的项目默认是私有的（隐藏了实现细节）
- 父级别和兄弟级别的项目总是可见的。
- 如果某个项对于 `foo` 是可见的，则对于 `foo` 的所有派生物来说，该项都是可见的。

### 路径（Paths）

路径通过以下方式进行解析：
1. 作为一个相对路径进行解析：
    - `foo` 或者 `self::foo` 指向当前模块中的 `foo`
    - `super::foo` 指向父模块中的 `foo`
2. 作为一个绝对路径进行解析：
    - `crate:foo` 指向当前单元包（crate）的根目录中的 `foo`
    - `bar::foo` 指向名为 `bar` 的单元包（crate）中的 `foo`

### 文件系统层次结构

```rust
mod garden;
```

上面的代码会告诉 Rust 在 `src/garden.rs` 中寻找 `garden` 这个模块。类似地，Rust 会在 `src/garden/vegetables.rs` 中寻找 `garden::vegetables` 模块。

单元包（crate）的 `crate` 根目录在：
- `src/lib.rs`：对于库单元包（library crate）
- `src/main.rs`：对于二进制单元包（binary crate）

**注意**：
- 在 Rust 2018 之前，模块需要位于 `module/mod.rs` 中，而不是 `module.rs` 中，而且在 Rust 2018 之后，这依然是一个可用的替代方案。
- 之所以引入 `filename.rs` 来替代 `filename/mod.rs` 是因为 IDE 很难区分大量的 `mod.rs` 文件。

也可以指定如下的配置，来修改 Rust 编译器寻找模块的路径：
```rust
#[path = "some/path.rs"]
mod some_module;
```

### [Re-exports](https://doc.rust-lang.org/nightly/rustdoc/write-documentation/re-exports.html)

假设我们正在编写名为 `lib` 的一个库，其中涉及了一些类型（`Foo`、`AnotherFoo`）定义在下面两个子模块中：
```rust
pub mod sub_module1 {
    pub struct Foo;
}
pub mod sub_module2 {
    pub struct AntoherFoo;
}
```

用户可以通过下面的方式使用：
```rust
use lib::sub_module1::Foo;
use lib::sub_module2::AnotherFoo;
```

假如我们希望这两个类型在单元包根目录可用，但是又不希望这两个模块对用户是可见的，该怎么办呢？可以通过 re-exports 实现：
```rust
// `sub_module1` and `sub_module2` are not visible outside.
mod sub_module1 {
    pub struct Foo;
}
mod sub_module2 {
    pub struct AnotherFoo;
}
// We re-export both types
pub use crate::sub_module1::Foo;
pub use crate::sub_module2::AnotherFoo;
```

现在用户可以这样使用它们：
```rust
use lib::{Foo, AnotherFoo}
```

并且因为 `sub_module1` 和 `sub_module2` 是私有的，用户并没有导入它们。

## trait：定义共享行为

> Rust 中的 trait 被用来向编译器描述某些特定类型拥有的且能够被其他类型共享的功能，它使我们以一种抽象的方式来定义共享行为。我们还可以使用 trait 约束来将泛型参数指定为实现了某些特定行为的类型。

**注意**：trait 与其他语言中的接口（interface）功能类似，但是也不完全相同。

```rust
struct Dog {
    name: String,
    age: i8,
}
struct Cat {
    lives: i8,
} // No name needed, cats won't respond anyway

trait Pet {
    fn talk(&self) -> String;
}

impl Pet for Dog {
    fn talk(&self) -> String {
        format!("Woof, my name is {}!", self.name)
    }
}

impl Pet for Cat {
    fn talk(&self) -> String {
        String::from("Miau!")
    }
}
```

例如对于上面的代码，我们通过 `trait Pet` 来定义了所有宠物都共享的行为（方法），这里对应的是 `talk`。

然后我们可以通过 `impl <Trait>` 来为每个类型实现对应的 trait，实现之后，对应的类型就可以调用对应 trait 中的方法了。

### trait 约束（bounds）
trait 也可以用作函数参数、返回值的类型约束，如：
```rust
// 约束参数 `x` 必须实现了 `Into<i32>` trait
fn add_42_millions(x: impl Into<i32>) -> i32 {
    x.into() + 42_000_000
}

// 约束类型 `T` 必须实现了 `Clone` trait
fn duplicate<T: Clone>(a: T) -> (T, T) {
    (a.clone(), a.clone())
}
```

### 默认方法

在定义 trait 时，如果没有默认实现某个方法，则该方法是 required methods，某个类型实现该 trait 时，就必须对 required methods 进行实现；如果某个方法有默认实现，则该方法是 provided methods 或 optional methods，某个类型实现该 trait 时，可以选择使用它默认实现的方法或者重写。

可以基于某一个 trait 作为 super trait，来实现另一个 trait：
```rust
trait Equals {
    fn equals(&self, other: &Self) -> bool;
}

// 基于 `Equals` 将其作为 super trait，来实现 `NotEquals`
trait NotEquals: Equals {
    fn not_equals(&self, other: &Self) -> bool {
        !self.equals(other)
    }
}
```

### 覆盖实现（blanket implementation）
可以为实现了某个 trait 的类型有条件地实现另一个 trait。对满足 trait 约束的所有类型实现 trait 也被称作覆盖实现（blanket implementation），这一机制被广泛地应用于 Rust 标准库中。例如，标准库对所有满足 `Display` trait 约束的类型实现了 `ToString` trait，对应代码如下所示：
```rust
impl <T: Display> ToString for T {
    ...
}
```
上面的语句也可以用 `where` 语句表示，如：
```rust
impl <T> ToString for T
where
    T: Display
{
    ...
}
```

### 一些重要的 trait

- `Iterator`：迭代器相关的处理。需要实现 `next` 方法，提供了 `count`、`last`、`nth`、`step_by`、`map`、`enumerate`、`collect` 等方法。
    - `IntoIterator`：将一个类型转换为 `Iterator`。需要实现 `into_iter` 方法。`for` 循环语法是基于 `IntoIterator` 实现的。
    - 参考 [What is the difference between iter and into_iter?](https://stackoverflow.com/questions/34733811/what-is-the-difference-between-iter-and-into-iter)，`iter`、`into_iter` 和 `iter_mut` 的区别：
        - `iter`：按照惯例，返回 `&T`。当希望只读地看一下数据时，使用 `iter`。
        - `iter_mut`：按照惯例，返回 `&mut T`。当希望修改数据时，使用 `iter_mut`。
        - `into_iter`：根据不同的上下文，可能返回 `T`、`&T` 或者 `&mut T`。当希望给元素一个新的所有者时，使用 `into_iter`。
- `FromIterator`：用于描述如何从一个迭代器创建对应的（容器）类型。`Iterator::collect()` 的底层就是通过 `FromIterator` 实现的。
- `From`、`Into`：用于类型转换，定义了 A 类型的 `From` B 之后，就自动实现了 B 类型的 `Into` A。
- `Read`, `Write`：读写相关的处理。
    - `Read`：需要实现 `read` 方法。提供了 `read_to_end`、`read_to_string` 等方法。
    - `Write`：需要实现 `write`、`flush` 方法。提供了 `write_all` 等方法。
- `Drop`：此处指 `std::ops::Drop`，当所有者离开作用域后时调用。需要实现 `drop` 方法。
- `Default`：用于给一个类型指定默认值。需要实现 `default` 方法。可以通过 `#[derive(Default)]` 直接派生。
- `std::ops`：如 `Add`、`Mul` 等，可以对类型实现这些 trait，从而实现 `+`、`*` 等运算符的重载。
- Closures: 函数或 lambda 表达式没有具体名称的类型，但是它们实现了 `Fn`, `FnMut`, `FnOnce` 这些 traits。

### [在 trait 的定义中使用关联类型（associated types）指定占位类型（placeholder types）类型](https://doc.rust-lang.org/book/ch19-03-advanced-traits.html#specifying-placeholder-types-in-trait-definitions-with-associated-types)

关联类型（associated type）是 trait 中的类型占位符，它可以被用于 trait 的方法签名中。

trait 的实现者需要根据特定的场景来为关联类型指定具体的类型。通过这一技术，我们可以定义出包含某些类型的 trait，而无须在实现前确定它们的具体类型。

标准库中的 `Iterator` 是一个带有关联类型的 trait 示例：
```rust
// 代码示例 19-12
pub trait Iterator {
    type Item;

    fn next(&mut self) -> Option<Self::Item>;
}
```

`Iterator` 中包含一个名为 `Item` 的关联类型，并使用该类型来替代迭代中出现的值类型。`Iterator` trait 的实现者需要为 `Item` 指定具体的类型，并在实现的 `next` 方法中返回一个包含该类型值的 `Option`。

**看上去 trait 中的关联类型与泛型的概念有些类似，泛型允许我们在不指定具体类型的前提下定义函数。那么我们为什么需要使用关联类型呢？**

为了说明它们的差别，我们来看这样一个例子：假设我们需要给泛型参数为 `u32` 的 `Counter` 类型 实现 `Iterator` trait，代码可以如下：
```rust
impl Iterator for Counter {
    type Item = u32;

    fn next(&mut self) -> Option<Self::Item> {
        // --snip--
```

如果 `Iterator` trait 按照泛型去定义，将是下面这样：
```rust
// 代码示例 19-13
pub trait Iterator<T> {
    fn next(&mut self) -> Option<T>;
}
```

如果使用代码示例 19-13 这种泛型的方式去定义 `Iterator` trait，我们就必须在每次实现 trait 的时候都注明类型，如 `impl Iterator<u32> for Counter`，或者 `impl Iterator<String> for Counter`，或者其他任意类型。也就是说，我们会对 `Counter` 实现多份 `Iterator`，每个具体的类型一份；在调用 `Counter` 的 `next` 方法时，也需要指定具体的类型注解，这样才能知道调用的是哪一份 `Iterator` 实现。

而通过关联类型实现 trait 的话，我们不需要额外指定类型注解，因为每个类型的对应 trait 实现只有一种，只能有一种 `impl Iterator for Counter` 的实现，`Counter` 也只拥有一个特定的 `Item` 类型；在调用 `Counter` 的 `next` 方法时，也不需要指定 `u32` 这样的类型注解。

关联类型也是 trait 规范用法的一部分，trait 的实现者需要将对关联类型的名称、描述写到 API 文档里。

### 默认泛型参数和运算符重载

我们可以在使用泛型参数时为泛型（generic type）指定一个默认的具体类型（default concrete type）。当使用默认类型就能工作时，该 trait 的实现者可以不用再指定另外的具体类型。可以在定义泛型时通过语法 `<PlaceholderType=ConcreteType>` 来为泛型指定默认类型。

这个技术常常被用在运算符重载中：
```rust
#[derive(Debug, Copy, Clone)]
struct Point {
    x: i32,
    y: i32,
}

// use default type parameter: `Self`, which will be the type we’re implementing `Add` on.
// See the `Add` trait definition: `pub trait Add<Rhs = Self> {...}`
impl std::ops::Add for Point {
    // the associated type name is 'Output', which is defined by the 'Add' trait
    type Output = Self;

    fn add(self, rhs: Self) -> Self {
        Self {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
        }
    }
}

// Set the `Rhs` type parameter to `(i32, i32)` instead of using the default of `Self`.
impl std::ops::Add<(i32, i32)> for Point {
    type Output = Point;

    fn add(self, rhs: (i32, i32)) -> Point {
        Point {
            x: self.x + rhs.0,
            y: self.y + rhs.1,
        }
    }
}

// Operator overloading
pub fn operator_overloading() {
    let p1 = Point { x: 10, y: 20 };
    let p2 = Point { x: 100, y: 200 };
    println!("{:?} + {:?} = {:?}", p1, p2, p1 + p2);

    let p3 = (5, 5);
    println!("{:?} + {:?} = {:?}", p1, p3, p1 + p3);
}
```

如上所示，`Add` trait 的定义 `pub trait Add<Rhs = Self> {...}` 中，默认类型参数为 `Self`，表示就是对某个类型实现 `Add` 时的那个类型；如果我们希望 `Point` 能和一个 Tuple `(i32, i32)` 做运算，可以通过指定 `Add` 的类型参数 `impl std::ops::Add<(i32, i32)> for Point` 来实现。

### 闭包（closures）的 trait

闭包或者 lambda 表达式没有可以被命名的类型，但是它们实现了 `Fn`、`FnMut`、`FnOnce` 等 traits。

- `Fn`：既不消耗也不修改捕获到的值，甚至有可能不捕获值。它可以被并发地调用多次。`Fn` 是 `FnMut` 和 `FnOnce` 的子类型。
- `FnMut`：可能会修改捕获到的值（如 `accumulate`）。它可以被调用多次，但是无法并发地调用。`FnMut` 是 `FnOnce` 的子类型。
- `FnOnce`：只能调用一次，它可能会消耗捕获到的值。

## 错误处理（Error Handling）

在 Rust 中，错误处理遵循以下流程：
- 可能发生错误的函数，在返回值中列出错误处理
- 没有例外

根据[官方文档](https://doc.rust-lang.org/book/ch09-00-error-handling.html)，Rust 将错误分为两大类：
- 可恢复的错误（recoverable errors）：一般希望将错误报告给用户并且重试操作等，如 `file not found error`
- 不可恢复的错误（unrecoverable errors）：通常是程序中的 bug 导致的，一般希望立即终止程序运行，如数组访问越界

### Panics

如果运行时发生错误，Rust 会触发一个 panic。

如以下的代码：
```rust
fn main() {
    let v = vec![10, 20, 30];
    println!("v[100]: {}", v[100]);
}
```

运行时报错：
```log
thread 'main' panicked at src/error_handling.rs:3:29:
index out of bounds: the len is 3 but the index is 100
note: run with `RUST_BACKTRACE=1` environment variable to display a backtrace
```

Panic 是专门用来描述不可恢复的（unrecoverable）和不符合预期的（unexpected）错误。

可以使用 `panic::catch_unwind` 来捕获 panic 错误，一般不推荐使用，也不一定能捕捉所有的 panic 错误：
```rust
use std::panic;

fn main() {
    let result = panic::catch_unwind(|| {
        println!("hello!");
    });
    assert!(result.is_ok());
    
    let result = panic::catch_unwind(|| {
        panic!("oh no!");
    });
    assert!(result.is_err());
}
```

请教了身边 Rust 经验最丰富的同事，他是这样理解的，私以为通俗易懂：
> Rust 的错误处理原则是，尽可能通过错误码(也就是Result)传递错误，因为这种会在编译时提示错误处理，符合显式api的设计原则，性能也是最优的。catch_unwind这个相当于开了个后门， 给那种出现任何错误都不想重启的场景提供个方案。

[To `panic!` or Not to `panic!`, that is a question.](https://doc.rust-lang.org/book/ch09-03-to-panic-or-not-to-panic.html)

### Backtrace

> A backtrace is a list of all the functions that have been called to get to this point. Backtraces in Rust work as they do in other languages: the key to reading the backtrace is to start from the top and read until you see files you wrote.

```log
$ RUST_BACKTRACE=1 cargo run
thread 'main' panicked at 'index out of bounds: the len is 3 but the index is 99', src/main.rs:4:5
stack backtrace:
   0: rust_begin_unwind
             at /rustc/e092d0b6b43f2de967af0887873151bb1c0b18d3/library/std/src/panicking.rs:584:5
   1: core::panicking::panic_fmt
             at /rustc/e092d0b6b43f2de967af0887873151bb1c0b18d3/library/core/src/panicking.rs:142:14
   2: core::panicking::panic_bounds_check
             at /rustc/e092d0b6b43f2de967af0887873151bb1c0b18d3/library/core/src/panicking.rs:84:5
   3: <usize as core::slice::index::SliceIndex<[T]>>::index
             at /rustc/e092d0b6b43f2de967af0887873151bb1c0b18d3/library/core/src/slice/index.rs:242:10
   4: core::slice::index::<impl core::ops::index::Index<I> for [T]>::index
             at /rustc/e092d0b6b43f2de967af0887873151bb1c0b18d3/library/core/src/slice/index.rs:18:9
   5: <alloc::vec::Vec<T,A> as core::ops::index::Index<I>>::index
             at /rustc/e092d0b6b43f2de967af0887873151bb1c0b18d3/library/alloc/src/vec/mod.rs:2591:9
   6: panic::main
             at ./src/main.rs:4:5
   7: core::ops::function::FnOnce::call_once
             at /rustc/e092d0b6b43f2de967af0887873151bb1c0b18d3/library/core/src/ops/function.rs:248:5
note: Some details are omitted, run with `RUST_BACKTRACE=full` for a verbose backtrace.
```

### 结构化的错误处理

Rust 推荐使用 `Result` 处理各种异常错误。

`Result` 必须被使用，`Result` 被标记为了 `#[must_use]` 属性，如果忽略了 `Result` 的处理，编译器会报告警告。

处理 `Result` 的代码样例：
```rust
#[derive(Debug)]
enum Version { Version1, Version2 }
fn parse_version(header: &[u8]) -> Result<Version, &'static str> {
    match header.get(0) {
        None => Err("invalid header length"),
        Some(&1) => Ok(Version::Version1),
        Some(&2) => Ok(Version::Version2),
        Some(_) => Err("invalid version"),
    }
}

let version = parse_version(&[1, 2, 3, 4]);
match version {
    Ok(v) => println!("working with version: {v:?}"),
    Err(e) => println!("error parsing header: {e:?}"),
}
```

如果你不想处理错误，可以在最后使用 `expect` 进行断言，如果运行正常，就返回 `Ok` 中的值；如果出现错误，就会触发一个 panic：
```rust
let x: Result<u32, &str> = Err("emergency failure");
x.expect("Testing expect"); // panics with `Testing expect: emergency failure`
```

`unwrap` 与 `expect` 类似，会把 `Ok` 或者 `Err` 中的值解出来，如果是 `Err`，会触发 panic，错误信息来自 Err。`expect` 的 panic 错误信息是通过参数指定的。

因为 `Result` 的处理代码比较范荣，Rust 也提供了一个 `?` 来简化写法，如：
```rust
// expression?
match expression {
    Ok(value) => value,
    Err(err)  => return Err(From::from(err)),
}
```

如果在一个返回 `Result` 的表达式末尾使用 `?`，则相当于使用了一个 match 表达式
- 如果发生了错误，则相当于进入 match 表达式的 `Err(err)` 分支，并提前 `return Err(From::from(err))`。
- 如果运行成功，则相当于进入 match 表达式的 `Ok(ok)` 分支。

## 测试（Testing）

Rust 和 Cargo 提供了简单的单元测试框架：
- 开发代码中直接支持写单元测试（unit test）
- 可以将集成测试（integration test）放在  `tests/` 目录下

### 单元测试（unit test）

可以通过 `#[test]` 来支持单元测试：
```rust
fn first_word(text: &str) -> &str {
    match text.find(' ') {
        Some(idx) => &text[..idx],
        None => &text,
    }
}

#[test]
fn test_empty() {
    assert_eq!(first_word(""), "");
}

#[test]
fn test_single_word() {
    assert_eq!(first_word("Hello"), "Hello");
}

#[test]
fn test_multiple_words() {
    assert_eq!(first_word("Hello World"), "Hello");
}
```

然后运行 `cargo test` 即可找到并执行上面的测试代码。

### 测试模块

单元测试代码也嵌入到一个模块中，如：
```rust
fn helper(a: &str, b: &str) -> String {
    format!("{a} {b}")
}

pub fn main() {
    println!("{}", helper("Hello", "World"));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_helper() {
        assert_eq!(helper("foo", "bar"), "foo bar");
    }
}
```

这种方式可以用来测试私有的函数，如上面的 `helper`。

`#[cfg(test)]` 属性表示只有运行 `cargo test` 时，对应的模块才是激活的。

### 文档测试（documentation tests）

Rust 内置支持了文档测试：

```rust
/// Shortens a string to the given length.
///
/// ```
/// # use playground::shorten_string;
/// assert_eq!(shorten_string("Hello World", 5), "Hello");
/// assert_eq!(shorten_string("Hello World", 20), "Hello World");
/// ```
pub fn shorten_string(s: &str, length: usize) -> &str {
    &s[..std::cmp::min(length, s.len())]
}
```

`///` 注释中的代码块会被编译器认为是 Rust 代码，会在 `cargo test` 时执行。

使用 [Rust Playground](https://play.rust-lang.org/?version=stable&mode=debug&edition=2021&gist=3ce2ad13ea1302f6572cb15cd96becf0) 可以测试成功，但是本地运行 `cargo test` 暂时没有验证成功。


### 集成测试（integration tests）

如果你希望作为一个客户端来测试你写的库，可以使用集成测试：

可以在 `tests/` 下创建 `.rs` 文件，如：

```rust
use my_library::init;

#[test]
fn test_init() {
    assert!(init().is_ok());
}
```

这些测试只能访问单元包中的公开 API。


## Unsafe Rust

Rust 语言包含两部分：
- **Safe Rust**：内存安全，没有可能的未定义行为
- **Unsafe Rust**：如果违反先决条件，可能会触发未定义的行为。

不安全代码（unsafe code）通常比较小且孤立，而且应该通过文档说明它的正确性。不安全代码通常被封装在安全的抽象层中。

Unsafe Rust 提供了以下五个能力：
- 对裸指针（raw pointer）进行解引用（dereference）
- 访问或者修改可变的静态变量
- 访问 `union` 的字段
- 调用 `unsafe` 的函数，包括 `extern` 的函数
- 实现 `unsafe` traits

Unsafe Rust 并不代表代码不正确，而是说开发者关闭了编译器的安全性检查功能，不再强制执行内存安全的规则，然后靠他们自己来写正确的代码。
