#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "arbolAVL.h"
#include "Libro.h"

class LibrosIndex {
public:
    LibrosIndex();
    ~LibrosIndex();

    void cargarLibrosDesdeCarpeta(const std::string& carpeta);
    void indexarLibros();
    void buscarLibrosPorFrase(const std::string& frase);

private:
    std::vector<Libro> libros;
    AVL_Principal arbolAVL;
    std::unordered_map<std::string, std::vector<Libro>> tablaHash;

    // Función auxiliar para tokenizar una cadena en palabras
    std::vector<std::string> tokenizar(const std::string& texto);
};
