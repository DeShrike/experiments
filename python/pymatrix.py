import curses
from curses import wrapper
import random

"""
A_ALTCHARSET
A_BLINK
A_BOLD
A_DIM
A_INVIS
A_ITALIC
A_NORMAL
A_PROTECT
A_REVERSE
A_STANDOUT
A_UNDERLINE
A_HORIZONTAL
A_LEFF
A_RIGHT
A_TOP
A_VERTICAL
A_CHARTEXT
"""

class PyMatrix():

    def __init__(self, stdscr):
        self.stdscr = stdscr

        self.colors = [
            curses.COLOR_GREEN,
            curses.COLOR_BLUE,
            curses.COLOR_RED,
            curses.COLOR_YELLOW,
            curses.COLOR_CYAN,
            curses.COLOR_MAGENTA,
            curses.COLOR_WHITE,
        ]

        self.current_color = 0
        self.running = True
        self.random_colors = False
        self.height = 0
        self.width = 0

        for ix, col in enumerate(self.colors):
            curses.init_pair(ix + 1, col, curses.COLOR_BLACK)

        self.height, self.width = stdscr.getmaxyx()

        self.columns = [self.init_column() for _ in range(self.width - 1)]

        self.debug_message = None
        curses.init_pair(len(self.colors) + 1, curses.COLOR_BLACK, curses.COLOR_YELLOW)
        self.debug_pair = curses.color_pair(len(self.colors) + 1)

        # self.debug_message = f"Width: {self.width} - Height: {self.height}"

    def init_column(self):
        # [y-pos, length, colorpair]
        if self.random_colors:
            rc = random.randint(0, len(self.colors) - 1)
            pair = curses.color_pair(rc + 1)
        else:
            pair = curses.color_pair(self.current_color + 1)

        return [
            random.randint(-15, -5),
            random.randint(5, self.height - 3),
            pair
        ]

    def render_column(self, c: int):
        pos, l, pair = self.columns[c]
        if pos - l > self.height:
            self.columns[c] = self.init_column()
            return
        r = min(self.height - 1, pos)
        while r > pos - l and r >= 0:
            letter = chr(96 + random.randint(1, 26))
            attr = pair | (curses.A_BOLD if r == pos else 0)
            if r >= pos - 1:
                self.stdscr.addstr(r, c, letter, attr)
            elif r == pos - l + 1:
                self.stdscr.addstr(r, c, " ")
            r -=  1

    def advance(self):
        for ix, c in enumerate(self.columns):
            self.columns[ix][0] = c[0] + 1

    def show_debug(self):
        if self.debug_message is not None:
            self.stdscr.addstr(self.height - 1, 0, self.debug_message, self.debug_pair)

    def render(self):
        #self.stdscr.clear()

        for c in range(0, self.width - 1, 2):
            self.render_column(c)

        self.show_debug()

        self.stdscr.refresh()

    def next_color(self):
        self.current_color = (self.current_color + 1) % len(self.colors)

    def run(self):
        self.stdscr.nodelay(1) # set getch() non-blocking
        curses.curs_set(False)
        while self.running:
            self.render()
            self.advance()

            k = self.stdscr.getch()
            if k == ord("q"):
                self.running = False
            elif k == ord("r"):
                self.random_colors = not self.random_colors
            elif k == ord("c"):
                self.next_color()

            curses.napms(50)

        curses.curs_set(True)

def start(stdscr):
    matrix = PyMatrix(stdscr)
    matrix.run()

if __name__ == "__main__":
    wrapper(start)
