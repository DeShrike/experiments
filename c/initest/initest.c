#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "config.h"
#include "initest.h"

int main(int argc, char* argv[])
{
    configuration* config;
    config = read_config("initest.ini");
    if (config == NULL)
    {
        printf("Can't load 'initest.ini'\n");
        return 1;
    }

    printf("Config loaded from 'initest.ini':\n");
    printf("     led1: %d \n     led2: %d \n     led3: %d \n     led4: %d \n  button1: %d \n  button2: %d \n      fan: %d \n",
        config->led1Pin, config->led2Pin, config->led3Pin, config->led4Pin,
        config->button1Pin, config->button2Pin,
        config->fanPin);

    printf("\nName: %s\n", config->name);
    free_config(config);

    return 0;
}
