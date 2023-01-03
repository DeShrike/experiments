import ctypes

clibrary = ctypes.CDLL("./example.so")

result = clibrary.sum(10,20)
print(result)


clibrary.test(b"John", 55)

func = clibrary.test

func.argtypes = [ctypes.c_char_p, ctypes.c_int]
func.restype = ctypes.c_char_p

a = func(b"Bob", 44)
print(a)

