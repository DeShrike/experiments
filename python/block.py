import hashlib
import json

nullen = 6

class Transaction():
	def __init__(self):
		self.source:str = None
		self.destination:str = None
		self.amount:float = 1
		self.signature:str = None

class NatchCoinBlock():
	def __init__(self, prev_block_hash:str, payload:str):
		self.id:int = 0
		self.nonce:int = 0
		self.prev_block_hash:str = prev_block_hash
		self.payload:str = payload
		self.block_hash:str = None

	def __str__(self):
		return self.get_data() + "\r\n" + ("" if self.block_hash is None else self.block_hash)

	def get_data(self):
		d = {
			"id": self.id,
			"nonce": self.nonce,
			"payload": self.payload,
			"prev_block_hash": self.prev_block_hash
		}
		return json.dumps(d)

def Mine(block:NatchCoinBlock) -> str:
	nonce = 1
	nuls = "0" * nullen
	while True:
		if nonce % 1000 == 0:
			print(f"{nonce}  ", end = "\r")
		block.nonce = nonce
		data = block.get_data()
		block_hash = hashlib.sha256(data.encode()).hexdigest()

		if block_hash[0:nullen] == nuls:
			block.block_hash = block_hash
			break
		nonce += 1


root = NatchCoinBlock("NatchCoin ROOT", "")
Mine(root)

block2 = NatchCoinBlock(root.block_hash, "Payload 2")
Mine(block2)

block3 = NatchCoinBlock(block2.block_hash, "Payload 3")
Mine(block3)

block4 = NatchCoinBlock(block3.block_hash, "Payload 4")
Mine(block4)

block5 = NatchCoinBlock(block4.block_hash, "Payload 5")
Mine(block5)

print("-----------------------------------------------------")
print(root)
print("-----------------------------------------------------")
print(block2)
print("-----------------------------------------------------")
print(block3)
print("-----------------------------------------------------")
print(block4)
print("-----------------------------------------------------")
print(block5)

