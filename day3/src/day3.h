#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int day3_part1(){
    string line;
    ifstream my_file;
    int priorities_sum = 0;
    my_file.open("C:/Users/Fred/eclipse-workspace/day3/src/input.txt");
    if (my_file.is_open()){
        while(getline(my_file, line)){
            // split line in half
            string first_half = line.substr(0, line.length()/2);
            string second_half = line.substr(line.length()/2);

            for (char& c : first_half){
               if (second_half.find(c) != string::npos){
                   // lower case
                   if (('a' - 1 < c) && (c < 'z' + 1)){
                       priorities_sum += c - 'a' + 1;
                   }
                   // upper case
                   else{
                       priorities_sum += c -'A' + 26 + 1;
                   }
                   // don't find the repeated letter more than once
                   break;
               }
            }

        }
        cout << priorities_sum;
        my_file.close();
    }
    return 0;
}

int day3_part2(){
    string line;
    ifstream my_file;
    int priorities_sum = 0;
    my_file.open("C:/Users/Fred/eclipse-workspace/day3/src/input.txt");
    if (my_file.is_open()){
        while(getline(my_file, line)){
            // find each group of 3 elves
            string elves[3];
            elves[0] = line;
            // only two because we already got one line in the while loop
            for (int i = 1; i <= 2; i++){
                getline(my_file, line);
                elves[i] = line;
            }
            // find the letter all 3 have in common
            for (char& c : elves[0]){
               if (elves[1].find(c) != string::npos){
                   if (elves[2].find(c) != string::npos){
                       // lower case
                       if (('a' - 1 < c) && (c < 'z' + 1)){
                           priorities_sum += c - 'a' + 1;
                       }
                       // upper case
                       else{
                           priorities_sum += c -'A' + 26 + 1;
                       }
                       // don't find the repeated letter more than once
                       break;
                   }
               }
            }

        }
        cout << priorities_sum;
        my_file.close();
    }
    return 0;
}
