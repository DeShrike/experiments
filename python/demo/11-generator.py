class first_n(object):
    def __init__(self, n):
        self.n = n
        self.num = 0

    def __iter__(self):
        return self

    def __next__(self):
        return self.next()

    def next(self):
        if self.num < self.n:
            cur, self.num = self.num, self.num + 1
            return cur
        raise StopIteration()

def firstn(n):
    num = 0
    while num < n:
        yield num
        num += 1

def main():
    sum_of_first_n = sum(first_n(1_000_000))
    print(sum_of_first_n)

    sum_of_first_n = sum(firstn(1_000_000))
    print(sum_of_first_n)

    print(firstn(10))
    print(list(firstn(10)))


if __name__ == "__main__":
    main()
