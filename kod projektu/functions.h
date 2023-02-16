/** @file */
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

/**
 * @brief Structure with information about the input, tree and outpup file extracted from the CLI arguments.
*/
struct Args{
    std::string input, tree, output;
};

/**
 * @brief Structure of a node extracted from the tree file.
*/
struct Node {
    std::string key;
    std::string argument;
    std::string op;
    double value;
    std::string l;
    std::string r;
    Node* left;
    Node* right;
};

typedef std::vector<std::map<std::string, double> > PersonData;

/**
 * @brief Parse arguments from command line, check if there are enough of them and if they are correct, else print error.
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 * @return Returns structure with parsed arguments.
*/
Args parseArgs(int argc, char* argv[]);

/**
 * @brief Reads the input file and stores the information in a vector.
 * @param input_file File stream with opened file containing necessary data.
 * @return Returns a vector of maps containing all the information from the input file ordered (argument : value).
*/
PersonData readInputFile(std::ifstream& input_file, std::ofstream& output_file);

/**
 * @brief Reads the file tree and creates nodes containing arguments and values from the file. 
 * @param tree_file File stream with opened file containing the tree's structure.
 * @return Returns a vector of nodes with parameters and values extracted from the file.
*/
std::vector<Node*> readTreeFile(std::ifstream& tree_file);

/**
 * @brief Checks if the parameter is a number. 
 * @param s A string which we want to check. 
 * @return Returns true if the string contains a number and false if it doesn't.
*/
bool isNumber(const std::string s);

/**
 * @brief Connects nodes if the pointer to the l or r parameter is a number.
 * @param tree A vector of nodes that we want to connect.
*/
void connectNodes(std::vector<Node*>& tree);

/**
 * @brief Traverses through the the tree recursively and decides where to assign certain example from the data file.
 * @param root The root of the tree.
 * @param person Map containing data about certain person.
 * @return Returns a string which is the category a person was assigned to.
*/
std::string decide(Node* root, std::map<std::string, double>& person);

void info(std::ifstream& input_file, std::ofstream& output_file);
    