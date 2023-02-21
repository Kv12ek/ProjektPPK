#include "functions.h"


Args parseArgs(int argc, char* argv[]) { //wywolanie funkcji ktora przechodzi przez argumenty czyli przez przelaczniki w funkcji.h
    Args arg; 
    // funkcja przechodzi przez wszystkie argumenty i przypisuje do odpowiednigo elementu tej struktury 
    if (argc != 7) throw std::runtime_error("Not enough arguments provided");

    for (int i = 0; i < argc; i++) {
        std::string val = argv[i];

        if (val == "-i") {
            if (i == argc - 1) throw std::runtime_error("No input file provided");
            arg.input = argv[i + 1]; 
        }
        else if (val == "-t") {
            if (i == argc - 1) throw std::runtime_error("No tree file provided");
            arg.tree = argv[i + 1];
        }
        else if (val == "-o") {
            if (i == argc - 1) throw std::runtime_error("No output file provided");
            arg.output = argv[i + 1];
        }
        //else {
        //    std::cout << "Wyjatek";
        //}
    }
    return arg;  
}


bool isNumber(const std::string s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}


PersonData readInputFile(std::ifstream& input_file, std::ofstream& output_file) {


    PersonData v;
    std::string line;
    std::vector<std::string> keys;                                  /// klucze  one przechowuja to samo jednego uzywam szybciej niz drugiego
    std::vector<std::string> cats;                                  /// kategorie

    getline(input_file, line);                                      ///funckja ktora bierze z pliku wejsciowego linie i zapisuje j¹ do line1
    line = line.substr(0, line.find('%'));                          ///funkcja od zerowgo indexu do idexu, jak znjadzie % to obetnie ten string
    std::stringstream ss;                                           ///strumieniowanie
    ss << line; 
    std::string tmp;                                                /// zmienna tymczasowa temporary
    while (ss >> tmp) {
        keys.push_back(tmp);
        cats.push_back(tmp);

    }
    std::sort(cats.begin(), cats.end());                            /// sortowanie alfabetycznie kategorii
    for (int i = 0; i < cats.size(); i++) {                         /// przejscie przez caly wektor kategorii
        output_file << cats[i] << " ";                              ///przy kazdej kategorii sie zatrzymuje i wypisuje ja w tym pliku i dje spacje
    }
    output_file << "%nazwy atrybutow" << std::endl;

    while (getline(input_file, line)) {
        std::map<std::string, double> map;
        line = line.substr(0, line.find('%'));
        std::stringstream s;
        s << line;                                                  /// stringstream
        double val;
        for (int i = 0; i < keys.size(); i++) {
            s >> val;
            map[keys[i]] = val;                                    /// przechodzi przez kazdy klucz i dodaje mu wartosci do mapy. Tworzy mape i zwraca
        }
        v.push_back(map);
    }


    return v;  
}

                                                                    /// fukcja ktora czyta dane nizej i zwraca je do mapy do wektora v
std::vector<Node*> readTreeFile(std::ifstream& tree_file) {
    std::string line1;
    int num;
    std::getline(tree_file, line1);
    line1 = line1.substr(0, line1.find('%'));
    std::stringstream ss;
    ss << line1;                                                       /// ss zmienna globalna 
    ss >> num;

    std::vector<Node*> tree;

    std::string line, key, argument, op, l, r;
    double value;

    while (std::getline(tree_file, line)) {
        line = line.substr(0, line.find('%'));
        std::stringstream ss;
        ss << line;
        ss >> key >> argument >> op >> value >> l >> r;
        Node* node = new Node; 
        node->key = key;                                            /// wskaznik na 
        node->argument = argument;
        node->op = op;
        node->value = value;
        node->l = l;
        node->r = r;
        tree.push_back(node);                                       /// dodawanie do wektora do tree daje node

    }
    return tree;
}


void connectNodes(std::vector<Node*>& tree) {
    for (int i = 0; i < tree.size(); i++) {
        if (isNumber(tree[i]->l)) {
            tree[i]->left = tree[std::stoi(tree[i]->l)];
        }
        if (isNumber(tree[i]->r)) {
            tree[i]->right = tree[std::stoi(tree[i]->r)];
        }
    }
}


std::string decide(Node* root, std::map<std::string, double>& person) {
    bool right = false; 
    if (root->op == ">") {
        right = root->value < person[root->argument];
    } 
    else if (root->op == "<") { 
        right = root->value > person[root->argument];
    }
    if (right) {
        if (root->right == nullptr) {
            return root->r;
        }
        else {
            return decide(root->right, person);
        }

    }
    else {
        if (root->left == nullptr) {                                        /// sprawdza czy nie ma zawartosci na ktorej jest
            return root->l; 
        }
        else {
            return decide(root->left, person);
        }
    }
}


void info(std::ifstream& input_file, std::ofstream& output_file) { 
    int n, d; 
    std::string line1;
    getline(input_file, line1);
    line1 = line1.substr(0, line1.find('%'));
    std::stringstream sss; 
    sss << line1;
    sss >> n >> d; 
    output_file << n << " " << d << " " << "% " << "n=" << n << " przyk³adow, " << "d=" << d << " atrybuty" << std::endl;
    
}
