#include <stdbool.h>
#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strlen()
#include <limits.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <unistd.h> // for sleep())
#include <signal.h> // for signal()
#include <errno.h>

extern int errno;

char BRIGHTRED[] = "\033[31;1m";

char RESET[] = "\033[0m";
char INVERSE[] = "\033[5m";
char HIDECURSOR[] ="\033[?25l";
char SHOWCURSOR[] = "\033[?25h";
char CLEARSCREEN[] = "\033[2J";
char STORESCREEN[] = "\033[?1049h\033[H";
char RESTORESCREEN[] = "\033[?1049l";

#define WIDTH            38
#define HEIGHT           22
#define PIXELWIDTH       2
#define PIXELHEIGHT      1
#define COLORCOUNT       (sizeof(Colors) / sizeof(int))
#define OFFSETX          ((80 - (WIDTH * PIXELWIDTH)) / 2)
#define OFFSETY          1

static volatile int keepRunning = 1;

// typedef char GridType[HEIGHT][WIDTH]; 

char Grid[HEIGHT][WIDTH];
int CurrentColor = -1;
char PreviousGrid[HEIGHT][WIDTH];
char Mem1[HEIGHT][WIDTH];
char Mem2[HEIGHT][WIDTH];
char StartState[HEIGHT][WIDTH];

char HighestState[HEIGHT][WIDTH];
char LowestState[HEIGHT][WIDTH];
char UnstableState[HEIGHT][WIDTH];

int Colors[] = { 0 /*5*/, 41, 42, 43, 44, 45, 46, 47 };

int Generation = 0;

void MoveCursor(int y, int x)
{
    printf("\033[%d;%dH", y, x);
}

void SetColor(int color)
{
    if (color < 0 || color >= COLORCOUNT)
    {
        return;
    }

    int colorValue = Colors[color];

    if (colorValue == CurrentColor)
    {
        return;
    }

    printf("\033[%dm", colorValue);
    CurrentColor = colorValue;
}

void ResetColor()
{
    printf("\033[0m");
    CurrentColor = 0;
}

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

void ClearGrid()
{
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            Grid[y][x] = 0;
        }
    }
}

void DrawPixel(int x, int y)
{
    int value = Grid[y][x];

    SetColor(value);
    for (int x = 0; x < PIXELWIDTH; x++)
    {
        putchar(' ');
    }

    // ResetColor();
}

void CopyGridToPrevious()
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            Mem1[y][x] = Mem2[y][x];
            Mem2[y][x] = PreviousGrid[y][x];
            PreviousGrid[y][x] = Grid[y][x];
        }
    }
}

bool CheckIfStable()
{
    bool stable = true;
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (Mem1[y][x] != Grid[y][x])
            {
                stable = false;
                break;
            }
        }
    }    

    if (stable)
    {
        return true;
    }

    stable = true;
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (Grid[y][x] != PreviousGrid[y][x])
            {
                stable = false;
                break;
            }
        }
    }    

    return stable;
}

void DrawGrid()
{
    bool shouldSetCursor = false;
    MoveCursor(1, 1);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int line = 0; line < PIXELHEIGHT; line++)
        {
            MoveCursor(y * PIXELHEIGHT + line + 1 + OFFSETY, 1 + OFFSETX);
            for (int x = 0; x < WIDTH; x++)
            {
                char prev = PreviousGrid[y][x];
                if (prev != Grid[y][x])
                {
                    if (shouldSetCursor)
                    {
                        MoveCursor(y * PIXELHEIGHT + line + 1 + OFFSETY, 1 + OFFSETX + (x * PIXELWIDTH));
                        shouldSetCursor = false;
                    }

                    DrawPixel(x, y);
                }
                else
                {
                    shouldSetCursor = true;
                }
            }
        }

        ResetColor();
    }

    fflush(stdout);
}

void PlotPoint(int x, int y, int c)
{
    Grid[y][x] = c;
}

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

void Init()
{
    /*
    Grid[0][0] = 7;
    Grid[1][1] = 7;
    Grid[1][2] = 7;
    Grid[2][0] = 7;
    Grid[2][1] = 7;

    Grid[10][10] = 7;
    Grid[11][11] = 7;
    Grid[11][12] = 7;
    Grid[12][10] = 7;
    Grid[12][11] = 7;
    */

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            Grid[y][x] = (rand() % 10 < 5) ? 7 : 0;
            StartState[y][x] = Grid[y][x];
        }
    }
}

