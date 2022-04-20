import ctypes
import time
from sys import platform, stdout
from os import get_terminal_size

# https://www.sudokuwiki.org/sudoku.htm

game1 = [
    "65..74..1",    # 652974381
    ".13...47.",    # 813265479
    "..9.8..2.",    # 749183526
    "..83.7..2",    # 568317942
    "...5.6...",    # 194526738
    "2..8.91..",    # 237849165
    ".2..5.8..",    # 326451897
    ".75...21.",    # 975638214
    "4..79..53",    # 481792653
]

game2 = [
    "...7.....",
    "..4....2.",
    "57...64..",
    "...5....8",
    "..781..5.",
    "....73...",
    "....2...1",
    "259......",
    "..3...67.",
]

game3 = [
    "97.5...2.",
    ".3.......",
    "....9....",
    "....2457.",
    "..4...1.8",
    "...6.5...",
    "...7...92",
    "..6..984.",
    "24..5....",
]

game4 = [
    "1..2..345",
    ".2.....96",
    "..3.....7",
    "2..4.....",
    "....5....",
    ".....6..8",
    "3.....7..",
    "41.....8.",
    "567..8..9",
]

game5 = [
    "56......1",
    "....5..6.",
    "..783.4..",
    "..53.1...",
    "7.....2.6",
    "2....7.5.",
    "......53.",
    ".514.....",
    "4....2...",
]

# 852793164......279..92..5384....1623....3.845.8..4.917.2.3..7966......5......7.8.
# 8.2..3164......279..92..5384....1623....3.845.8..4.917.2.3..7966......5......7.8.
game6 = [
    "8....31.4",
    ".......7.",
    "..92.....",
    "4....16.3",
    "........5",
    ".8..4....",
    ".2.3..7.6",
    "6......5.",
    ".....7.8.",
]

game7 = [
    "....6........D.1",
    "6.A.....9.1C.E.4",
    "0.FD2A1.4......C",
    ".1.4......6..7A.",
    "1.....F..5......",
    ".A0BD...7.46.9..",
    "E..F....0.81..53",
    "..4.1..6...370.A",
    "..3....7.9.AB..0",
    "..75.D.2C....8..",
    "..CEAF43..2....9",
    ".F.8B......5A.7.",
    "...C5....0EF..6.",
    "D..9.BA.8....4..",
    "..2.4....A..C.D.",
    ".....0.F2DB.9...",
]

game8 = [
    "......8..C....4.",
    "....B...34..A86.",
    "....CD.9..6F...B",
    ".7....A.EB.D....",
    "AF8.6.E0.D9CB...",
    "B.9..3.5.A10E..F",
    "E...A.1.F......C",
    ".D....C..2...3..",
    ".B2.7CD.0.5.8.16",
    "..1.F..E.83.0..A",
    "....51......94DE",
    ".9.........6C...",
    ".2.98E.....7F...",
    "D.E.9.7C23AB..8.",
    ".4.......F....9.",
    "F...2..B.9D41.3.",
]

game9 = [
   ".E.C.D7.92......",
   ".4.D10...C..9.8.",
   "1......936D.E.7.",
   "9....AE...4...0D",
   "...7.40.....3B..",
   "BC...1..0.5.7E4.",
   ".A24...E.B...F.8",
   "E.85B36..4.C..9.",
   "..A...94.3.5..D.",
   "3.C8.B...E1..9F5",
   "5..E...2...DA...",
   ".7.9...3..AB.12.",
   "...BD2.06.7.F.19",
   "7.43...1F.2..D..",
   "D8.09.5B..C3.4..",
   "AF1.E..7D..06C5.",
]

game10 = [
    "72..96..3",
    "...2.5...",
    ".8...4.2.",
    ".......6.",
    "1.65.38.7",
    ".4.......",
    ".3.8.....",
    "...7.2...",
    "2..43..18",
]

