import asyncio

async def main():
    print("Hello")
    task = asyncio.create_task(foo("World"))
    await asyncio.sleep(2)
    # await task
    print("Done")

async def foo(text):
    print(text)
    await asyncio.sleep(1)

asyncio.run(main())

