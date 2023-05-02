#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <regex>
using namespace std;

// return crate on the top of each pile:
// each pile is essentially a stack
vector<char> day5_part1(string filename){
    // find number of pairs that are fully contained within the other
    string line;
    ifstream my_file;
    bool stack_reached = false;
    bool instructions_reached = false;
    bool stacks_initialized = false;
    vector<char> tops_of_stacks;
    vector<stack<char>> stacks; // each pile is basically a stack
    vector<vector<char>> unorganized_stacks; // used to parse the input file before I know the bottom of the stack
    my_file.open(filename);
    if (my_file.is_open()){
        while(getline(my_file, line)){
            if(stacks_initialized == false){
                // initialize stacks based on length of line
                stacks.resize((line.length()+1)/4);
                unorganized_stacks.resize((line.length()+1)/4);
                stacks_initialized = true;
            }
            // parse the first lines for stacks
            // until I reach a bunch of numbers in a row
            if (stack_reached == false){
                int line_tracker = 0;
                // iterate through the line, stopping at each number
                while(line_tracker <= line.length()){
                    // if it's a char, we're still dealing with a stack of crates
                    if (line[line_tracker] == '['){
                        unorganized_stacks[line_tracker / 4].push_back(line[line_tracker +1]);
                    }
                    // otherwise we're starting the stack order
                    else if (line[line_tracker +1] > '0'){
                        stack_reached = true;
                        break;
                    }
                    // each pile takes up exactly four spaces, whether it's there or not
                    line_tracker += 4;
                }
            }
            // we'll have two lines where nothing happens
            else if (instructions_reached == false){
                if (line[0] == 'm'){
                    instructions_reached = true;

                    // initialize the stacks here
                    for (int i = 0; i < unorganized_stacks.size(); i++){
                        for (int j = unorganized_stacks[i].size()-1; j >= 0; j--){
                            // push the items in reverse order for the vectors
                            stacks[i].push(unorganized_stacks[i][j]);
                        }
                    }
                }
            }
            if (instructions_reached == true){
                // parse instructions
                regex r("move (\\d+) from (\\d+) to (\\d+)");
                smatch m;
                regex_search(line, m, r);
                int num_items_move = stoi(m.str(1));
                int stack_from = stoi(m.str(2));
                int stack_to = stoi(m.str(3));
                for (int i = 0; i < num_items_move; i++){
                    stacks[stack_to-1].push(stacks[stack_from-1].top());
                    stacks[stack_from-1].pop();

                }
            }
        }
    }
    my_file.close();
    for (int i = 0; i < stacks.size(); i++){
        tops_of_stacks.push_back(stacks[i].top());
    }
    return tops_of_stacks;
}

// only difference from part 1 is that multiple boxes get moved at one time
vector<char> day5_part2(string filename){
    // find number of pairs that are fully contained within the other
    string line;
    ifstream my_file;
    bool stack_reached = false;
    bool instructions_reached = false;
    bool stacks_initialized = false;
    vector<char> tops_of_stacks;
    vector<stack<char>> stacks; // each pile is basically a stack
    vector<vector<char>> unorganized_stacks; // used to parse the input file before I know the bottom of the stack
    my_file.open(filename);
    if (my_file.is_open()){
        while(getline(my_file, line)){
            if(stacks_initialized == false){
                // initialize stacks based on length of line
                stacks.resize((line.length()+1)/4);
                unorganized_stacks.resize((line.length()+1)/4);
                stacks_initialized = true;
            }
            // parse the first lines for stacks
            // until I reach a bunch of numbers in a row
            if (stack_reached == false){
                int line_tracker = 0;
                // iterate through the line, stopping at each number
                while(line_tracker <= line.length()){
                    // if it's a char, we're still dealing with a stack of crates
                    if (line[line_tracker] == '['){
                        unorganized_stacks[line_tracker / 4].push_back(line[line_tracker +1]);
                    }
                    // otherwise we're starting the stack order
                    else if (line[line_tracker +1] > '0'){
                        stack_reached = true;
                        break;
                    }
                    // each pile takes up exactly four spaces, whether it's there or not
                    line_tracker += 4;
                }
            }
            // we'll have two lines where nothing happens
            else if (instructions_reached == false){
                if (line[0] == 'm'){
                    instructions_reached = true;

                    // initialize the stacks here
                    for (int i = 0; i < unorganized_stacks.size(); i++){
                        for (int j = unorganized_stacks[i].size()-1; j >= 0; j--){
                            // push the items in reverse order for the vectors
                            stacks[i].push(unorganized_stacks[i][j]);
                        }
                    }
                }
            }
            if (instructions_reached == true){
                // parse instructions
                regex r("move (\\d+) from (\\d+) to (\\d+)");
                smatch m;
                regex_search(line, m, r);
                int num_items_move = stoi(m.str(1));
                int stack_from = stoi(m.str(2));
                int stack_to = stoi(m.str(3));
                // need to make a stack of what is being moved to account
                // for multiple being moved at a time
                stack<char> order_to_move;
                for (int i = 0; i < num_items_move; i++){
                    order_to_move.push(stacks[stack_from-1].top());
                    stacks[stack_from-1].pop();
                }
                for (int i = 0; i < num_items_move; i++){
                    stacks[stack_to-1].push(order_to_move.top());
                    order_to_move.pop();
                }
            }
        }
    }
    my_file.close();
    for (int i = 0; i < stacks.size(); i++){
        tops_of_stacks.push_back(stacks[i].top());
    }
    return tops_of_stacks;
}
