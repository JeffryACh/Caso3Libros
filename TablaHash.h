#ifndef CASO3_EDATOS_TABLAHASH_H
#define CASO3_EDATOS_TABLAHASH_H
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <pair>
#include "libro.h"
using namespace std;

class TablaHash {
private:
    unordered_map<string, vector<pair<Libro, int> > > tabla; // la key es la palabra, el value es un vector de pares <Libro, int> (libro, cantidad de veces que aparece la palabra en el libro)

public:
    void insertar(string palabra, Libro libro);
    vector<pair<Libro, int> > buscar(string palabra);
    void imprimir();
    void imprimirLibros();
    Libro buscarLibroConMasApariciones(string palabra);
};

#endif // CASO3_EDATOS_TABLAHASH_H