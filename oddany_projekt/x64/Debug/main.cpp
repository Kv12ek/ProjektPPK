#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "functions.h"





int main(int argc, char* argv[])
{
    Args args = parseArgs(argc, argv);

    
    std::ifstream input_file(args.input); 
    std::ifstream tree_file(args.tree); 
    std::ofstream output_file(args.output); 



    info(input_file, output_file);
    PersonData v = readInputFile(input_file, output_file); 
    std::vector<Node*> tree = readTreeFile(tree_file);  
    connectNodes(tree); 
    

    for (int i = 0; i < v.size(); i++) { 
        for (auto const& x : v[i]) { 
            output_file << x.second << " "; 
        } 
        output_file << decide(tree[0], v[i]) << std::endl; 
    }

    for (int i = 0; i < tree.size(); i++) { 
        delete tree[i]; 
    }

    output_file.close(); 
    input_file.close();
    tree_file.close();

}

/*int main(int argc, char* argv[]) {
    Args args;
    try {
        args = parseArgs(argc, argv);
    }
    catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::ifstream input_file(args.input);
    if (!input_file.is_open()) {
        std::cerr << "Error: cannot open input file " << args.input << std::endl;
        return 1;
    }

    std::ofstream output_file(args.output);
    if (!output_file.is_open()) {
        std::cerr << "Error: cannot open output file " << args.output << std::endl;
        return 1;
    }

    std::vector<Node*> tree;
    std::ifstream tree_file(args.tree);
    if (!tree_file.is_open()) {
        std::cerr << "Error: cannot open tree file " << args.tree << std::endl;
        return 1;
    }

    try {
        info(input_file, output_file);
        PersonData person_data = readInputFile(input_file, output_file);
        tree = readTreeFile(tree_file);
        connectNodes(tree);

        for (int i = 0; i < person_data.size(); i++) {
            std::string result = decide(tree[0], person_data[i]);
            output_file << result << std::endl;
        }

    }
    catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    input_file.close();
    output_file.close();
    tree_file.close();

    return 0;
}*/