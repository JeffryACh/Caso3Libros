#include "LibroIndex.h"

LibrosIndex::LibrosIndex() {
    // Constructor
}

LibrosIndex::~LibrosIndex() {
    // Destructor
}

void LibrosIndex::cargarLibrosDesdeCarpeta(const std::string& carpeta) {
    // Implementa la lógica para cargar libros desde una carpeta
    // Supongamos que llena el vector de libros
}

void LibrosIndex::indexarLibros() {
    for (const Libro& libro : libros) {
        // Insertar el libro en el árbol AVL por título
        arbolAVL.insertarPorTitulo(libro);

        // Indexar palabras clave en la tabla hash
        indexarPalabrasClave(libro);
    }
}

std::vector<std::string> LibrosIndex::buscarLibrosPorFrase(const std::string& frase) {
    std::vector<std::string> resultados;
    std::vector<std::string> palabrasClave = dividirFraseEnPalabras(frase);

    for (const std::string& palabra : palabrasClave) {
        // Buscar la palabra clave en la tabla hash
        if (indicePorPalabra.find(palabra) != indicePorPalabra.end()) {
            for (const std::string& libroId : indicePorPalabra[palabra]) {
                resultados.push_back(libroId);
            }
        }
    }

    return resultados;
}

void LibrosIndex::mostrarRankingPorTitulo() {
    arbolAVL.inOrdenTitulo();
}

void LibrosIndex::indexarPalabrasClave(const Libro& libro) {
    // Implementa la lógica para extraer y indexar palabras clave del libro
    // Agrega los identificadores de libro al conjunto correspondiente en la tabla hash
}

std::vector<std::string> LibrosIndex::dividirFraseEnPalabras(const std::string& frase) {
    std::vector<std::string> palabras;
    // Implementa la lógica para dividir la frase en palabras clave
    return palabras;
}
