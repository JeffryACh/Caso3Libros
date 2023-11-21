#ifndef RANKING_LIBROS_H
#define RANKING_LIBROS_H

#include <string>
#include <unordered_map>
#include "IndexadorLibros.h"
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

private:
    IndexadorLibros& indexador; // Referencia al indexador de libros.

    /**
     * Función para obtener los sustantivos de una frase.
     * @param frase La frase de la cual se obtendrán los sustantivos.
     * @return Un unordered_map con los sustantivos y su frecuencia.
     */
    std::unordered_map<std::string, int> obtenerSustantivos(const std::string& frase);
};

#endif
