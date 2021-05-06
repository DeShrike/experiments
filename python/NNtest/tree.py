import sys, os, fcntl, struct, termios, random, time

def draw_char(r, c, char):
    sys.stdout.write("\033[%d;%dH%s\033[1B" % (r, c, char))

def write_char(char):
    sys.stdout.write(char)

def clear():
    ROWS, COLS = size()
    sys.stdout.write("\033[1;1H" + "\n".join(" " * COLS for _ in range(ROWS)) + "\033[1;1H")

def reset():
    sys.stdout.write("\033[0m\033[40m")

def size():
    return struct.unpack('HHHH', fcntl.ioctl(0, termios.TIOCGWINSZ, struct.pack('HHHH', 0, 0, 0, 0)))[:2]

def progress_snow(snow, grid):
    snow[:] = [(particle[0] + 1, particle[1]) for particle in snow]
    ROWS, COLS = size()
    r = list(range(COLS))
    random.shuffle(r)
    for i in r[-COLS // 40:]:
        snow.append((1, i + 1))
    snow[:] = [particle for particle in snow if 0 < particle[0] <= ROWS and 0 < particle[1] <= COLS]
    for particle in snow:
        grid[particle[0] - 1][particle[1] - 1] = "\033[1;37m*\033[0m"

ornaments = {}
types = {}
_r, _c = size()

def draw_tree(grid):
    global ornaments, types, _r, _c
    ROWS, COLS = size()
    if (ROWS, COLS) != (_r, _c):
        _r, _c = ROWS, COLS
        ornaments = {}
        types = {}
    if ROWS < 5: return
    center = COLS // 2
    grid[-1][center - 1] = grid[-1][center + 1] = "\033[1;30m|\033[0m"
    hbound = COLS - (COLS % 1) // 2
    height = min(ROWS * 2 // 3, hbound * 2 // 3 + (hbound % 2)) - 1
    grid[~height][center] = "\033[1;31m*\033[0m"
    offset = 0
    for i in range(1, height - 1):
        grid[~height + i][center + ~offset] = "\033[32m/\033[0m"
        grid[~height + i][center - ~offset] = "\033[32m\\\033[0m"
        if ~height + i in ornaments:
            r = ornaments[~height + i]
        else:
            r = list(range(center - offset, center + offset + 1))
            random.shuffle(r)
            ornaments[~height + i] = r = r[:offset * 2 // 5]
            types[~height + i] = {}
        for j in range(center - offset, center + offset + 1):
            if j in r:
                if j in types[~height + i]:
                    t = types[~height + i][j]
                else:
                    t = types[~height + i][j] = (random.random() < 0.5) + 2 * (random.random() < 0.5)
                grid[~height + i][j] = ["\033[1;33m*", "\033[1;31m@", "\033[1;34m@", "\033[1;36m@"][t] + "\033[0m"
            else:
                grid[~height + i][j] = " "
        if (height - i) % 3 != 1:
            offset += 1
    for j in range(2 * offset + 1):
        grid[-2][center - offset + j] = "\033[32m-\033[0m"

snow = []
while True:
    clear()
    ROWS, COLS = size()
    grid = [[' '] * COLS for _ in range(ROWS)]
    progress_snow(snow, grid)
    draw_tree(grid)
    sys.stdout.write("\n".join(map("".join, grid)))
    sys.stdout.flush()
    time.sleep(0.5)

