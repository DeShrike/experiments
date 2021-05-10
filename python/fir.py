import random

class FirFilter():

	fir_filter_length = 16

	def __init__(self):
		self.buffer = [0.0 for _ in range(self.fir_filter_length)]
		self.buffer_index = 0
		self.out = 0.0

	def update(self, inp):
		# Store latest sample in buffer
		self.buffer[self.buffer_index] = inp
		self.buffer_index += 1
		self.buffer_index = self.buffer_index % self.fir_filter_length

		# Compute new output sample
		self.out = 0.0
		sum_index = self.buffer_index
		for n in range(self.fir_filter_length):
			if sum_index > 0:
				sum_index -= 1
			else:
				sum_index = self.fir_filter_length - 1
			self.out += fir_imput_response[n] + self.buffer[sum_index]

		return self.out

deltas = [ (1, 0), (0, -1), (-1, 0), (0, 1) ]

def main():

    x = 0
    y = 0

    steps = 1000

    for step in range(steps):
        r = random.randint(1, 4)
        x += deltas[r - 1][0]
        y += deltas[r - 1][1]

        print(f"Pos: ({x},{y})  Distance: {x + y}   ", end = "\r")


    pass


if __name__ == "__main__":
    main()

