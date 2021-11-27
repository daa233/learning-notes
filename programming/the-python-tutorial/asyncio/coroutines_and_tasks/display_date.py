import asyncio
import datetime


async def display_date():
    loop = asyncio.get_running_loop()
    # `loop.time()` returns the time (float, in seconds) according to the event loop's clock.
    end_time = loop.time() + 5.0
    while True:
        print(datetime.datetime.now())
        if (loop.time() + 1.0) >= end_time:
            break
        # suspends the current task, allowing other tasks to run
        await asyncio.sleep(1)


asyncio.run(display_date())
