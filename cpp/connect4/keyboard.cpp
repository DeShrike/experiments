#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include "keyboard.hpp"

using namespace std;

Keyboard::Keyboard()
{
}

int Keyboard::GetKey()
{
    Disable();

    int c = getchar();
    cout << "First " << c << endl;
    if (c == 27 /*224*/)
    {
        // Special 
        cout << "Special" << endl;
        c += getchar();
        c += getchar();
    }

    Enable();
    return c;
}

/* Disables buffered input */
void Keyboard::Disable(void)
{
    tcgetattr(STDIN_FILENO, &t); 		// Get the current terminal I/O structure
    t.c_lflag &= ~(ICANON|ECHO); 		// Manipulate the flag bits to do what you want it to do
    tcsetattr(STDIN_FILENO, TCSANOW, &t); // Apply the new settings
}

/* Enables buffered input */
void Keyboard::Enable(void)
{
    tcgetattr(STDIN_FILENO, &t); 	// Get the current terminal I/O structure
    t.c_lflag |= (ICANON|ECHO); 	// Manipulate the flag bits to do what you want it to do
    tcsetattr(STDIN_FILENO, TCSANOW, &t); // Apply the new settings
}
