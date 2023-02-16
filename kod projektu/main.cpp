/** @file */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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




    for(int i = 0; i<v.size(); i++){
        for(auto const& x : v[i]){
            output_file << x.second << " ";
        }
        output_file << decide(tree[0], v[i]) << std::endl;
    }

    for(int i = 0; i<tree.size(); i++){
        delete tree[i];
    }

    output_file.close();
    input_file.close();


}






