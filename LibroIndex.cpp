#include "LibroIndex.h"
#include <filesystem>
#include <algorithm>

/**
 * @brief Constructor de la clase LibrosIndex. Inicializa las estructuras de datos.
 * 
 */
LibrosIndex::LibrosIndex() {
    // Constructor: inicializa las estructuras de datos
}

// Destructor de la clase LibrosIndex que libera la memoria de los libros.
LibrosIndex::~LibrosIndex() {
    // Destructor: libera la memoria de los libros
}

/**
 * Carga los libros desde una carpeta especificada.
 * 
 * @param carpeta La ruta de la carpeta donde se encuentran los archivos de texto de los libros.
 */
void LibrosIndex::cargarLibrosDesdeCarpeta(const std::string& carpeta) {
    for (const auto& entry : std::filesystem::directory_iterator(carpeta)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::ifstream archivo(entry.path());
            if (archivo.is_open()) {
                std::string contenido((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>());
                libros.emplace_back(entry.path().stem().string(), "", contenido);
                archivo.close();
            }
        }
    }
}

/**
 * indexarLibros - Función que indexa los libros en un árbol AVL por título y en una tabla hash por palabras clave.
 * 
 * @return void
 */
void LibrosIndex::indexarLibros() {
    for (const Libro& libro : libros) {
        // Insertar el libro en el árbol AVL por título
        arbolAVL.insertarNodo(libro.titulo, libro);

        // Indexar palabras clave en la tabla hash
        indexarPalabrasClave(libro);
    }
}

/**
 * Busca libros en la tabla hash que contengan las palabras clave de una frase.
 * @param frase La frase a buscar en la tabla hash.
 */
void LibrosIndex::buscarLibrosPorFrase(const std::string& frase) {
    // Tokeniza la frase en palabras
    std::vector<std::string> palabras = tokenizar(frase);

    // Realiza la búsqueda en la tabla hash por palabras clave
    std::vector<Libro> librosRelevantes;

    for (const std::string& palabra : palabras) {
        if (tablaHash.find(palabra) != tablaHash.end()) {
            for (const Libro& libro : tablaHash[palabra]) {
                if (std::find(librosRelevantes.begin(), librosRelevantes.end(), libro) == librosRelevantes.end()) {
                    librosRelevantes.push_back(libro);
                }
            }
        }
    }

    // Imprime los libros relevantes
    std::cout << "Libros relevantes para la frase '" << frase << "':" << std::endl;
    for (const Libro& libro : librosRelevantes) {
        std::cout << "Título: " << libro.titulo << std::endl;
        std::cout << "Autor: " << libro.autor << std::endl;
        std::cout << "Contenido: " << libro.cont << std::endl;
        std::cout << std::endl;
    }
}

/**
 * @brief Tokeniza un texto en palabras individuales y las almacena en un vector.
 * 
 * @param texto El texto a tokenizar.
 * @return std::vector<std::string> El vector de palabras resultante.
 */
std::vector<std::string> LibrosIndex::tokenizar(const std::string& texto) {
    std::vector<std::string> palabras;
    std::string palabra;
    std::istringstream stream(texto);

    while (stream >> palabra) {
        palabras.push_back(palabra);
    }

    return palabras;
}