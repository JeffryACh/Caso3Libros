#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <algorithm>
//#include "LibroIndex.h"
//#include "Libro.h"
#include "SusAndAdj.cpp"
//#include "TipoDePalabra.cpp"
//#include "RankingLibros.h"
//#include "IndexadorLibros.h"

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
