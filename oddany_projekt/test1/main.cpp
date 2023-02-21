#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>
#include "functions.h"
//#include <stdexcept>



int main(int argc, char* argv[])
{
    Args args = parseArgs(argc, argv);


    std::ifstream input_file(args.input); 
    std::ifstream tree_file(args.tree); 
    std::ofstream output_file(args.output); 


    info(input_file, output_file);                               ///tworzy wektor v kotrego zawartosc bedzie rowna readinputfile, pearsondata to wektor map stringow i doubli
    PersonData v = readInputFile(input_file, output_file);       ///wektor nodow on sie nazwya tree i bedzie zapelniony readtreefile 
    std::vector<Node*> tree = readTreeFile(tree_file);  
    connectNodes(tree);                                          /// wektor tree czyta plik drzewa i je przechowuje
                                                                 ///sprawda czy 2 ostatnie dane czy to liczba czy tekst bo jak jest liczba to jest wskaznik na nastepny wezel a jezeli tekst to wskaznik na przypisanie etykiety 

    for (int i = 0; i < v.size(); i++) {                         /// funkcjonalosc wypisywania po kolei danych zawodnikow i do czego zostali dopisani
        for (auto const& x : v[i]) {                             ///najpierw przechodzi przez wektor v - wektor przechowuje mapy, a mapa ma klucz i wartosc
            output_file << x.second << " "; 
        }                                                        /// first napis np.wzrost, second liczba
        output_file << decide(tree[0], v[i]) << std::endl;       ///wypisywanie decyzji np.k lub l
    }

    for (int i = 0; i < tree.size(); i++) {                      /// zawlnianie pamiêci, jak skonczy sie wszytsko dziac to przechodzi przez cale drzewo binarne i usuwa galezie
        delete tree[i]; 
    }

    output_file.close(); 
    input_file.close();
    //tree_file.close();
}

