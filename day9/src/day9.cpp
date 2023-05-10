//============================================================================
// Name        : day7.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "day9.h"
using namespace std;
#ifndef FILENAME
#define FILENAME "C:/Users/Fred/eclipse-workspace/day9/src/input.txt"
#endif

int main() {
    // + 1 because it doesn't count the starting position
	cout << day9_part1(FILENAME) + 1 << endl;
	return 0;
}
