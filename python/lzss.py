# Lempel-Ziv-Storer-Szymanski (LZSS)

sliding_window = 14
look_ahead_buffer = 4
escape = "/"

text = "LZSS is a dictionary coding technique. It attempts to replace a string of symbols with a reference to a dictionary location of the same string."

def compress(data: str):
   buffer = [None] * sliding_window + list(text)
   result = []

   return result

def uncompress(data) -> str:
   return "X"

def main():
   print(text)
   print(f"Length: {len(text)}")

   compressed = compress(text)

   print(compressed)
   print(f"Length: {len(compressed)}")

   uncompressed = uncompress(compressed)

   print(uncompressed)
   print(f"Length: {len(uncompressed)}")


if __name__ == "__main__":
   main()

