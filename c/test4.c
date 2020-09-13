#include <stdio.h>
#include <string.h>

typedef unsigned short uint16;

typedef struct
{
	float x;
	float y;
	float z;
} Vector3;

typedef struct
{
	char name[25];
	Vector3 position;
	uint16 health;
} Player;

void ShowPlayer(Player player)
{
	printf("Player '%s' is at position (%.3f, %.3f, %.3f) and has health %d\n", player.name, player.position.x, player.position.y, player.position.z, player.health);
}

int main()
{
	Player thePlayer;
	strcpy(thePlayer.name, "Luke Skywalker");
	thePlayer.health = 100;
	thePlayer.position.x = 0.0;
	thePlayer.position.y = 0.0;
	thePlayer.position.z = 0.0;

	ShowPlayer(thePlayer);

	char buffer[100];
	sprintf(buffer, "Player uses %d bytes.\n", sizeof(thePlayer));
	printf(buffer);	
}
