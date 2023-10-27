#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <filesystem> // Incluye la cabecera de filesystem

#include "arbolAVL.h"
#include "libro.h"
using namespace std;
class LibrosIndex {
public:
    LibrosIndex();
    ~LibrosIndex();

    void cargarLibrosDesdeCarpeta(const std::string& carpeta);
    void indexarLibros();
    void mostrar();
    // Búsqueda de libros por frase
    std::vector<std::string> buscarLibrosPorFrase(const std::string& frase);

    // Mostrar ranking de autores
    void mostrarRankingPorTitulo();

private:
    std::vector<Libro> libros;
    AVL_Principal arbolAVL;
    std::unordered_map<std::string, std::set<std::string>> indicePorPalabra;

    void mostrar() const;
};