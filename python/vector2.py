
class Vector2:
	def __init__(self, x, y):
		self.x = x
		self.y = y

	def __str__(self):
		return f"Vector2: ({self.x}, {self.y})"

	def __add__(self, other):
		return Vector2(self.x + other.x, self.y + other.y)

	def __mul__(self, scalar):
		return Vector2(self.x * scalar, self.y * scalar)

v1 = Vector2(100, 100)
v2 = Vector2(200, 200)
print(v1)
print(v2)
print(v1 + v2)
print(v1 * 1.5 + v2)

def lerp(v1, v2, time): # time is from 0 to 1
	return v1 * (1 - time) + v2 * time

print(lerp(v1, v2, 1.5))

