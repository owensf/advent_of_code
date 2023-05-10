#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <regex>
#include <cmath>

using namespace std;

/*
 * coordinates:
 * x = 0: starting point
 * y = 0: starting point
 * positive x: to the right
 * positive y: up
 */

typedef struct {
    int x;
    int y;
} Position;

class Knot {
    private:
    Position coordinates;
    vector<Position> visited_positions;
    public:
    Knot(){
        coordinates.x = 0;
        coordinates.y = 0;
        //visited_positions = {};
    }
    // move up/down/left/right
    void move(char direction){
        switch(direction){
        case('U'):
            coordinates.y += 1;
            break;
        case('D'):
            coordinates.y -= 1;
            break;
        case('R'):
            coordinates.x += 1;
            break;
        case('L'):
            coordinates.x -= 1;
            break;
        }
    }
    // update a tail in response to the head
    void update_tail(Knot * head){
        // check if we need to move at all
        if (catch_up(head->coordinates)){
            // check if we need to add it to the positions visited vector
            if (check_if_visited(coordinates)){
                visited_positions.push_back(coordinates);
            }
        }
    }

    int count_locations(){
        for (auto point : visited_positions){
            cout << point.x << point.y << endl;
        }
        return visited_positions.size();
    }
    bool check_if_visited(const Position& new_point){
        auto iter = find_if(visited_positions.begin(), visited_positions.end(), [&](const Position& found){
            return ((found.x == new_point.x) && (found.y == new_point.y));});
        return iter == visited_positions.end();
    }
    // returns true if moved, false otherwise
    bool catch_up(const Position& new_point){
        // check if directly up/down
        if (new_point.x == coordinates.x){
            //above
            if (new_point.y - 1 > coordinates.y){
                move('U');
                return true;
            }
            // down
            else if (coordinates.y - 1 > new_point.y){
                move('D');
                return true;
            }
        }
        else if (new_point.y == coordinates.y){
            // right
            if (new_point.x - 1 > coordinates.x){
                move('R');
                return true;
            }
            else if (coordinates.x - 1 > new_point.x){
                move('L');
                return true;
            }
        }
        // dealing with diagnoal
        else{
            // make sure they're not touching diagonally first
            if ((abs(new_point.x - coordinates.x) == 1) && (abs(new_point.y-coordinates.y) == 1)){
                return false;
            }
            // need to do exactly two moves: one left/right and one up/down
            if (new_point.x > coordinates.x){
                move('R');
            }
            else{
                move('L');
            }
            if (new_point.y > coordinates.y){
                move('U');
            }
            else{
                move('D');
            }
            return true;
        }
        return false;
    }

    int return_x(){
        return coordinates.x;
    }
    int return_y(){
        return coordinates.y;
    }
};


// return number of unique locations visited
int day9_part1(string filename){
    string line;
    ifstream my_file;
    Knot head;
    Knot tail;
    my_file.open(filename);
    if (my_file.is_open()){
        while(getline(my_file, line)){
            regex r("(\\w) (\\d+)");
            smatch m;
            regex_search(line, m, r);
            char direction = m.str(1)[0];
            int num_steps = stoi(m.str(2));
            for (int i = 0; i < num_steps; i++){
                head.move(direction);
                tail.update_tail(&head);
            }
        }
    }
    return tail.count_locations();
}
