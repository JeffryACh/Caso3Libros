#include "TablaHash.h"
#include <iostream>
#include <string>

using namespace std;

void TablaHash::insertar(string palabra, Libro libro) {
    if (tabla.find(palabra) == tabla.end()) {
        tabla[palabra] = make_pair(libro, 1);
    } else {
        tabla[palabra].second++;
    }
}

vector<pair<Libro, int> > TablaHash::buscar(string palabra) {
    if (tabla.find(palabra) == tabla.end()) {
        return vector<pair<Libro, int> >();
    } else {
        return tabla[palabra];
    }
}

void TablaHash::imprimir() {
    for (auto it = tabla.begin(); it != tabla.end(); it++) {
        cout << it->first << ": " << it->second.second << endl;
    }
}

void TablaHash::imprimirLibros() {
    for (auto it = tabla.begin(); it != tabla.end(); it++) {
        cout << it->first << ": " << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << "\t" << it2->first.titulo << endl;
        }
    }
}

Libro TablaHash::buscarLibroConMasApariciones(string palabra) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se retorna un libro vacío
        return Libro("", "", vector<string>());
    } else {
        Libro libro = tabla[palabra][0].first;
        int max = tabla[palabra][0].second;
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->second > max) {
                libro = it->first;
                max = it->second;
            }
        }
        return libro;
    }
}

