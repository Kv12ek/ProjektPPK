#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>


struct Args {
    std::string input, tree, output; 
};


struct Node {
    std::string key;
    std::string argument;
    std::string op;
    double value{};
    std::string l;
    std::string r;
    Node* left = nullptr;
    Node* right = nullptr;
};

typedef std::vector<std::map<std::string, double> > PersonData; // zbedne dane (string)

Args parseArgs(int argc, char* argv[]);

PersonData readInputFile(std::ifstream& input_file, std::ofstream& output_file);

std::vector<Node*> readTreeFile(std::ifstream& tree_file);

bool isNumber(const std::string s);

void connectNodes(std::vector<Node*>& tree);

std::string decide(Node* root, std::map<std::string, double>& person);

void info(std::ifstream& input_file, std::ofstream& output_file);

