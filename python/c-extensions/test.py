import HelloC

HelloC.helloworld()

som = HelloC.add(13, 29)

print(som)

HelloC.simple_print("String One", "This is string two")

HelloC.print_complex(42 + 3.1415926j)

num = 40

print(f"Fibo({num}) = {HelloC.fib(num)}")
print(HelloC.version())

x = 1 + 1j

print(HelloC.mandelpixel(x, 100))

