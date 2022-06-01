from functools import cache
import time

def benchmark(func):
    def wrapper(*args, **kwargs):
        t = time.perf_counter()
        res = func(*args, **kwargs)
        print(func.__name__, time.perf_counter() - t, "seconds")
        return res
    return wrapper

def logging(func):
    def wrapper(*args, **kwargs):
        res = func(*args, **kwargs)
        print(func.__name__, args, kwargs)
        return res
    return wrapper

def counter(func):
    counter.counts = {}
    counter.counts[func.__name__] = 0

    def wrapper(*args, **kwargs):
        counter.counts[func.__name__] += 1
        res = func(*args, **kwargs)
        return res

    counter.counts[func.__name__] = 0
    return wrapper

#@logging
@counter
#@cache
def fibonaci(num:int) -> int:
    if num <= 2:
        return 1
    return fibonaci(num - 1) + fibonaci(num - 2)

@benchmark
def main():
    a = fibonaci(35)
    print("fib(35) = ", a)
    print("Call counts: ", counter.counts)


if __name__ == "__main__":
    main()