char GetNeighbour(int x, int y)
{
    if (x < 0)
    {
        x += WIDTH;
    }

    if (y < 0)
    {
        y += HEIGHT;
    }

    if (x >= WIDTH)
    {
        x -= WIDTH;
    }

    if (y >= HEIGHT)
    {
        y -= HEIGHT;
    }

    return PreviousGrid[y][x];
}

int CountNeighbours(int x, int y)
{
    int c = 0;
    c += GetNeighbour(x + 1, y + 0) > 0 ? 1 : 0;
    c += GetNeighbour(x + 1, y + 1) > 0 ? 1 : 0;
    c += GetNeighbour(x + 0, y + 1) > 0 ? 1 : 0;
    c += GetNeighbour(x - 1, y + 1) > 0 ? 1 : 0;
    c += GetNeighbour(x - 1, y + 0) > 0 ? 1 : 0;
    c += GetNeighbour(x - 1, y - 1) > 0 ? 1 : 0;
    c += GetNeighbour(x + 0, y - 1) > 0 ? 1 : 0;
    c += GetNeighbour(x + 1, y - 1) > 0 ? 1 : 0;

    return c;
}

bool Life(bool show)
{
    CopyGridToPrevious();
    ClearGrid();

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            char c = PreviousGrid[y][x];
            int n = CountNeighbours(x, y);
            if (c > 0 && n < 2)
            {
                Grid[y][x] = 0;
            }
            else if (c > 0 && (n == 2 || n == 3))
            {
                Grid[y][x] = c > 1 ? c - 1 : 1;
            }
            else if (c > 0 && n >= 3)
            {
                Grid[y][x] = 0;
            }
            else if (c == 0 && n == 3)
            {
                Grid[y][x] = 7;
            }
        }
    }

    Generation++;

    if (CheckIfStable())
    {
        return false;
    }

    if (show)
    {
        DrawGrid();
    }

    CopyGridToPrevious();

    return true;
}

void intHandler(int dummy)
{
    keepRunning = 0;
}

void WaitForEnter()
{
	MoveCursor(1, 1);
	printf("%sPress ENTER to start%s", BRIGHTRED, RESET);
	getchar();
	MoveCursor(1, 1);
	printf("                          ");
}

void LoadGrid(char *filename)
{
    FILE *fp = fopen(filename, "r");
	if (fp == NULL)	
	{
		fprintf(stderr, "Could not open file %s: %d\n", filename, errno);	
		// perror("Error printed by perror");
      	// fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
      	return;
    }

    char buffer[WIDTH * HEIGHT];
	size_t read = fread(buffer, sizeof(char), WIDTH * HEIGHT, fp);
    fclose(fp);

    int ix = 0;
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
        	Grid[y][x] = buffer[ix];
        	ix++;
		}
	}
}

void SaveGrid(char (*state)[WIDTH], int generations)
{
	char filename[100];
	sprintf(filename, "life-%d.gol", generations);

	printf("Saving %s\n", filename);
	
    FILE *fp = fopen(filename, "w");
	if (fp == NULL)
	{
		fprintf(stderr, "Could not open file %s: %d\n", filename, errno);	
		// perror("Error printed by perror");
      	// fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
      	return;
    }
	
 	// fprintf(fp, "This is testing for fprintf...\n");
   	// fputs("This is testing for fputs...\n", fp);

	// size_t fread(void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *a_file);

    int ix = 0;
    char buffer[WIDTH * HEIGHT];
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
        	buffer[ix] = state[y][x];
        	ix++;
		}
	}

	fwrite(buffer, sizeof(char), WIDTH * HEIGHT, fp);
    
    fclose(fp);
}

void NormalRun(char *filename)
{
    time_t t;
    srand((unsigned) time(&t));

    signal(SIGINT, intHandler);

    printf(STORESCREEN);
    printf(CLEARSCREEN);
    printf(HIDECURSOR);

    if (filename != NULL)
    {
    	LoadGrid(filename);
    }
    else
    {
    	Init();
	}

    DrawGrid();

    WaitForEnter();

    while (keepRunning)
    {
        if (Life(true) == false)
        {
            break;
        }

        usleep(100000);
    }

    sleep(1);
    printf(SHOWCURSOR);
    printf(RESTORESCREEN);

    printf("Stable after %d Generations\n", Generation);
}

