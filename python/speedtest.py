import time
import math
from timeit import default_timer as timer

BRIGHTRED = u"\u001b[31;1m"
RESET = u"\u001b[0m"
INVERSE = u"\u001b[5m"

def int_test_real(max):
    result = 0
    for num in range(0, max):
        if (num % 3 == 0 or num % 5 == 0):
            result += num

    print("Sum is %s%d%s " % (BRIGHTRED, result, RESET))

def float_test_real(max):
    delta = 0.1
    angle = 0.0
    result = 0.0
    for num in range(max):
       result = result + math.sin(angle) + math.cos(angle)
       angle += delta

    print("Sum is %s%.4f%s " % (BRIGHTRED, result, RESET))

def int_test():
    int_test_real(10_000_000)

def float_test():
    float_test_real(10_000_000)

if __name__ == "__main__":
    print("%s *** PYTHON *** %s" % (INVERSE, RESET))

    print("Starting int_test")
    start = time.time()
    int_test()
    end = time.time()
    ellapsed = end - start
    print("Ellapsed: %s%.5f%s seconds" % (BRIGHTRED, ellapsed, RESET))

    print("")

    print("Starting float_test")
    start = time.time()
    float_test()
    end = time.time()
    ellapsed = end - start
    print("Ellapsed: %s%.5f%s seconds" % (BRIGHTRED, ellapsed, RESET))


# start = timer()
# DoIt()
# end = timer()
# ellapsed = end - start
# print("Ellapsed: %.5f seconds" % ellapsed)


# start = time.process_time()
# DoIt()
# end = time.process_time()
# ellapsed = end - start
# print("Ellapsed: %.5f seconds" % ellapsed)


