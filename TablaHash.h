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
    TablaHash(); // constructor
    bool estaVacia(); // retorna true si la tabla hash está vacía
    void insertar(string palabra, Documento libro); // inserta una palabra y un libro en la tabla hash
    vector<pair<Documento, int> > buscar(string palabra); // busca una palabra en la tabla hash y devuelve los documentos asociados a esa palabra
    void imprimir(); // imprime los elementos almacenados en la tabla hash
    void imprimirLibros(); // imprime los libros almacenados en la tabla hash
    Documento buscarLibroConMasApariciones(string palabra); // busca el libro con más apariciones de una palabra
    vector<Documento> getTopMatches(string palabra);    // retorna los 10 mejores matches de una palabra
    vector<Documento> getTopMatches(vector<string> palabras); // retorna los 10 mejores matches de un conjunto de palabras
    unordered_map<string, vector<pair<Documento, int> > > getTabla(); // retorna la tabla hash
    int cantidadDePalabrasEnLibro(string palabra, Documento libro); // retorna la cantidad de veces que aparece una palabra en un libro
    Documento libroConMasApariciones(); // retorna el libro con más apariciones
    vector<Documento> getLibrosDePalabra(string palabra); // retorna los libros asociados a una palabra
}; 

#endif // CASO3_EDATOS_TABLAHASH_H