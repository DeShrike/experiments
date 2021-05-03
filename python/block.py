import hashlib

class NeuralCoinBlock():
	def __init__(self, prev_block_hash, transaction_list):
		self.prev_block_hash = prev_block_hash
		self.transaction_list = transaction_list

		self.block_data = "-".join(self.transaction_list) + "-" + self.prev_block_hash
		self.block_hash = hashlib.sha256(self.block_data.encode()).hexdigest()

t1 = "Ann send 2 NC to Mike"
t2 = "Bob send 4.1 NC to Mike"
t3 = "Mike send 3 NC to Bob"
t4 = "John send 9 NC to Ann"
t5 = "Ann send 3.5 NC to John"
t6 = "Mike send 3 NC to Ann"

root = NeuralCoinBlock("ROOT", [t1, t2])

print(root.block_data)
print(root.block_hash)

block2 = NeuralCoinBlock(root.block_hash, [t3, t4])
print(block2.block_data)
print(block2.block_hash)

block3 = NeuralCoinBlock(block2.block_hash, [t5, t6])
print(block3.block_data)
print(block3.block_hash)

