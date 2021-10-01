# https://www.youtube.com/watch?v=Ks1pw1X22y4

state = 0b1001

for i in range(20):
    #print("{:04b}".format(state))
    print(state & 1, end="")
    newbit = state ^ (state >> 1) & 1
    state = (state >> 1) | (newbit << 3)

print("")

state = (1 << 127 ) | 1

for i in range(2000000):
    print(state & 1, end="")
    newbit = (state ^ (state >> 1) ^ (state >> 2) ^ (state >> 7)) & 1
    state = (state >> 1) | (newbit << 127)
