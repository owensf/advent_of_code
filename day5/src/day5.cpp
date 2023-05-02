//============================================================================
// Name        : day5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include "day5.h"
#define FILENAME "C:/Users/Fred/eclipse-workspace/day5/src/input.txt"
using namespace std;

int main() {
	vector<char> tops_of_stacks =  day5_part2(FILENAME);
	for (auto i: tops_of_stacks){
	    cout << i << endl;
	}
}
