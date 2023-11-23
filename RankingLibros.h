#ifndef RANKING_LIBROS_H
#define RANKING_LIBROS_H

#include <string>
#include <unordered_map>
#include "IndexadorLibros.h"
#include "SusAndAdj.cpp"
#include "SusAndAdj.h"

/**
 * Clase que representa un ranking de libros a partir de una frase.
 */
class RankingLibros {
public:
    /**
     * Constructor de la clase RankingLibros.
     * @param indexador Referencia al indexador de libros.
     */
    RankingLibros(IndexadorLibros& indexador);

    /**
     * Función para crear un ranking de los 10 mejores matches a partir de una frase.
     * @param frase La frase a partir de la cual se creará el ranking.
     * @return Un unordered_map con los 10 mejores matches y su frecuencia.
     */
    std::unordered_map<std::string, int> getTopMatches(const std::string& frase);

    /**
     * Función para obtener los sustantivos de una frase.
     * @param frase La frase de la cual se obtendrán los sustantivos.
     * @return Un unordered_map con los sustantivos y su frecuencia.
    */
    std::unordered_map<std::string, int> obtenerSustantivos(const std::string& frase);
    
    /**
     * Función para obtener los adjetivos de una frase.
     * @param frase La frase de la cual se obtendrán los adjetivos.
     * @return Un unordered_map con los adjetivos y su frecuencia.
    */
    std::unordered_map<std::string, int> obtenerAdjetivos(const std::string& frase);

    /**
     * Función para calcular la relevancia de un documento.
     * @param palabra La palabra a buscar en el documento.
     * @param documento El documento en el cual se buscará la palabra.
     * @param frecuencia La frecuencia de la palabra en el documento.
     * @return La relevancia del documento.
     */
    int calcularRelevancia(const std::string& palabra, const std::string& documento, int frecuencia);

private:
    IndexadorLibros& indexador; // Referencia al indexador de libros.
};

#endif
