#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#define NB_DISABLE 1
#define NB_ENABLE  0

int kbhit()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

void nonblock(int state)
{
    struct termios ttystate;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state == NB_ENABLE)
    {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        ttystate.c_lflag &= ~ECHO;

        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else if (state == NB_DISABLE)
    {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
        ttystate.c_lflag |= ECHO;
    }

    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

int main()
{
    char c;
    int i = 0;

    printf("Press Q to exit...\n");

    nonblock(NB_ENABLE);
    while (1)
    {
        usleep(1);
        i = kbhit();
        if (i != 0)
        {
            c = fgetc(stdin);
            if (c == 'q' || c == 'Q')
            {
                break;
            }

            printf("%c\n", c);
        }
    }

    nonblock(NB_DISABLE);
    return 0;
}
