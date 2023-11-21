#include "TablaHash.h"
#include <iostream>
#include <string>

using namespace std;

void TablaHash::insertar(string palabra, Documento libro) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se crea un vector vacío
        vector<pair<Documento, int>> libros;
        libros.push_back(make_pair(libro, 1));
        tabla[palabra] = libros;
    } else {
        bool libroEncontrado = false;
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->first.getTitulo() == libro.getTitulo()) {
                it->second++;
                libroEncontrado = true;
                break;
            }
        }
        if (!libroEncontrado) {
            tabla[palabra].push_back(make_pair(libro, 1));
        }
    }
}

vector<pair<Documento, int> > TablaHash::buscar(string palabra) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se retorna un vector vacío
        return vector<pair<Documento, int>>();
    } else {
        return tabla[palabra];
    }
}

void TablaHash::imprimir() {
    for (auto it = tabla.begin(); it != tabla.end(); it++) {
        cout << it->first << ": " << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << "\t" << it2->first.getTitulo() << " (" << it2->second << ")" << endl;
        }
    }
}

void TablaHash::imprimirLibros() {
    for (auto it = tabla.begin(); it != tabla.end(); it++) {
        cout << it->first << ": " << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << "\t" << it2->first.getTitulo() << endl;
            cout << "\t" << it2->first.getAutor() << endl;

        }
    }
}

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

bool TablaHash::estaVacia() {
    return tabla.empty();
}