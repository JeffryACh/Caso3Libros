#include "RankingLibros.h"
#include "TipoDePalabra.cpp"
#include <iostream>
#include <algorithm>
#include <vector>

/**
 * @brief Constructor de la clase RankingLibros.
 * 
 * @param indexador Objeto de la clase IndexadorLibros utilizado para indexar los libros.
 */
RankingLibros::RankingLibros(IndexadorLibros& indexador) : indexador(indexador) {
    // Constructor de la clase RankingLibros.
}

/**
 * @brief Unordered map que almacena pares de cadenas de caracteres y enteros.
 * @param frase La frase a partir de la cual se creará el ranking.
 * @return Un unordered_map con los 10 mejores matches y su frecuencia.
 */
std::unordered_map<std::string, int> RankingLibros::getTopMatches(const std::string& frase) {
    // Obtiene los sustantivos de la frase.
    std::unordered_map<std::string, int> sustantivos = obtenerSustantivos(frase);

    // Mapa para almacenar el ranking.
    std::unordered_map<std::string, int> ranking;

    // Recorre los sustantivos y busca coincidencias en el índice.
    for (const auto& sustantivo : sustantivos) {
        std::string palabra = sustantivo.first;

        // Verifica si la palabra está en el índice.
        if (indexador.contieneTermino(palabra)) {
            // Obtiene los documentos que contienen la palabra.
            std::vector<std::string> documentos = indexador.getDocumentosConTermino(palabra);

            // Calcula la puntuación para cada documento.
            for (const std::string& doc : documentos) {
                // Supongamos que tienes una función para calcular la relevancia.
                int relevancia = calcularRelevancia(palabra, doc, sustantivo.second);

                // Almacena la puntuación en el ranking.
                ranking[doc] += relevancia;
            }
        }
    }

    // Ordena el ranking por relevancia en orden descendente.
    std::vector<std::pair<std::string, int>> rankingOrdenado(ranking.begin(), ranking.end());
    std::sort(rankingOrdenado.begin(), rankingOrdenado.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Crea un mapa con los 10 mejores matches.
    std::unordered_map<std::string, int> topMatches;
    for (size_t i = 0; i < std::min(rankingOrdenado.size(), 10U); ++i) {
        topMatches[rankingOrdenado[i].first] = rankingOrdenado[i].second;
    }

    return topMatches;
}

/**
 * @brief An unordered map that maps strings to integers.
 * @param palabra La palabra a buscar en el índice.
 * @return Un unordered_map con los sustantivos y su frecuencia.
 */
std::unordered_map<std::string, int> RankingLibros::obtenerSustantivos(const std::string& frase) {
    // Mapa para almacenar los sustantivos.
    std::unordered_map<std::string, int> sustantivos;

    for (const auto& palabra : indexador.separarFrase(frase)) {
        // Verifica si la palabra es un sustantivo.
        if (tipoDePalabra2(palabra) == "sustantivo" || tipoDePalabra2(palabra) == "adjetivo") {
            // Almacena el sustantivo en el mapa.
            sustantivos[palabra] += 1;
            std::cout << palabra << std::endl;
            std::cout << sustantivos[palabra] << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        } else{
            continue;
        }
    }

    return sustantivos;
}
