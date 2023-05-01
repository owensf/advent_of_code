#include <iostream>
#include <fstream>
#include <string>
#define ENEMY_ROCK 65
#define ENEMY_PAPER 66
#define ENEMY_SCISSORS 67
#define MY_ROCK 88
#define MY_PAPER 89
#define MY_SCISSORS 90
using namespace std;

int day1_part1(){
    string line;
    ifstream myfile;
    int myscore = 0;
    myfile.open("C:/Users/Fred/eclipse-workspace/day2/src/input.txt");
    if (myfile.is_open()){
        while(getline(myfile, line)){
            char enemy_throw = line[0];
            char my_throw = line[2];
            //wins
            //rock > scissors
            if ((my_throw == 88) && (enemy_throw == 67)){
                myscore += 6;
            }
            // paper > rock
            else if ((my_throw == 89) && (enemy_throw == 65)){
                myscore += 6;
            }
            // scissors > paper
            else if ((my_throw == MY_SCISSORS) && (enemy_throw == 66)){
                myscore += 6;
            }
            else if (my_throw -23 == enemy_throw){
                myscore += 3;
            }
            // ASCII X is 88
            myscore += my_throw - 87;
            //cout << enemy_throw << my_throw << myscore << endl;
        }
        myfile.close();
    }
    cout << "My score: " << myscore << endl;
    return 0;
}

int day2_part2(){
    string line;
    ifstream myfile;
    int myscore = 0;
    myfile.open("C:/Users/Fred/eclipse-workspace/day2/src/input.txt");
    if (myfile.is_open()){
        while(getline(myfile, line)){
            char enemy_throw = line[0];
            char my_throw = line[2];
            //wins: I throw MY_SCISSORS
            if (my_throw == MY_SCISSORS){
                // opponent throws rock: I need to throw paper
                if (enemy_throw == 65){
                    myscore += 8;
                }
                // I throw scissors
                else if (enemy_throw == 66){
                    myscore += 9;
                }
                else{
                    myscore += 7;
                }
            }
            // ties: I throw 89
            else if (my_throw == 89){
                if (enemy_throw == ENEMY_ROCK){
                    myscore += 4;
                }
                else if (enemy_throw == ENEMY_PAPER){
                    myscore += 5;
                }
                else{
                    myscore += 6;
                }
            }
            // lose
            else if (my_throw == 88){
                if (enemy_throw == ENEMY_ROCK){
                    myscore += 3;
                }
                else if (enemy_throw == ENEMY_PAPER){
                    myscore += 1;
                }
                else{
                    myscore += 2;
                }
            }
        }
        myfile.close();
    }
    cout << "My score: " << myscore << endl;
    return 0;
}
