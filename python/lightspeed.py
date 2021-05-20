import math

def main():
   a1 = 4 * math.pi * (10 ** -1)
   a2 = 8.8542 * (10 ** -12)
   a3 = 1 / (a1 * a2)
   c = math.sqrt(a3)
   print(f"Speed of Light = {c} km/sec")

if __name__ == "__main__":
   main()

