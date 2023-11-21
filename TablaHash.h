#ifndef CASO3_EDATOS_TABLAHASH_H
#define CASO3_EDATOS_TABLAHASH_H
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include "Documento.h"
using namespace std;

class TablaHash {
private:
    unordered_map<string, vector<pair<Documento, int> > > tabla; 
// la key es la palabra, el value es un vector de pares <Libro, int> (libro, cantidad de veces que aparece la palabra en el libro)

public:
    TablaHash();
    bool estaVacia();
    void insertar(string palabra, Documento libro);
    vector<pair<Documento, int> > buscar(string palabra);
    void imprimir();
    void imprimirLibros();
    Documento buscarLibroConMasApariciones(string palabra);
    vector<Documento> getTopMatches(string palabra);
};

#endif // CASO3_EDATOS_TABLAHASH_H