# Tough
game11 = [
    "3.9...4..",
    "2..7.9...",
    ".87......",
    "75..6.23.",
    "6..9.4..8",
    ".28.5..41",
    "......59.",
    "...1.6..7",
    "..6...1.4",
]

# Diabolical
game12 = [
    "...7.4..5",
    ".2..1..7.",
    "....8...2",
    ".9...625.",
    "6...7...8",
    ".532...1.",
    "4...9....",
    ".3..6..9.",
    "2..4.7...",
]

# Extreme
game13 = [
    "..6.195..",
    "9.7.68.43",
    ".8.......",
    "8.419....",
    "...6458..",
    "...8.29.4",
    ".....642.",
    "54...16.7",
    "..29843..",
]

game14 = [
    ".C.8.D5.2....E9A",
    "5...F.4..1.63C..",
    ".63.0CE9........",
    ".DE.3.2..B.476.8",
    "...3...E.6..5.1B",
    "1.F.....4.5..9..",
    ".B80.7.51.FE6.43",
    "E.....8FB9...D..",
    "...97...8A......",
    ".F4.E......2.7..",
    "....4893.C....62",
    "..B....A.....3C1",
    "F....5..6.4C.8..",
    "...2..C.D7A.F..0",
    "A.C......0....76",
    "4.D.9.0B.....A.5",
]

class Ansi():

    Width = None
    Height = None

    Black =   u"\u001b[30m"
    Red =     u"\u001b[31m"
    Green =   u"\u001b[32m"
    Yellow =  u"\u001b[33m"
    Blue =    u"\u001b[34m"
    Magenta = u"\u001b[35m"
    Cyan =    u"\u001b[36m"
    White =   u"\u001b[37m"

    BrightBlack =   u"\u001b[30;1m"
    BrightRed =     u"\u001b[31;1m"
    BrightGreen =   u"\u001b[32;1m"
    BrightYellow =  u"\u001b[33;1m"
    BrightBlue =    u"\u001b[34;1m"
    BrightMagenta = u"\u001b[35;1m"
    BrightCyan =    u"\u001b[36;1m"
    BrightWhite =   u"\u001b[37;1m"

    BlackBackground =   u"\u001b[40m"
    RedBackground =     u"\u001b[41m"
    GreenBackground =   u"\u001b[42m"
    YellowBackground =  u"\u001b[43m"
    BlueBackground =    u"\u001b[44m"
    MagentaBackground = u"\u001b[45m"
    CyanBackground =    u"\u001b[46m"
    WhiteBackground =   u"\u001b[47m"

    BrightBlackBackground =   u"\u001b[100;1m"
    BrightRedBackground =     u"\u001b[101;1m"
    BrightGreenBackground =   u"\u001b[102;1m"
    BrightYellowBackground =  u"\u001b[103;1m"
    BrightBlueBackground =    u"\u001b[104;1m"
    BrightMagentaBackground = u"\u001b[105;1m"
    BrightCyanBackground =    u"\u001b[106;1m"
    BrightWhiteBackground =   u"\u001b[107;1m"

    Bold = u"\u001b[1m"
    Dim = u"\u001b[2m"
    Underline = u"\u001b[4m"
    Reversed = u"\u001b[7m"

    Up = u"\u001b[%dA"
    Down = u"\u001b[%dB"
    Right = u"\u001b[%dC"
    Left = u"\u001b[%dD"

    NextLine = u"\u001b[1E"
    PreviousLine = u"\u001b[1F"

    ToColumn = u"\u001b[%dG"

    Move = u"\u001b[%d;%dH"

    Clear = u"\u001b[2J"
    ClearLine = u"\u001b[2K"

    Reset = u"\u001b[0m"

    HideCursor = u"\u001b[?25l"
    ShowCursor = u"\u001b[?25h"

    @staticmethod
    def SetColor(color: int) -> str:
        return u"\u001b[3%dm" % color

    @staticmethod
    def CursorToColumn(column: int) -> str:
        return Ansi.ToColumn % column

    @staticmethod
    def MoveUp(count: int=1) -> str:
        return Ansi.Up % count

    @staticmethod
    def MoveDown(count: int=1) -> str:
        return Ansi.Down % count

    @staticmethod
    def MoveLeft(count: int=1) -> str:
        return Ansi.Left % count

    @staticmethod
    def MoveRight(count: int=1) -> str:
        return Ansi.Right % count

    @staticmethod
    def MoveCursor(column: int, line: int) -> str:
        return Ansi.Move % (line, column)

    @staticmethod
    def Flush():
        stdout.flush()

    @staticmethod
    def Init():
        terminal_size = get_terminal_size()
        Ansi.Width = terminal_size.columns
        Ansi.Height = terminal_size.lines

        if platform == "linux" or platform == "linux2":
            # linux
            pass

        elif platform == "darwin":
            # OS X
            pass

        elif platform == "win32":
            import msvcrt
            kernel32 = ctypes.windll.kernel32
            kernel32.SetConsoleMode(kernel32.GetStdHandle(-11), 7)


