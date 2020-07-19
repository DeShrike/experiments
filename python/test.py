class A(object):

    id = 0

    def __init__(self, id):
        print("Creating A")
        A.id = id

    def hello(self):
        print(f"I am A - {self.id}")

class B(A):

    def __init__(self, id):
        print("Creating B")
        A.id = id

    def hello(self):
        print(f"I am B - {self.id}")


class C(A):

    def __init__(self, id):
        print("Creating C")
        A.id = id

    def hello(self):
        print(f"I am C - {self.id}")

aa = A(42)
print(type(aa))


bb = B(666)
print(type(bb))

aa.hello()
bb.hello()

print(A.id)
print(B.id)

aaa = A(2020)

print(A.id)






aa = A(1)
bb = B(2)
cc = C(3)

print(type(aa))
print(type(bb))
print(type(cc))



if type(aa) == type(bb):
    print("aa == bb")
else:
    print("aa is not bb")

if type(bb) == type(cc):
    print("bb == cc")
else:
    print("bb is not cc")
