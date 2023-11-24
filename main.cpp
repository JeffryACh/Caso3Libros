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
 * @brief Divide una cadena en subcadenas utilizando un delimitador específico.
 * 
 * @param str La cadena que se va a dividir.
 * @param delimiter El delimitador utilizado para separar las subcadenas.
 * @return vector<string> Un vector que contiene las subcadenas resultantes.
 */
vector <string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string tok;

    while(getline(ss, tok, delimiter)) { // getline() lee hasta el delimitador y lo elimina de la cadena original
        internal.push_back(tok); // Se agrega la subcadena al vector
    }

    return internal;
}


/*void eliminarPalabrasRepetidas(string archivo) {
    ifstream file(archivo);
    unordered_set<string> palabras;
    string palabra;

    while (file >> palabra) {
        palabras.insert(palabra);
    }

    file.close();

    ofstream file2(archivo);
    for (auto& palabra : palabras) {
        file2 << palabra << endl;
    }

    file2.close();
}
*/


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
