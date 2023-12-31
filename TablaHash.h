/**
 * @file TablaHash.h
 * 
 * @brief Implementación de la clase TablaHash.
 * 
 * @date 28/11/2023 14:00
 * 
 * @author Jeffry Araya Ch
*/

#ifndef CASO3_EDATOS_TABLAHASH_H
#define CASO3_EDATOS_TABLAHASH_H
#include <string>
#include <queue>
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
    bool existePalabra(string palabra); // retorna true si la palabra existe en la tabla hash
    vector<Documento> getLibrosMacth(vector<string> palabras); // retorna los libros que hacen match con las palabras ingresadas
    int vecesPalabraEnLibro(string palabra, Documento libro); // retorna la cantidad de veces que aparece una palabra en un libro
    vector<Documento> interseccion(vector<Documento> libros1, vector<Documento> libros2); // retorna la intersección de dos vectores de libros
    Documento libroConMasApariciones(string); // retorna el libro con más apariciones de una palabra
    Documento libroConMasApariciones(vector<Documento>, string); // retorna el libro con más apariciones de una palabra
    bool libroExiste(vector<Documento>, Documento); // retorna true si un libro existe en un vector de libros
    Documento segundoLibroConMasApariciones(string, vector<Documento>); // retorna el segundo libro con más apariciones de una palabra
    vector<Documento> quitarLibrosRepetidos(vector<Documento>); // quita los libros repetidos de un vector de libros
    Documento tercerLibroConMasApariciones(string, vector<Documento>); // retorna el tercer libro con más apariciones de una palabra
    Documento segundoLibroConMasApariciones(string); // retorna el segundo libro con más apariciones de una palabra
}; 

#endif // CASO3_EDATOS_TABLAHASH_H