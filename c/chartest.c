#include <stdio.h>

#define LEN(x)  (sizeof(x) / sizeof((x)[0]))

char BRIGHTRED[] = "\033[31;1m";

char RESET[] = "\033[0m";
char INVERSE[] = "\033[5m";
char HIDECURSOR[] ="\033[?25l";
char SHOWCURSOR[] = "\033[?25h";
char CLEARSCREEN[] = "\033[2J";
char STORESCREEN[] = "\033[?1049h\033[H";
char RESTORESCREEN[] = "\033[?1049l";

char STARTBOX[] = "\033(0";
char STOPBOX[] = "\033(B";

void ShowAll()
{
   char t[2];
   t[0] = 0;
   t[1] = 0;
   for (int i = 0; i < 256; i++)
   {
      t[0] = i;
      printf("Char %d = %s \n", i, t);
   }
}

void main()
{
	char special[] = { 0x80, 0x82, 0x8c, 0x90, 0x94, 0x98, 0x9c, 0xa4, 0xac, 0xb4, 0xbc };

	char block[] = { 0xe2, 0x94, 0x80, '\0' };

	for (int i = 0x80; i < 0xff; i++)
	{
		block[2] = i;
	    printf("%d %x %s \n", i, i, block);
	}

	printf("Start \n");

	for (int i = 0; i < LEN(special); i++)
	{
		block[2] = special[i];
	    printf("%d %x %s%s%s \n", special[i], special[i], BRIGHTRED, block, RESET);
	}

	// ShowAll();
}
