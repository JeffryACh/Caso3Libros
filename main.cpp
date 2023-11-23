#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include "SusAndAdj.cpp"
//#include "RankingLibros.h"
#include "IndexarLibro.h"

/**
 * @brief Divide a string into substrings based on a delimiter.
 * 
 * @param str The string to be split.
 * @param delimiter The character used to separate the substrings.
 * @return vector<string> A vector containing the substrings.
 */
vector <string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

int main() {
    std::string frase;

    std::cout << "Ingresa una frase: ";
    std::getline(std::cin, frase);

    std::cout << "Sustantivos y Adjetivos en la frase:" << std::endl;
    for (auto& palabra : split(frase, ' ')) {
        if (esSustantivo(palabra)) {
            std::cout << palabra << " es un sustantivo" << std::endl;
        } else if (esAdjetivo(palabra)) {
            std::cout << palabra << " es un adjetivo" << std::endl;
        } else {
            continue;
        }
    }

    return 0;
}
