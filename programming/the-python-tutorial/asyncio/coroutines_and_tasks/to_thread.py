import asyncio
import time
from datetime import datetime


def blokcing_io():
    print(f"started blocking_io at {datetime.utcnow().strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]}")

    # any IO-bound operation
    time.sleep(1)

    print(f"finished blocking_io at {datetime.utcnow().strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]}")


async def main():
    print(f"started main at {datetime.utcnow().strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]}")

    other_task = asyncio.sleep(1)

    await asyncio.gather(
        asyncio.to_thread(blokcing_io),
        other_task,
    )

    print(f"finished main at {datetime.utcnow().strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]}")


asyncio.run(main())

# Expected output:
# started main at 2021-11-27 12:30:20.815
# started blocking_io at 2021-11-27 12:30:20.818
# finished blocking_io at 2021-11-27 12:30:21.821
# finished main at 2021-11-27 12:30:21.828
