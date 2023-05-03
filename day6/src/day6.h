#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// return the char # where the first 4 unique characters occur
int day6_part1(string filename){
    string line;
    ifstream my_file;
    int found_unique = -1;
    my_file.open(filename);
    if (my_file.is_open()){
        while(getline(my_file, line)){
            for (int buffer_tracker = 0; buffer_tracker < line.length() - 3; buffer_tracker++){
                string buffer = line.substr(buffer_tracker, 4);
                //cout << buffer << endl;
                // check if first char in buffer matches any others
                if ((buffer.substr(1, 3)).find(buffer[0])==string::npos){
                    if((buffer.substr(2, 2)).find(buffer[1])==string::npos){
                        if(buffer[2]!=buffer[3]){
                            found_unique = buffer_tracker + 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    my_file.close();
    // +3 because found_unique is the first char in the buffer, but they want the last one
    return found_unique + 3;
}


// return the char # where the first 14 unique characters occur
int day6_part2(string filename){
    string line;
    ifstream my_file;
    int found_unique = -1;
    my_file.open(filename);
    if (my_file.is_open()){
        while(getline(my_file, line)){
            for (int buffer_tracker = 0; buffer_tracker < line.length() - 13; buffer_tracker++){
                string buffer = line.substr(buffer_tracker, 14);
                //cout << buffer << endl;
                bool matching_found = false;
                // check if each char in the string matches any others
                // at first, check if the first char can be found in the substr, then the second, etc.
                for (int i = 0; i < 14; i++){
                    if ((buffer.substr(i+1, 14-1)).find(buffer[i])!=string::npos){
                        matching_found = true;
                        break;
                    }
                }
                if (matching_found == false){
                    found_unique = buffer_tracker + 1;
                    break;
                }
            }
        }
    }
    my_file.close();
    // +3 because found_unique is the first char in the buffer, but they want the last one
    return found_unique + 13;
}
