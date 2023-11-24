#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cmath>
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
    string ruta = "Libros/";

    indexarLibro indexador = indexarLibro(ruta);
    bool salir = false;

    while(!salir){
        string consulta;
        cout << "Ingrese la consulta a buscar (\"salir\" termina el programa): ";
        getline(cin, consulta);
        if (consulta == "salir") {
            salir = true;
        }
        else if (consulta.empty()) {
            cout << "Debe ingresar una consulta" << endl;
            continue;
        }
        else {
            continue;
        }
    }

    return 0;
}
