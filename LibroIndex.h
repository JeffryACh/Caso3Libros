#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

#include "arbolAVL.h"
#include "libro.h"

class LibrosIndex {
public:
    LibrosIndex();
    ~LibrosIndex();

    void cargarLibrosDesdeCarpeta(const std::string& carpeta);
    void indexarLibros();
    std::vector<std::string> buscarLibrosPorFrase(const std::string& frase);
    void mostrarRankingPorTitulo();

private:
    std::vector<Libro> libros;
    AVL_Principal arbolAVL;
    std::unordered_map<std::string, std::set<std::string>> indicePorPalabra;

    void indexarPalabrasClave(const Libro& libro);
    std::vector<std::string> dividirFraseEnPalabras(const std::string& frase);
};