class UI():
    def __init__(self, solver):
        self.solver = solver
        self.size = solver.size
        self.ssize = solver.ssize
        Ansi.Init()
        print(Ansi.Clear, end="")

    def show(self, pos: int) -> None:
        pass

    def _show_row(self, y: int, row):
        print(Ansi.BrightCyan + "|" + Ansi.Reset, end="")
        for x, col in enumerate(row):
            if self.solver.digits[y][x] is None:
                print(Ansi.BrightBlack + "." + Ansi.Reset, end="")
            else:
                if self.solver.digits[y][x].fixed:
                    print(Ansi.White, end="")
                elif not self.solver.digits[y][x].ad_hoc:
                    print(Ansi.BrightBlue, end="")
                else:
                    print(Ansi.BrightYellow, end="")
                print(self.solver.digits[y][x].value, end="")
                print(Ansi.Reset, end="")

            if x < self.size - 1 and x % self.ssize == (self.ssize - 1):
                print(Ansi.BrightCyan + "|" + Ansi.Reset, end = "")
        print(Ansi.BrightCyan + "|" + Ansi.Reset)

    def _show_divider(self):
        print(Ansi.BrightCyan + "+" + (("-" * self.ssize) + "+") * self.ssize + Ansi.Reset)

    def _show_top_bottom(self):
        print(Ansi.BrightCyan + "+" + (("-" * self.ssize) + "+") * self.ssize + Ansi.Reset)

    def show(self, pos: int) -> None:
        term_x = pos * (self.size + self.ssize + 4) + 1

        term_y = 2
        print(Ansi.MoveCursor(term_x, term_y), end="")
        self._show_top_bottom()
        term_y += 1

        for y, row in enumerate(self.solver.digits):
            print(Ansi.MoveCursor(term_x, term_y), end="")
            self._show_row(y, row)
            term_y += 1

            if y < self.size - 1 and y % self.ssize == (self.ssize - 1):
                print(Ansi.MoveCursor(term_x, term_y), end="")
                self._show_divider()
                term_y += 1

        print(Ansi.MoveCursor(term_x, term_y), end="")
        self._show_top_bottom()
        term_y += 1


class Digit():
    def __init__(self, x: int, y: int, value: str, fixed: bool = False, ad_hoc: bool = True):
        self.x = x
        self.y = y
        self.value = value
        self.fixed = fixed
        self.ad_hoc = ad_hoc

    def __repr__(self):
        return f"Digit({self.x}, {self.y}, {self.value})"

