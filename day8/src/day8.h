#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

typedef struct {
    int height;
    bool visible;
}Tree;

int calc_visibility_score(vector<vector<shared_ptr<Tree>>> trees, int row, int col){
    int tree_height = trees[row][col] -> height;
    int num_left = 0;
    int num_right = 0;
    int num_up = 0;
    int num_down = 0;
    // check left
    for (int i = col - 1; i >= 0; i--){
        num_left++;
        if (trees[row][i] -> height >= tree_height){
            break;
        }
    }
    // check_right;
    for (int i = col + 1; i < trees[row].size(); i++){
        num_right++;
        if (trees[row][i] -> height >= tree_height){
            break;
        }
    }
    // check_up;
    for (int i = row - 1; i >= 0; i--){
        num_up++;
        if (trees[i][col] -> height >= tree_height){
            break;
        }
    }

    // check_down;
    for (int i = row + 1; i < trees.size(); i++){
        num_down++;
        if (trees[i][col] -> height >= tree_height){
            break;
        }
    }
    // if it doesn't break early, it's going to double count the edge
    return num_left * num_right * num_up * num_down;
}

int highest_visibility_score(vector<vector<shared_ptr<Tree>>> trees){
    int highest_score = 0;
    for (int i = 0; i < trees.size(); i++){
        for (int j = 0; j < trees[i].size(); j++){
            int tree_score = calc_visibility_score(trees, i, j);
            if (tree_score > highest_score){
                highest_score = tree_score;
            }
        }
    }
    return highest_score;
}

int count_visible(vector<vector<shared_ptr<Tree>>> trees){
    int num_visible = 0;
    for (vector<shared_ptr<Tree>> tree_row: trees){
        for (shared_ptr<Tree> tree : tree_row){
            if (tree -> visible){
                num_visible++;
            }
        }
    }
    return num_visible;
}

void find_visible_row(vector<shared_ptr<Tree>> tree_row){
    tree_row[0] -> visible = true;
    tree_row[tree_row.size()-1] -> visible = true;
    int largest_height = -1;
    // loop left -> right to check for visibility
    for (int i = 0; i < tree_row.size() - 1; i++){
        if (tree_row[i] -> height > largest_height){
            tree_row[i] -> visible = true;
            largest_height = tree_row[i] -> height;
        }
    }
    largest_height = -1;
    // loop right -> left to check for visibility
    for (int i = tree_row.size() -1; i >= 0; i--){
        if (tree_row[i] -> height > largest_height){
            tree_row[i] -> visible = true;
            largest_height = tree_row[i] -> height;
        }
    }
}

int day8_part1(string filename){
    vector<vector<shared_ptr<Tree>>> trees;
    string line;
    ifstream my_file;
    int row_tracker = 0;

    my_file.open(filename);
    if (my_file.is_open()){
        while(getline(my_file, line)){
            // add a new row
            trees.push_back({});
            for (char tree_height : line){
                shared_ptr<Tree> new_tree(new Tree);
                new_tree -> height = tree_height - '0';
                new_tree -> visible = false;
                trees[row_tracker].push_back(new_tree);
            }
            find_visible_row(trees[row_tracker]);
            row_tracker++;
        }
    }
    my_file.close();
    // rearrange columns as tree vectors. find if they're visible
    int num_cols = trees[0].size();
    for (int i = 0; i < num_cols; i++){
        vector<shared_ptr<Tree>> tree_col;
        for (int j = 0; j < trees.size(); j++){
            tree_col.push_back(trees[j][i]);
        }
        find_visible_row(tree_col);
    }

    cout << "highest vis score" << highest_visibility_score(trees) << endl;

    return count_visible(trees);
}
