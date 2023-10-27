#include "LibroIndex.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <dirent.h>

LibrosIndex::LibrosIndex() {
    // Constructor: inicializa las estructuras de datos
}

LibrosIndex::~LibrosIndex() {
    // Destructor: libera la memoria de los libros
}

void LibrosIndex::cargarLibrosDesdeCarpeta(const std::string& carpeta) {
    DIR* directorio;
    struct dirent* archivo;

    directorio = opendir(carpeta.c_str());
    if (directorio) {
        while ((archivo = readdir(directorio)) != nullptr) {
            std::string nombreArchivo = archivo->d_name;
            if (nombreArchivo != "." && nombreArchivo != ".." && nombreArchivo.rfind(".txt") != std::string::npos) {
                std::string rutaCompleta = carpeta + "/" + nombreArchivo;
                std::ifstream archivoStream(rutaCompleta);
                if (archivoStream.is_open()) {
                    std::string contenido((std::istreambuf_iterator<char>(archivoStream)), std::istreambuf_iterator<char>());
                    Libro libroTemporal(nombreArchivo, "", contenido); // Crea un objeto temporal Libro
                    libros.push_back(libroTemporal); // Agrega el objeto temporal a la colección
                    archivoStream.close();
                }
            }
        }
        closedir(directorio);
    }
}

void LibrosIndex::indexarLibros() {
    for (const auto& libro : libros) {
        std::istringstream stream(libro.cont);
        std::string palabra;
        while (stream >> palabra) {
            std::transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);  // Convierte a minúsculas
            indicePorPalabra[palabra].insert(libro.titulo);
        }
    }
}

std::vector<std::string> LibrosIndex::buscarLibrosPorFrase(const std::string& frase) {
    std::vector<std::string> resultados;
    std::istringstream stream(frase);
    std::string palabra;
    while (stream >> palabra) {
        std::transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);  // Convierte a minúsculas
        if (indicePorPalabra.find(palabra) != indicePorPalabra.end()) {
            // Si se encuentra la palabra en el índice, agrega los títulos de los libros relacionados
            for (const std::string& titulo : indicePorPalabra[palabra]) {
                resultados.push_back(titulo);
            }
        }
    }
    return resultados;
}

void LibrosIndex::mostrarRankingPorTitulo() {
    std::unordered_map<std::string, int> rankingTitulos;

    for (const Libro& libro : libros) {
        rankingTitulos[libro.titulo]++;
    }

    std::cout << "Ranking de Títulos:" << std::endl;

    // Itera a través del mapa y muestra el ranking
    for (const auto& pair : rankingTitulos) {
        std::cout << pair.first << ": " << pair.second << " veces" << std::endl;
    }
}