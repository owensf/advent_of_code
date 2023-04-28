#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int day1_part2(){
    string line;
    int most_calories[3] = {0, 0, 0};
    int current_calories = 0;
    ifstream myfile;
    myfile.open("C:/Users/Fred/eclipse-workspace/day1/src/input.txt");
    if (myfile.is_open()){
        while(getline(myfile, line)){
            if (line != ""){
                current_calories += stoi(line);
            }
            else{
                if (current_calories > most_calories[0]){
                    most_calories[2] = most_calories[1];
                    most_calories[1] = most_calories[0];
                    most_calories[0] = current_calories;
                }
                else if (current_calories > most_calories[1]){
                    most_calories[2] = most_calories[1];
                    most_calories[1] = current_calories;
                }
                else if (current_calories > most_calories[2]){
                    most_calories[2] = current_calories;
                }
                current_calories = 0;
            }
        }
        myfile.close();
    }
    cout << "Top 3 calories: " << most_calories[2] + most_calories[1] + most_calories[0] << endl;
    return 0;
}

int day1_part1(){
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
