#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <memory>
using namespace std;

/* Node class
 * All nodes have:
 * Size
 * Name
 * Pointer to a Node above
 */
struct Node {
    int size;
    string name;
    bool folder = false;
    vector<shared_ptr<struct Node>> child_files;
    vector<shared_ptr<struct Node>> child_folders;
    vector <string> child_files_names;
    vector <string> child_folders_names;
    shared_ptr<struct Node> parent;
};


/*
struct Dir_Node {
    int size;
    string name;
    vector<File_Node*> files;
    Dir_Node* parent;
};

struct File_Node {
    int size;
    string name;
    Dir_Node* upper;
};
*/
// find all folders with size below 100k
int find_below_100k(shared_ptr<struct Node> current_node){
    int sum_under_100k = 0;
    if (current_node -> size <= 100000){
        sum_under_100k += current_node -> size;
        if (current_node -> size < 0){
            cout << current_node -> name << endl;
        }
    }
    for (shared_ptr<Node> child : current_node -> child_folders){
        sum_under_100k += find_below_100k(child);
    }
    return sum_under_100k;
}


// adds the file size to all parents in the tree
int add_sizes(shared_ptr<struct Node> current_node, int filesize){
    if(current_node -> parent != NULL){
        current_node -> parent -> size += filesize;
        current_node = current_node -> parent;
        add_sizes(current_node, filesize);
    }
    return 0;
}

shared_ptr<Node> find_node_name(shared_ptr<struct Node> parent_node, string name){
    /*for (int i = 0; i < parent_node -> child_folders.size(); i++){
        struct Node* child = parent_node -> child_folders[i];
        cout << child -> name << endl;
        if (child -> name == name){
            return child;
        }
    }*/
    for (shared_ptr<struct Node> child : parent_node -> child_folders){
        if (child -> name == name){
            return child;
        }
    }
    return NULL;
}

int day7_part1(string filename){
    string line;
    ifstream my_file;
    int sum_dirs_below_100k = 0;
    shared_ptr<struct Node> home_node(new Node);
    home_node -> size = 0;
    home_node -> name = "Home";
    home_node -> folder = true;
    home_node -> parent = NULL;
    shared_ptr<struct Node> current_node = home_node;
    int line_number = 0;
    bool lsing_files = false;
    my_file.open(filename);
    if (my_file.is_open()){
        while(getline(my_file, line)){
            line_number++;
            //cout << line_number << endl;
            //cout << current_node -> name << endl;
            //cout << current_node -> size << endl;
            /*
             * User commands:
             * cd
             * ls
             */
            if (line.substr(0, 1) == "$"){
                if (line.substr(2, 2) == "cd"){
                    lsing_files = false;
                    if (line[5] == '/'){
                        current_node = home_node;
                    }
                    else if (line.substr(5, 2) == ".."){
                        current_node = current_node -> parent;
                    }
                    else {
                        regex r("cd (\\w+)");
                        smatch m;
                        regex_search(line, m, r);
                        string folder_name = m.str(1);
                        /*for (int i = 0; i < current_node-> child_folders.size(); i++){
                            struct Node* child = current_node -> child_folders[i];
                            cout << child -> name << endl;
                        }*/
                        current_node = find_node_name(current_node, folder_name);
                    }
                }
                else if (line.substr(2, 2) == "ls"){
                    lsing_files = true;
                }
            }
            else if (lsing_files == true){
                if (line.substr(0, 3) == "dir"){
                    // check if dir already exists
                    regex r("dir (\\w+)");
                    smatch m;
                    regex_search(line, m, r);
                    string folder_name = m.str(1);
                    if (find(current_node -> child_folders_names.begin(), current_node -> child_folders_names.end(), folder_name) == current_node-> child_folders_names.end()){
                        shared_ptr<struct Node> child_folder(new Node);
                        child_folder -> size = 0;
                        child_folder -> name = folder_name;
                        //cout << child_folder -> name << endl;
                        child_folder -> folder = true;
                        child_folder -> parent = current_node;
                        current_node -> child_folders.push_back(child_folder);
                        /*for (int i = 0; i < current_node-> child_folders.size(); i++){
                             cout << current_node -> child_folders.size();
                             struct Node* child = current_node -> child_folders[i];
                             cout << child -> name << endl;
                         }*/
                        /*for (struct Node* child: current_node -> child_folders){
                            cout << child -> name << endl;
                        }*/
                        current_node -> child_folders_names.push_back(folder_name);
                    }
                }
                // it's a file
                else{
                    // check if file exists
                    //regex r("(\\d+) (\\w+.\\w+)");
                    regex r ("(\\d+) ([A-Za-z.]+)");
                    smatch m;
                    regex_search(line, m, r);
                    string child_filename = m.str(2);
                    if (find(current_node -> child_files_names.begin(), current_node ->child_files_names.end(), child_filename) == current_node -> child_files_names.end()){
                        shared_ptr<struct Node> child_node(new Node);
                        child_node -> size = stoi(m.str(1));
                        child_node -> name = child_filename;
                        child_node -> folder = false;
                        child_node -> parent = current_node;
                        /*if (child_node -> size < 0){
                            cout << child_node -> name << endl;
                        }*/
                        add_sizes(child_node, child_node -> size);
                        current_node -> child_files.push_back(child_node);
                        current_node -> child_files_names.push_back(child_filename);
                        /*for (struct Node* child: current_node -> child_files){
                            cout << "child filenames!" << endl;
                            cout << child -> name << endl;
                        }*/
                    }
                }
            }
        }
    }
    my_file.close();
    // add up folders at the end

    sum_dirs_below_100k = find_below_100k(home_node);
    return sum_dirs_below_100k;
}
