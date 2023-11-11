#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include "LibroIndex.h"
#include "TipoDePalabra.cpp"
#include "RankingLibros.h"
#include "IndexadorLibros.h"

/**
 * @brief Clase que representa una palabra con su tipo.
 * 
 */
class Word {
public:
    std::string text; /**< Texto de la palabra */
    std::string type; /**< Tipo de la palabra */

    /**
     * @brief Constructor de la clase Word.
     * 
     * @param t Texto de la palabra.
     * @param ty Tipo de la palabra.
     */
    Word(const std::string &t, const std::string &ty) : text(t), type(ty) {}
};

// Función para procesar una frase y retornar sustantivos y adjetivos.
/**
 * @brief Procesa una frase para identificar sustantivos y adjetivos únicos y repetidos.
 * 
 * @param frase La frase a procesar.
 * @return Un vector de palabras únicas con su tipo (sustantivo o adjetivo).
 */
std::vector<Word> procesarFrase(const std::string &frase) {
    std::vector<Word> palabrasUnicas;
    std::unordered_map<std::string, std::string> wordTypes;
    std::unordered_set<std::string> palabrasRepetidas;

    std::string palabra;
    std::istringstream ss(frase);

    while (ss >> palabra) {
        // Convierte la palabra a minúsculas para evitar distinciones entre mayúsculas y minúsculas.
        std::transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);

        // Simula la identificación de sustantivos y adjetivos.
        std::string tipo = "desconocido";
        if (palabra == "gato" || palabra == "valla") {
            tipo = "sustantivo";
        } else if (palabra == "feliz" || palabra == "alta" || palabra == "rápido" || palabra == "diminuto") {
            tipo = "adjetivo";
        }

        // Verifica si la palabra es única y no repetida.
        if (tipo != "desconocido" && palabrasRepetidas.find(palabra) == palabrasRepetidas.end()) {
            palabrasRepetidas.insert(palabra);
            palabrasUnicas.emplace_back(palabra, tipo);
        }
        else if (tipo != "desconocido") {
            wordTypes[palabra] = tipo;
        }
    }

    // Agrega sustantivos y algunos adjetivos que se repiten.
    for (const Word& word : palabrasUnicas) {
        if (word.type == "sustantivo" || word.type == "adjetivo") {
            palabrasUnicas.push_back(word);
        }
    }

    return palabrasUnicas;
}

int main() {
    std::string frase;

    std::cout << "Ingresa una frase: ";
    std::getline(std::cin, frase);

    std::vector<Word> palabrasUnicas = procesarFrase(frase);

    std::cout << "Sustantivos y Adjetivos en la frase:" << std::endl;
    for (const Word &palabra : palabrasUnicas) {
        std::cout << palabra.text << " - " << palabra.type << std::endl;
    }

    return 0;
}
