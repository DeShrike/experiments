#include <iostream>

using namespace std;

#include <stdio.h>	// this is a C header include

int main()
{
  double pi, radius;
  double area, circumference;

  pi = 3.1415926535;

  radius = 42;

  area = pi * (radius * radius);
  circumference = 2 * pi * radius;

  printf("Hello C\n");
  cout << "Hello C++" << endl;

  return 0;
}

// c++ hello.c -o hello
