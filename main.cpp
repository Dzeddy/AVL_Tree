#include <iostream>
#include <fstream>
#include <string>
#include "AVL_Tree.h"
#include <regex>
#include <unordered_map>
#include <filesystem>

using namespace std;

int main() {

    string input_dir = "./input-files/";
    string output_dir = "./output-files/";

    // Define regular expressions for the input commands
    std::regex insert_regex("insert \"([^\"]*)\"\\s*(\\d+)");
    regex remove_regex("remove (\\d{8})");
    regex search_id_regex("search (\\d+)");
    regex search_name_regex("search \"([^\"]*)\"");
    regex inorder_regex("removeInorder (\\d+)");
    regex print_order_regex("print(Inorder|Preorder|Postorder)");
    regex print_level_count_regex("printLevelCount");

    for (const auto &entry: filesystem::directory_iterator(input_dir)) {
        if (entry.is_regular_file()) {
            AVL_Tree tree;
            string input_file = entry.path().string();
            string output_file = output_dir + entry.path().filename().string();

            string line;
            int count = 0;
            ifstream infile(input_file);
            ofstream outfile(output_file);

            if (!infile) {
                cerr << "Error: could not open input file " << input_file << endl;
                continue;
            }

            if (!outfile) {
                cerr << "Error: could not open output file " << output_file << endl;
                continue;
            }

            // Redirect cout to the output file
            cout.rdbuf(outfile.rdbuf());

            infile >> count;
            getline(infile, line);

            while (count--) {
                getline(infile, line);
                //match the input line with the regular expressions
                if (regex_match(line, insert_regex)) {
                    std::regex key_regex("^[0-9]+$");
                    //if the input line matches the insert command, extract the name and id from the line
                    smatch match;
                    regex_search(line, match, insert_regex);
                    string name = match[1];
                    int id = stoi(match[2]);
                    std::string id_str = match[2];
                    if (!regex_match(id_str, key_regex) || id_str.length() != 8) {
                        outfile << "unsuccessful" << endl;
                        continue;
                    }
                    //insert the name and id into the tree
                    tree.insert(id, name);
                } else if (regex_match(line, remove_regex)) {
                    //if the input line matches the remove command, extract the id from the line
                    smatch match;
                    regex_search(line, match, remove_regex);
                    int id = stoi(match[1]);

                    //remove the id from the tree
                    tree.remove(id);
                } else if (regex_match(line, search_id_regex)) {
                    //if the input line matches the search by id command, extract the id from the line
                    smatch match;
                    regex_search(line, match, search_id_regex);
                    int id = stoi(match[1]);

                    //search the tree for the id
                    tree.search(id);
                } else if (regex_match(line, search_name_regex)) {
                    //if the input line matches the search by name command, extract the name from the line
                    smatch match;
                    regex_search(line, match, search_name_regex);
                    string name = match[1];

                    //search the tree for the name
                    tree.searchName(name);
                } else if (regex_match(line, print_order_regex)) {
                    //if the input line matches the print command, extract the order
                    smatch match;
                    regex_search(line, match, print_order_regex);
                    string order = match[1];
                    //print the tree in the specified order
                    if (order == "Inorder") {
                        tree.inOrder();
                    } else if (order == "Preorder") {
                        tree.preOrder();
                    } else if (order == "Postorder") {
                        tree.postOrder();
                    }
                } else if (regex_match(line, print_level_count_regex)) {
                    //if the input line matches the print level count command, print the level count
                    tree.printLevelCount();
                } else if (regex_match(line, inorder_regex)) {
                    //if the input line matches the remove inorder command, extract the id from the line
                    smatch match;
                    regex_search(line, match, inorder_regex);
                    int id = stoi(match[1]);

                    //remove the id from the tree using the remove inorder function
                    tree.removeInOrder(id);
                } else {
                    //if the input line does not match any of the commands, print unsuccessful
                    outfile << "unsuccessful" << endl;
                }
            }

            infile.close();
            outfile.close();
        }
    }

    return 0;
}