#include "TablaHash.h"
#include <iostream>
#include <string>

using namespace std;

TablaHash::TablaHash() {
} // constructor

/**
 * @brief Inserta una palabra y un libro en la tabla hash.
 * 
 * Si la palabra no se encuentra en la tabla, se crea un nuevo vector vacío y se agrega el libro con una frecuencia de 1.
 * Si la palabra ya existe en la tabla, se busca el libro en el vector asociado a la palabra.
 * Si el libro se encuentra, se incrementa su frecuencia en 1.
 * Si el libro no se encuentra, se agrega al vector con una frecuencia de 1.
 * 
 * @param palabra La palabra a insertar.
 * @param libro El libro asociado a la palabra.
 */
void TablaHash::insertar(string palabra, Documento libro) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se crea un vector vacío
        vector<pair<Documento, int>> libros;
        libros.push_back(make_pair(libro, 1));
        tabla[palabra] = libros;
    } else {
        bool libroEncontrado = false;
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) { // se busca el libro en el vector asociado a la palabra
            if (it->first.getTitulo() == libro.getTitulo()) { // si el libro se encuentra, se incrementa su frecuencia en 1
                it->second++; // se incrementa la frecuencia del libro en 1
                libroEncontrado = true;
                break;
            }
        }
        if (!libroEncontrado) {
            tabla[palabra].push_back(make_pair(libro, 1));
        }
    }
}

/**
 * @brief Busca una palabra en la tabla hash y devuelve los documentos asociados a esa palabra.
 * 
 * @param palabra La palabra a buscar en la tabla hash.
 * @return Un vector de pares (Documento, int) que representa los documentos asociados a la palabra.
 *         Si la palabra no se encuentra, se retorna un vector vacío.
 */
vector<pair<Documento, int> > TablaHash::buscar(string palabra) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se retorna un vector vacío
        return vector<pair<Documento, int>>();
    } else {
        return tabla[palabra];
    }
}

/**
 * Imprime los elementos almacenados en la tabla hash.
 * 
 * Recorre la tabla hash e imprime cada elemento junto con su cantidad.
 * 
 * @param None
 * @return None
 */
void TablaHash::imprimir() {
    for (auto it = tabla.begin(); it != tabla.end(); it++) {
        cout << it->first << ": " << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << "\t" << it2->first.getTitulo() << " (" << it2->second << ")" << endl;
        }
    }
}

/**
 * Imprime los libros almacenados en la tabla hash.
 * 
 * Recorre la tabla hash e imprime los títulos y autores de los libros almacenados.
 */
void TablaHash::imprimirLibros() {
    for (auto it = tabla.begin(); it != tabla.end(); it++) {
        cout << it->first << ": " << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << "Titulo: " << it2->first.getTitulo() << " - " << "Autor: "<< it2->first.getAutor() << endl;
        }
    }
}

/**
 * @brief Clase que representa un documento.
 * 
 * @param palabra La palabra a buscar en la tabla hash.
 * 
 * Esta clase representa un documento y contiene información sobre el mismo, como el título, el autor y el número de apariciones de una palabra en el documento.
 * 
 * @return Un Documento que representa el libro con más apariciones de la palabra.
 */
Documento TablaHash::buscarLibroConMasApariciones(string palabra) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se retorna un libro vacío
        return Documento();
    } else {
        int max = 0;
        Documento libroConMasApariciones;
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->second > max) {
                max = it->second;
                libroConMasApariciones = it->first;
            }
        }
        return libroConMasApariciones;
    }
}

/**
 * Obtiene los documentos con las mejores coincidencias para una palabra dada.
 * 
 * @param palabra La palabra para la cual se desean obtener las mejores coincidencias.
 * @return Un vector de Documento con los documentos que tienen las mejores coincidencias para la palabra dada.
 *         Si no se encuentra la palabra, se retorna un vector vacío.
 */
