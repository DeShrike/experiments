import curses
from signal import signal, SIGTERM, pause
from collections import namedtuple
from threading import Thread
from time import sleep
from random import choice

game_on = False
point = namedtuple("point", "y x")
block_char = "\u2588"
keyboard_on = True

directions = {
    curses.KEY_UP: point(-1, 0),
    curses.KEY_DOWN: point(1, 0),
    curses.KEY_RIGHT: point(0, 1),
    curses.KEY_LEFT: point(0, -1),
}

def safe_exit():
    exit(1)

def start_game():
    global snake, game, game_on, bearing

    game_area.clear()

    bearing = choice(list(directions))

    snake = [point(terminal_y // 2, terminal_x // 2)]
    game_area.addstr(snake[0].y, snake[0].x, block_char)

    game_area.border()
    game_area.refresh()

    gameover_popup.addstr(1,1, "Game Over !")
    gameover_popup.addstr(2,1, "Press Space Bar to Play Again")
    gameover_popup.border()

    game_on = True
    game = Thread(target = play, daemon = True)
    game.start()


def play():
    global keyboard_on
    try:
        while game_on:
            move_snake()
        gameover_popup.refresh()
        
    except Exception as e:
        keyboard_on = False
        curses.endwin()
        print(f"Unexpected error: {e}")

def move_snake():
    global game_on
    sleep(0.1)

    new_location = point(snake[0].y + directions[bearing].y, snake[0].x + directions[bearing].x)
    snake.insert(0, new_location)

    game_area.addstr(new_location.y, new_location.x, block_char)
    game_area.addstr(snake[-1].y, snake[-1].x, " ")
    game_area.refresh()

    snake.pop(-1)

    if new_location.y in (0, terminal_y - 2) or new_location.x in (0, terminal_x - 1):
        game_on = False

try:
    signal(SIGTERM, safe_exit)

    terminal = curses.initscr()
    terminal_y, terminal_x = terminal.getmaxyx()

    if terminal_y < 20 or terminal_x < 50:
        raise RuntimeError

    curses.curs_set(0)
    curses.noecho()

    score_board = curses.newwin(1, terminal_x, 0, 0)
    game_area = curses.newwin(terminal_y - 1, terminal_x, 1, 0)
    game_area.keypad(True)
    game_area.timeout(50)

    gameover_popup = curses.newwin(4, 40, terminal_y // 2 - 1, terminal_x // 2 - 20)

    start_game()

    while keyboard_on:
        key = game_area.getch()
        if key in directions:
            bearing = key
        elif not game_on and key == 32:
            start_game()

except RuntimeError:
    curses.endwin()
    print("ERROR: Terminal window too small")
    print("At least 50x20 characters are required")
    print(f"Current terminal dimensions are: {terminal_x}x{terminal_y}")

finally:
    if game_on:
        game_on = False
        game.join()

    if not curses.isendwin():
        curses.endwin()


