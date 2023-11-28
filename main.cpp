/**
 * @file main.cpp
 * 
 * @brief Implementación del programa principal.
 * 
 * @author Jeffry Araya Ch
 * 
 * @date 28/11/2023 14:00
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "SusAndAdj.cpp"
#include "IndexarLibro.h"


/**
 * @brief Divide una cadena en subcadenas utilizando delimitadores como ' ' o ',' o ';' o '.' o ':'.  
 * @param str La cadena que se va a dividir.
 * @return vector<string> Un vector que contiene las subcadenas resultantes.
 */
vector <string> split(string str){
    vector <string> resultado;
    stringstream ss(str);
    string token;
    while(getline(ss, token, ' ') || getline(ss, token, ',') || getline(ss, token, ';') || getline(ss, token, '.') || getline(ss, token, ':') || getline(ss, token, '?') || getline(ss, token, '!')){
        resultado.push_back(token);
    }
    return resultado;
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
            //vector<pair<int, double>> resultados = indexador.buscar(consulta);
            vector<string> palabras = split(consulta);
            if (indexador.getTablaHash().estaVacia()) {
                cout << "Indexando la tabla" << endl;
                indexador.indexarTablaHash(palabras);
            }else{
                cout << "Actualizando la tabla" << endl;
                indexador.actualizarTablaHash(palabras);
            }
            cout << "Resultados de la búsqueda: " << endl;
            indexador.getTablaHash().imprimir();
            cout << "Libros: " << endl;
            indexador.getTablaHash().imprimirLibros();
            cout << "Libro con más apariciones: " << endl;
            cout << indexador.getTablaHash().libroConMasApariciones().getTitulo() << endl;
            cout << "top 10 matches: " << endl;
            vector<Documento> topMatches = indexador.getTablaHash().getTopMatches(palabras);
            cout << "----------------------------------------" << endl;
            for (auto& libro : topMatches) {
                cout << "----------------------------------------" << endl;
                cout << "Libro: " << libro.getTitulo() << endl;
                cout << "Autor: " << libro.getAutor() << endl;
                cout << "----------------------------------------" << endl;
            }
            cout << "----------------------------------------" << endl;
            cout << topMatches.size() << " resultados" << endl;
        }
    }


    return 0;
}