vector<Documento> TablaHash::getTopMatches(string palabra) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se retorna un vector vacío
        return vector<Documento>();
    } else {
        vector<Documento> topMatches;
        int max = 0;
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->second > max) {
                max = it->second;
            }
        }
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->second == max) {
                topMatches.push_back(it->first);
            }
        }
        return topMatches;
    }
}

/**
 * Obtiene los documentos con las mejores coincidencias para un conjunto de palabras dadas.
 * 
 * @param palabras El conjunto de palabras para las cuales se desean obtener las mejores coincidencias.
 * @return Un vector de Documento con los documentos que tienen las mejores coincidencias para las palabras dadas.
 *         Si no se encuentra alguna de las palabras, se retorna un vector vacío.
 */

vector<Documento> TablaHash::getTopMatches(vector<string> palabras) {
    vector<Documento> topMatches;
    vector<Documento> topMatchesAux;
    for (int i = 0; i < palabras.size(); i++) {
        topMatchesAux = getTopMatches(palabras[i]);
        if (topMatchesAux.empty()) {
            return vector<Documento>();
        } else {
            if (topMatches.empty()) {
                topMatches = topMatchesAux;
            } else {
                for (int j = 0; j < topMatches.size(); j++) {
                    bool encontrado = false;
                    for (int k = 0; k < topMatchesAux.size(); k++) {
                        if (topMatches[j].getTitulo() == topMatchesAux[k].getTitulo()) {
                            encontrado = true;
                            break;
                        }
                    }
                    if (!encontrado) {
                        topMatches.erase(topMatches.begin() + j);
                        j--;
                    }
                }
            }
        }
    }
    return topMatches;
}

/**
 * Verifica si la tabla hash está vacía.
 * 
 * @return true si la tabla hash está vacía, false en caso contrario.
 */
bool TablaHash::estaVacia() {
    return tabla.empty();
}

/**
 * Retorna la tabla hash.
 * 
 * @return La tabla hash.
 */

unordered_map<string, vector<pair<Documento, int> > > TablaHash::getTabla() {
    return tabla;
}

/**
 * Retorna la cantidad de veces que aparece una palabra en un libro.
 * 
 * @param palabra La palabra a buscar.
 * @param libro El libro en el cual se busca la palabra.
 * @return La cantidad de veces que aparece la palabra en el libro.
 *         Si no se encuentra la palabra, se retorna 0.
 */
int TablaHash::cantidadDePalabrasEnLibro(string palabra, Documento libro) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se retorna 0
        return 0;
    } else {
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->first.getTitulo() == libro.getTitulo()) {
                return it->second;
            }
        }
        return 0;
    }
}

/**
 * Retorna el libro con más apariciones.
 * 
 * @return El libro con más apariciones.
 */
Documento TablaHash::libroConMasApariciones() {
    int max = 0;
    Documento libroConMasApariciones;
    for (auto it = tabla.begin(); it != tabla.end(); it++) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            if (it2->second > max) {
                max = it2->second;
                libroConMasApariciones = it2->first;
            }
        }
    }
    return libroConMasApariciones;
}

/**
 * Retorna los libros asociados a una palabra.
 * 
 * @param palabra La palabra a buscar.
 * @return Un vector de Documento con los libros asociados a la palabra.
 *         Si no se encuentra la palabra, se retorna un vector vacío.
 */
vector<Documento> TablaHash::getLibrosDePalabra(string palabra) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se retorna un vector vacío
        return vector<Documento>();
    } else {
        vector<Documento> libros;
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            libros.push_back(it->first);
        }
        return libros;
    }
}

/**
 * Verifica si una palabra existe en la tabla hash.
 * 
 * @param palabra La palabra a buscar.
 * @return true si la palabra existe en la tabla hash, false en caso contrario.
 */
bool TablaHash::existePalabra(string palabra) {
    return tabla.find(palabra) != tabla.end();
}