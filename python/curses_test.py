import curses
from curses import wrapper
from curses.textpad import Textbox, rectangle

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

def main(stdscr):
    curses.init_pair(1, curses.COLOR_BLUE, curses.COLOR_YELLOW)
    curses.init_pair(2, curses.COLOR_RED, curses.COLOR_BLACK)

    counter_win = curses.newwin(6, 30, 5, 10)

    stdscr.clear()

    for i in range(10):
        stdscr.addstr(i, i, f"Hello {i}", curses.color_pair(1))
        stdscr.addstr(i, i + 10, f"Hello {i}", curses.color_pair(2))
        stdscr.addstr(i, i + 20, f"Hello {i}", curses.color_pair(2) | curses.A_BOLD)
        stdscr.addstr(i, i + 30, f"Hello {i}", curses.A_LEFT)

    counter_win.addstr(1, 1, "Hello There")
    counter_win.refresh()

    rectangle(stdscr, 15, 5, 5, 20)

    stdscr.refresh()
    stdscr.getch()

if __name__ == "__main__":
    wrapper(main)