int BatchRun(int batchSize)
{
    time_t t;
    srand((unsigned) time(&t));

    int HighestGeneration = 0;
    int LowestGeneration = 1000000;

    int GenerationLimit = 20000;
    bool hasUnstable = false;

    for (int g = 0; g < batchSize; g++)
    {
        if ((g % 1000) == 0)
        {
        	printf("Game %d ", g + 1);
    	}

        Init();
        Generation = 0;
        while (keepRunning)
        {
            if (Life(false) == false)
            {
                break;
            }

            if (Generation > GenerationLimit)
            {
                break;
            }
        }

        if ((g % 1000) == 0)
        {
        	printf("Stable after %d Generations\n", Generation);
    	}

        if (Generation < GenerationLimit)
        {
            if (Generation > HighestGeneration)
            {
                HighestGeneration = Generation;
                CopyTo(StartState, HighestState);
			    SaveGrid(HighestState, HighestGeneration);
            }

            if (Generation < LowestGeneration)
            {
                LowestGeneration = Generation;
                CopyTo(StartState, LowestState);
			    SaveGrid(LowestState, LowestGeneration);
            }
        }
        else
        {
            CopyTo(StartState, UnstableState);
            hasUnstable = true;
        }
    }

    if (hasUnstable)
    {
    	SaveGrid(UnstableState, GenerationLimit);
	}

    SaveGrid(HighestState, HighestGeneration);
    SaveGrid(LowestState, LowestGeneration);

    printf("\n");
    printf("Lowest: %d\n", LowestGeneration);
    printf("Highest: %d\n", HighestGeneration);
}

/******************************************************/

const char *argp_program_version = "Life 1.0";
const char *argp_program_bug_address = "<de_shrike@hotmail.com>";

/* Program documentation. */
static char doc[] = "Game Of Live in the Terminal -- run the Game of Life in your Linux terminal\n";

/* A description of the arguments we accept. */
static char args_doc[] = "";

/* The options we understand. */
static struct argp_option options[] = {
	{"run",       'r', 0,      0, "Run 1 Game Of Life on screen" },
	{"batchsize", 'b', "NUM",  0, "The number of games to run (default 10)" },
	{"input",     'i', "FILE", 0, "Read the given file and replay" },
	{ 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments
{
	char *args[1];                /* arg1  */
	bool normalrun;
	int batchsize;
	bool batchmode;
	bool filemode;
	char *inputfile;
};

static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
	/* Get the input argument from argp_parse, which we
	   know is a pointer to our arguments structure. */
	struct arguments *arguments = state->input;

	// printf("parse_opt %d %c %s\n", key, (char)key, arg);

	switch (key)
	{
		case 'r':
			arguments->normalrun = true;
			arguments->batchmode = false;
			arguments->filemode = false;
			break;

		case 'i':
			arguments->filemode = true;
			arguments->inputfile = arg;
			arguments->batchmode = false;
			arguments->normalrun = false;
			break;

		case 'b':
			arguments->batchsize = atoi(arg);
			arguments->batchmode = true;
			arguments->normalrun = false;
			arguments->filemode = false;
			break;

		case ARGP_KEY_ARG:
			// printf("ARGP_KEY_ARG %d\n", state->arg_num);
			if (state->arg_num >= 0)
			{
				/* Too many arguments. */
				// printf("Too many\n");
				argp_usage(state);
			}

			arguments->args[state->arg_num] = arg;
			break;

		case ARGP_KEY_END:
			if (state->arg_num < 0)
			{
				/* Not enough arguments. */
				// printf("Not enough\n");
				argp_usage(state);
			}

			break;

		default:
			return ARGP_ERR_UNKNOWN;
	}

	return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char *argv[])
{
	/*
	printf("File :%s\n", __FILE__ );
	printf("Date :%s\n", __DATE__ );
	printf("Time :%s\n", __TIME__ );
	printf("Line :%d\n", __LINE__ );
	printf("ANSI :%d\n", __STDC__ );
	*/
	
	struct arguments arguments;

	/* Default values. */
	arguments.normalrun = true;
	arguments.batchmode = false;
	arguments.filemode = false;
	arguments.inputfile = NULL;
	arguments.batchsize = 10;

	/* Parse our arguments; every option seen by parse_opt will
	   be reflected in arguments. */
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	/*
	printf("NORMALMODE = %s\n"
		   "MODE = %s\n"
		   "INPUT_FILE = %s\n"
           "BATCHSIZE = %d\n"
           "BATCHMODE = %s\n",
          arguments.normalrun ? "yes" : "no",
          arguments.args[0], 
          arguments.inputfile,
          arguments.batchsize,
          arguments.batchmode ? "yes" : "no");
	*/

	if (arguments.normalrun)
	{
		NormalRun(NULL);
	}
	else if (arguments.batchmode)
	{
		BatchRun(arguments.batchsize);
	}
	else
	{
		NormalRun(arguments.inputfile);
	}

	exit(0);
}
