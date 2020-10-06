// #include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h> // for strlen()
// #include <limits.h>
// #include <math.h>
#include <time.h>
// #include <float.h>
#include <unistd.h> // for sleep())
// #include <errno.h>

#include <iostream>
#include <string>

#include "grid.hpp"
#include "board.hpp"
#include "player.hpp"
#include "ai.hpp"
#include "human.hpp"
#include "keyboard.hpp"

extern int errno;

using namespace std;

bool done = false;
Board *board;
Grid *grid;
int currentTurn;
Player *player1;
Player *player2;

typedef struct
{
    bool normalrun;
    bool battle;
    int ai1;
    int ai2;
    int startingPlayer;
} Arguments;

/*
void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    now = then = clock();
    while( (now-then) < pause )
    {
        now = clock();
    }
}
*/

void CopyTo(char (*from)[WIDTH], char (*to)[WIDTH])
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            to[y][x] = from[y][x];
        }
    }
}

/*void WaitForEnter()
{
	MoveCursor(1, 1);
	printf("%sPress ENTER to start%s", BRIGHTRED, RESET);
	getchar();
	MoveCursor(1, 1);
	printf("                          ");
}
*/
void Init(Arguments arguments)
{
    grid = new Grid();
    board = new Board(grid);
    currentTurn = arguments.startingPlayer;

    if (arguments.normalrun)
    {
        player1 = new Human();
        player2 = new Ai(arguments.ai1);
    }
    else
    {
        player1 = new Ai(arguments.ai1);
        player2 = new Ai(arguments.ai2);
    }
}

bool Game()
{
    int move = 0;
    if (currentTurn == 1)
    {
        move = player1->GetNextMove(board);
    }
    else
    {
        move = player2->GetNextMove(board);
    }

    board->DoMove(move);
    board->Draw();
    int winner = board->Winner();
    if (winner != 0)
    {
        currentTurn = currentTurn == 1 ? 2 : 1;
        return true;
    }

    return false;
}

void Run(Arguments arguments)
{
    Init(arguments);
    board->Draw();

    while (done == false)
    {
        if (Game())
        {
            break;
        }

        usleep(100000);
        break;  // TOD remove 
    }

    sleep(1);

    delete player1;
    delete player2;
    delete board;
    delete grid;
}

/******************************************************/

int main(int argc, char *argv[])
{
	Arguments arguments;

	/* Default values. */
	arguments.normalrun = true;
	arguments.battle = false;
	arguments.ai1 = 1;
	arguments.ai2 = 1;
    arguments.startingPlayer = 1;

    Keyboard *k = new Keyboard(); 

    int x = k->GetKey();
    cout << " " << x << " " << (char)x << " " << endl;
    delete k;
    //Run(arguments);

	exit(0);
}
