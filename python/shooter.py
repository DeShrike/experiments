from Ansi import Ansi





if __name__ == "__main__":
    Ansi.Init()
    print(Ansi.Clear + Ansi.HideCursor , Ansi.MoveCursor(1,1), end = ""),
    print(Ansi.Red + "This Is Red" , Ansi.Reset)
    print("Test")

    print(Ansi.ShowCursor, end = "")

