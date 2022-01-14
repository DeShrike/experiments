from random import Random
import random

def generate(seed: int, delta: int, message: str) -> bytearray:
   garbage = Random(5774667)
   random.seed(seed)
   result = bytearray()
   i = 0
   while i < len(message):
      c = message[i]
      if random.randrange(delta):
         result.append(random.randrange(256) ^ ord(c))
         i += 1
      else:
         result.append(garbage.randrange(256))
         #result.append(0)
   return result.hex().upper()

seed = 2022
message = "Happy New Year !"
delta = 4
data = generate(seed, delta, message)

code = f"""import random
random.seed({seed})
print("".join(chr(random.randrange(256) ^ c)
   for c in bytes.fromhex({repr(data)})
   if random.randrange({delta})))
"""

print("")
print(code)
print("")

random.seed(seed)
print("".join(chr(random.randrange(256) ^ c)
   for c in bytes.fromhex(data) 
   if random.randrange(delta)))

