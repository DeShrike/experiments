#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

// SIGWINCH is called when the window is resized.

void show_dimensions()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    printf ("Lines: %d\n", w.ws_row);
    printf ("Columns: %d\n", w.ws_col);
    printf ("X pixels: %d\n", w.ws_xpixel);
    printf ("Y pixels: %d\n", w.ws_ypixel);
}

void handle_winch(int sig)
{
    signal(SIGWINCH, SIG_IGN);

    show_dimensions();

    signal(SIGWINCH, handle_winch);
}

int main (int argc, char **argv)
{
    printf("Press <enter> to exit \n");

    show_dimensions();

    signal(SIGWINCH, handle_winch);

    getchar();

    return 0;
}
