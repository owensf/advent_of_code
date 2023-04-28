//============================================================================
// Name        : day1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string line;
    int most_calories = 0;
    int current_calories = 0;
    ifstream myfile;
    myfile.open("C:/Users/Fred/eclipse-workspace/day1/src/input.txt");
    if (myfile.is_open()){
        while(getline(myfile, line)){
            if (line != ""){
                current_calories += stoi(line);
            }
            else{
                if (current_calories > most_calories){
                    most_calories = current_calories;
                }
                current_calories = 0;
            }
        }
        myfile.close();
    }
    cout << "Most calories: " << most_calories << endl;
    return 0;
}
