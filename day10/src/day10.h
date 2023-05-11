#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <regex>
#include <cmath>

// return sum of 20th, 60th, 100th, 140th, 180th, and 220th cycles
int day10_part1(std::string filename){
    std::string line;
    std::ifstream my_file;
    int reg_value = 1;
    int cycle_count = 0;
    std::vector<int> historic_reg_values;
    my_file.open(filename);
    if (my_file.is_open()){
        while(getline(my_file, line)){
            // parse command
            if (line.substr(0, 4) == "noop"){
                historic_reg_values.push_back(reg_value);
            }
            else{
                historic_reg_values.push_back(reg_value);
                // check for negative
                if (line.substr(5, 1) == "-"){
                    std::regex r("addx -(\\d+)");
                    std::smatch m;
                    std::regex_search(line, m, r);
                    reg_value -= stoi(m.str(1));
                    historic_reg_values.push_back(reg_value);
                }
                else{
                std::regex r("addx (\\d+)");
                std::smatch m;
                std::regex_search(line, m, r);
                reg_value += stoi(m.str(1));
                historic_reg_values.push_back(reg_value);
                }
            }
        }
    }
    int value_sum = 0;
    for (int i = 20; i < 222; i+=40){
        value_sum += historic_reg_values[i-2] * i;
        std::cout<< historic_reg_values[i-2] << std::endl;
    }
    return value_sum;
}


// output screen seen on cathode crt
void day10_part2(std::string filename){
    std::string line;
    std::ifstream my_file;
    int reg_value = 1;
    int cycle_count = 0;
    std::vector<int> historic_reg_values;
    historic_reg_values.push_back(1);
    my_file.open(filename);
    if (my_file.is_open()){
        while(getline(my_file, line)){
            // parse command
            if (line.substr(0, 4) == "noop"){
                historic_reg_values.push_back(reg_value);
            }
            else{
                historic_reg_values.push_back(reg_value);
                // check for negative
                if (line.substr(5, 1) == "-"){
                    std::regex r("addx -(\\d+)");
                    std::smatch m;
                    std::regex_search(line, m, r);
                    reg_value -= stoi(m.str(1));
                    historic_reg_values.push_back(reg_value);
                }
                else{
                std::regex r("addx (\\d+)");
                std::smatch m;
                std::regex_search(line, m, r);
                reg_value += stoi(m.str(1));
                historic_reg_values.push_back(reg_value);
                }
            }
        }
    }
    // print a 40x6 display
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 40; j++){
            //std::cout << historic_reg_values[i * 40 + j] << std::endl;

            //if (abs(historic_reg_values[(i * 40) + j] - i * 40 - j) < 2){
            if (abs(historic_reg_values[(i * 40) + j] - j) < 2){
                std::cout << "#";
            }
            else{
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}
