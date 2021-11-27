import asyncio
import time


async def say_after(delay, what):
    await asyncio.sleep(delay)
    print(what)


async def fun1():
    print(f"started fun1 at {time.strftime('%X')}")

    await say_after(1, "hello")
    await say_after(2, "world")

    print(f"finished fun1 at {time.strftime('%X')}")


async def fun2():
    # schedule tasks to run soon concurrently
    task1 = asyncio.create_task(say_after(1, "hello"))
    task2 = asyncio.create_task(say_after(2, "world"))
    # tasks already executed!

    print(f"started fun2 at {time.strftime('%X')}")

    # here sleep for 1 second does not delay the tasks
    await asyncio.sleep(1)

    # the task object can be used to cancel or wait to complete

    # Wait until both tasks are completed (should take
    # around 2 seconds.)
    await task1
    await task2

    print(f"finished fun2 at {time.strftime('%X')}")


if __name__ == "__main__":
    asyncio.run(fun1())
    # started fun1 at 11:40:39
    # hello
    # world
    # finished fun1 at 11:40:42

    asyncio.run(fun2())
    # started fun2 at 11:40:42
    # hello
    # world
    # finished fun2 at 11:40:44
