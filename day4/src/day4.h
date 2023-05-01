#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int day4_part1(){
    // find number of pairs that are fully contained within the other
    string line;
    ifstream my_file;
    int num_contained_pairs = 0;
    my_file.open("C:/Users/Fred/eclipse-workspace/day4/src/input.txt");
    if (my_file.is_open()){
        while(getline(my_file, line)){
            // ranges are split up by commas
            string first_range = line.substr(0, line.find(','));
            string second_range = line.substr(line.find(',')+1);
            int first_first = stoi(first_range.substr(0, first_range.find('-')));
            int first_second = stoi(first_range.substr(first_range.find('-')+1));
            int second_first = stoi(second_range.substr(0, second_range.find('-')));
            int second_second = stoi(second_range.substr(second_range.find('-')+1));
            // check if first_range contains second_range
            if ((first_first <= second_first) && (first_second >= second_second)){
                num_contained_pairs++;
            }
            // check if second_range contains first range
            else if ((second_first <= first_first) && (second_second >= first_second)){
                num_contained_pairs++;
            }
        }
    }
    return num_contained_pairs;
}

// find number of pairs with any overlap
int day4_part2(){
    // find number of pairs that are fully contained within the other
    string line;
    ifstream my_file;
    int num_contained_pairs = 0;
    my_file.open("C:/Users/Fred/eclipse-workspace/day4/src/input.txt");
    if (my_file.is_open()){
        while(getline(my_file, line)){
            // ranges are split up by commas
            string first_range = line.substr(0, line.find(','));
            string second_range = line.substr(line.find(',')+1);
            // numbers are split up by dashes
            int first_first = stoi(first_range.substr(0, first_range.find('-')));
            int first_second = stoi(first_range.substr(first_range.find('-')+1));
            int second_first = stoi(second_range.substr(0, second_range.find('-')));
            int second_second = stoi(second_range.substr(second_range.find('-')+1));
            // check for overlaps
            if ((first_first <= second_second) && (first_first >= second_first)){
                num_contained_pairs++;
            }
            else if ((first_second <= second_second) && (first_second >= second_first)){
                num_contained_pairs++;
            }
            else if ((second_first <= first_second) && (second_second >= first_first)){
                num_contained_pairs++;
            }
            else if ((second_second <= first_second) && (second_second >= first_second)){
                num_contained_pairs++;
            }
        }
    }
    return num_contained_pairs;
}
