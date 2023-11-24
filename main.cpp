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
    indexarLibro indexador;
    string ruta = "Libros";
    bool salir = false;
    indexador.indexar(ruta);
    indexador.imprimirDocumentos();
    cout << indexador.cantidadDocumentos() << endl;
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
            vector<pair<int, double>> resultados = indexador.buscar(consulta);
            vector<string> palabras = split(consulta, ' ');
            if (resultados.empty()) {
                cout << "No se encontraron resultados" << endl;
            }
            else {
                cout << "Resultados de la búsqueda:" << endl;
                for (auto& resultado : resultados) {
                    cout << "Documento: " << indexador.getDocumento(resultado.first).getTitulo() << " - Relevancia: " << resultado.second << endl;
                }
            }
            indexador.indexarTablaHash(palabras);
            indexador.getTablaHash().imprimir();
        }
    }

    return 0;
}