class Solver():
    def __init__(self):
        self.step = 0
        self.possible_digits = {}

    def loadgame(self, game):
        self.size = len(game)
        if self.size not in [4, 9, 16]:
            raise Exception("Size must be 4, 9 or 16")

        self.digits = [[None for x in range(self.size)] for y in range(self.size)]

        if self.size == 4:
            self.valid_digits = ["1", "2", "3", "4"]
            self.ssize = 2
        elif self.size == 9:
            self.valid_digits = ["1", "2", "3", "4", "5", "6", "7", "8", "9"]
            self.ssize = 3
        elif self.size == 16:
            self.valid_digits = ["0", "1", "2", "3", "4", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"]
            self.ssize = 4

        self.valid_digits_set = set(self.valid_digits)

        if len(game) != self.size:
            raise Exception(f"Game must contain {self.size} rows")
        if any([len(line) != self.size for line in game]):
            raise Exception(f"All rows in game must contain {self.size} columns")

        for y, row in enumerate(game):
            for x, col in enumerate(row):
                if col in self.valid_digits:
                    self.digits[y][x] = Digit(x, y, col, True)

        if self._check_validity() == False:
            raise Exception("Loaded game is invalid")

        self.UI = UI(self)
        self.UI.show(0)

    def _validate_row(self, y: int) -> bool:
        filled_in = [d.value for d in self.digits[y] if d is not None]
        return len(filled_in) == len(set(filled_in))

    def _validate_column(self, x: int) -> bool:
        filled_in = [d[x].value for d in self.digits if d[x] is not None]
        return len(filled_in) == len(set(filled_in))

    def _validate_box(self, bx: int, by: int) -> bool:
        filled_in = []
        for x in range(bx * self.ssize, (bx + 1) * self.ssize):
            for y in range(by * self.ssize, (by + 1) * self.ssize):
                if self.digits[y][x] is not None:
                    filled_in.append(self.digits[y][x].value)
        return len(filled_in) == len(set(filled_in))

    def _check_validity(self) -> bool:
        for y in range(self.size):
            if self._validate_row(y) == False:
                return False
        for x in range(self.size):
            if self._validate_column(x) == False:
                return False
        for x in range(self.ssize):
            for y in range(self.ssize):
                if self._validate_box(x, y) == False:
                    return False
        return True

    def _is_solved(self) -> bool:
        for row in self.digits:
            if any([d is None for d in row]):
                return False
        return self._check_validity()

    def calculate_possible_digits(self) -> None:
        for x in range(self.size):
            for y in range(self.size):
                if self.digits[y][x] is not None:
                    continue
                self.possible_digits[(x, y)] = [digit for digit in self.valid_digits if self.can_place(x, y, digit)]

    def _find_obvious_spot_by_row(self, yy: int):
        filled_in = [d.value for d in self.digits[yy] if d is not None]
        missing = list(self.valid_digits_set.difference(set(filled_in)))

        possibilities = {}

        for digit in missing:
            possibilities[digit] = []
            for x in range(self.size):
                if self.digits[yy][x] is not None:
                    continue
                self.digits[yy][x] = Digit(x, yy, digit, ad_hoc = False)
                if self._check_validity():
                    possibilities[digit].append((x, yy))
                self.digits[yy][x] = None

        for digit, poss in possibilities.items():
            if len(poss) == 1:
                return poss[0][0], poss[0][1], digit

        return None, None, None

    def _find_obvious_spot_by_column(self, xx: int):
        filled_in = [d[xx].value for d in self.digits if d[xx] is not None]
        missing = list(self.valid_digits_set.difference(set(filled_in)))

        possibilities = {}

        for digit in missing:
            possibilities[digit] = []
            for y in range(self.size):
                if self.digits[y][xx] is not None:
                    continue
                self.digits[y][xx] = Digit(xx, y, digit, ad_hoc = False)
                if self._check_validity():
                    possibilities[digit].append((xx, y))
                self.digits[y][xx] = None

        for digit, poss in possibilities.items():
            if len(poss) == 1:
                return poss[0][0], poss[0][1], digit

        return None, None, None

    def _box_spots(self, bx: int, by: int):
        for x in range(bx * self.ssize, (bx + 1) * self.ssize):
            for y in range(by * self.ssize, (by + 1) * self.ssize):
                yield (x, y)

    def _find_obvious_spot_by_box(self, bx: int, by: int):
        filled_in = []
        for x in range(bx * self.ssize, (bx + 1) * self.ssize):
            for y in range(by * self.ssize, (by + 1) * self.ssize):
                if self.digits[y][x] is not None:
                    filled_in.append(self.digits[y][x].value)
        missing = list(self.valid_digits_set.difference(set(filled_in)))

        possibilities = {}

        for digit in missing:
            possibilities[digit] = []
            for x, y in self._box_spots(bx, by):
                if self.digits[y][x] is not None:
                    continue
                self.digits[y][x] = Digit(x, y, digit, ad_hoc = False)
                if self._check_validity():
                    possibilities[digit].append((x, y))
                self.digits[y][x] = None

        for digit, poss in possibilities.items():
            if len(poss) == 1:
                return poss[0][0], poss[0][1], digit

        return None, None, None

    def _find_obvious_spot(self):
        for yy in range(self.size):
            x, y, value = self._find_obvious_spot_by_row(yy)
            if x is not None:
                return x, y, value

        for xx in range(self.size):
            x, y, value = self._find_obvious_spot_by_column(xx)
            if x is not None:
                return x, y, value

        for bx in range(self.ssize):
            for by in range(self.ssize):
                x, y, value = self._find_obvious_spot_by_box(bx, by)
                if x is not None:
                    return x, y, value

        return None, None, None

    def can_place_on_row(self, row: int, value) -> bool:
        for i in range(self.size):
            if self.digits[row][i] is not None and self.digits[row][i].value == value:
                return False
        return True

    def can_place_on_column(self, column: int, value) -> bool:
        for i in range(self.size):
            if self.digits[i][column] is not None and self.digits[i][column].value == value:
                return False
        return True

    def can_place_on_box(self, column: int, row: int, value) -> bool:
        bx = column - column % self.ssize
        by = row - row % self.ssize
        for y in range(by, by + self.ssize):
            for x in range(bx, bx + self.ssize):
                if self.digits[y][x] is not None and self.digits[y][x].value == value:
                    return False
        return True

    def show_progress(self):
        if self.step % 100_000 == 0:
            self.UI.show(2)

    def can_place(self, x: int, y: int, value) -> bool:
        self.step += 1
        if not self.can_place_on_row(y, value):
            return False
        if not self.can_place_on_column(x, value):
            return False
        if not self.can_place_on_box(x, y, value):
            return False
        return True

    def try_solve(self) -> bool:
        # print(self.digits[0][0])
        for yy in range(self.size):
            for xx in range(self.size):
                if self.digits[yy][xx] is None:
                    # print(xx, yy)
                    for digit in self.possible_digits[(xx,yy)]:
                        self.show_progress()
                        if self.can_place(xx, yy, digit):
                            self.digits[yy][xx] = Digit(xx, yy, digit)
                            if self.try_solve():
                                return True

                            self.digits[yy][xx] = None
                    return False
        return True

    def solve(self):
        while self._is_solved() == False:
            x, y, value = self._find_obvious_spot()
            if x is None:
                break
            else:
                self.digits[y][x] = Digit(x, y, value, ad_hoc=False)
                self.UI.show(1)

        self.UI.show(1)

        if self._is_solved() == False:
            self.calculate_possible_digits()
            if not self.try_solve():
                print("Not solvable")

        self.UI.show(2)
        return True


def main(game):
    solver = Solver()
    solver.loadgame(game)
    print(Ansi.HideCursor)
    start = time.perf_counter()
    solved = solver.solve()
    end = time.perf_counter()
    ellapsed = end - start
    print("Ellapsed: %s%.5f%s seconds" % (Ansi.BrightRed, ellapsed, Ansi.Reset))
    if not solved:
        print("No solution")
    print(Ansi.ShowCursor)

if __name__ == "__main__":
    main(game12)
