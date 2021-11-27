import asyncio
from datetime import datetime


async def eternity():
    # sleep for an hour
    await asyncio.sleep(3600)
    print("yay!")


async def main():
    # wait for at most 1 second
    wait_time = 1.0
    # wait_time:
    #   * None: block until the future completes
    #   * float/int: wait for the time

    try:
        print(f"started at {datetime.utcnow().strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]}")
        await asyncio.wait_for(eternity(), timeout=wait_time)
    except asyncio.TimeoutError:
        print("timeout!")

    print(f"finished at {datetime.utcnow().strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]}")


asyncio.run(main())
