# asyncI/O - Asynchronous I/O

**异步 I/O（Asynchronous I/O）**：当代码需要执行一个耗时的 I/O 操作时，它只发出 I/O 指令，并不等待 I/O 结果，然后就去执行其他代码了。一段时间后，当 I/O 返回结果时，再通知 CPU 进行处理。

异步 I/O 模型需要一个消息循环，在消息循环中，主线程不断地重复“读取消息-处理消息”这一过程：

```python
loop = get_event_loop()
while True:
    event = loop.get_event()
    process_event(event)
```

**协程（Coroutine）**：又称微线程，Python 3.7 之后引入，通过 `async/await` 语法声明。协程像是一个更通用的一种子程序（subroutines），可以在不同的节点进入、退出或者恢复。和多线程不同，协程运行在同一个线程里。

和多线程相比，协程的优势：
* 执行效率高，子程序切换没有线程切换的开销
* 不存在多线程锁的机制。

如何使用协程利用多核 CPU？最简单的方法是多进程+协程。

运行协程的方法：
* `asyncio.run()`：一般是作为执行协程最顶层的一个入口。
* `await <coro_object>`。`coro_object` 就是调用协程函数返回的对象。
* `asyncio.create_task()`：并行地执行协程

**Awaitables**：如果一个对象可以用 `await` 表达式，那它就是 awaitable。主要有协程、Task 和 Future 三种。

**Task** 可以通过 `asyncio.create_task()` 创建，用于规划调度协程的并发，创建的 Task 对象可以控制执行的进程（`cancel` 或者 `await` 等）。

**Future** 是一种特殊的 low-level awaitable 对象，用于表示一个异步操作的最终结果。一般情况下，在应用级别的代码中不需要创建 Future 对象。

## 参考资料
- [Python 官方文档 - asyncI/O — Asynchronous I/O](https://docs.python.org/3.10/library/asyncio.html)
- [廖雪峰 Python 教程 - 异步I/O](https://www.liaoxuefeng.com/wiki/1016959663602400/1017959540289152)
- [Real Python - Async I/O in Python: A Complete Walkthrough](https://realpython.com/async-I/O-python/)

