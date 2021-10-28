#include <iostream>
#include <string>
#include <fstream>
#include "Cinema.h"
#include "Movies.h"
#include "Seat.h"
#include <stdlib.h>
#include <cstdlib>
#include <Windows.h>
using namespace std;

Cinema c;

int main() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 15);
	c.beginprogram();
}

