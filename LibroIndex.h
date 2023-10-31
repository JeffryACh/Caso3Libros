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
    /**
     * @brief Constructor de la clase LibrosIndex.
     * 
     */
    LibrosIndex();

    /**
     * @brief Destructor de la clase LibrosIndex.
     * 
     */
    ~LibrosIndex();

    /**
     * @brief Carga los libros desde una carpeta especificada.
     * 
     * @param carpeta La ruta de la carpeta donde se encuentran los libros.
     */
    void cargarLibrosDesdeCarpeta(const std::string& carpeta);

    /**
     * @brief Indexa los libros cargados previamente.
     * 
     */
    void indexarLibros();

    /**
     * @brief Busca los libros que contienen una frase especificada.
     * 
     * @param frase La frase a buscar en los libros.
     */
    void buscarLibrosPorFrase(const std::string& frase);

private:
    std::vector<Libro> libros; /**< Vector que almacena los libros cargados. */
    AVL_Principal arbolAVL; /**< Árbol AVL que indexa los libros. */
    std::unordered_map<std::string, std::vector<Libro>> tablaHash; /**< Tabla hash que almacena los libros indexados por palabra clave. */

    /**
     * @brief Función auxiliar que tokeniza una cadena en palabras.
     * 
     * @param texto La cadena a tokenizar.
     * @return std::vector<std::string> El vector de palabras resultante.
     */
    std::vector<std::string> tokenizar(const std::string& texto);
};
