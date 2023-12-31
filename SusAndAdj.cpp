/**
 * @file SusAndAdj.cpp
 * 
 * @brief Implementación de las funciones de SusAndAdj.h.
 * 
 * @date 28/11/2023 14:00
 * 
 * @author Jeffry Araya Chaves
*/

#include "SusAndAdj.h"

/**
 * @brief Función que elimina los caracteres '"', '[' y ']' de una cadena de texto.
 * 
 * @param palabra La cadena de texto a modificar.
 * @return La cadena de texto modificada.
 */
string setearPalabra(string palabra) {
    //cout << palabra << endl;
    palabra.erase(std::remove_if(palabra.begin(), palabra.end(), [](char c) { return c == '\"' || c == '[' || c == ']'; }), palabra.end());
    //cout << palabra << endl;
    return palabra;
}

/**
 * @brief Verifica si una palabra es un sustantivo.
 * 
 * @param palabra La palabra a verificar.
 * @return true si la palabra es un sustantivo, false en caso contrario.
 */
bool esSustantivo(string palabra) {
    ifstream inputFile("Palabras/sus.txt"); // Open the input file stream
    if (inputFile.is_open()) {
        string sustantivo;
        while (getline(inputFile, sustantivo)) {
            transform(sustantivo.begin(), sustantivo.end(), sustantivo.begin(), ::tolower);
            transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
            if (palabra == setearPalabra(sustantivo)) {
                inputFile.close(); // Close the file
                return true;
            }
        }
        inputFile.close(); // Close the file
    }
    return false;
}

/**
 * Verifica si una palabra es un adjetivo.
 * @param palabra La palabra a verificar.
 * @return true si la palabra es un adjetivo, false en caso contrario.
 */
bool esAdjetivo(string palabra) {
    ifstream inputFile("Palabras/adj.txt"); // Open the input file stream
    if (inputFile.is_open()) {
        string adjetivo;
        while (getline(inputFile, adjetivo)) {
            transform(adjetivo.begin(), adjetivo.end(), adjetivo.begin(), ::tolower);
            transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
            if (palabra == setearPalabra(adjetivo)) {
                inputFile.close(); // Close the file
                return true;
            }
        }
        inputFile.close(); // Close the file
    }
    return false;
}

/**
 * @brief elimina las palabras repetidas de un archivo.
 * 
 * @param ruta La ruta del archivo.
*/
void eliminarPalabrasRepetidas(string ruta) {
    ifstream file(ruta);
    unordered_set<string> palabras;
    string palabra;

    while (file >> palabra) {
        palabras.insert(palabra);
    }

    file.close();

    ofstream file2(ruta);
    for (auto& palabra : palabras) {
        if (!esPalabraRepetida(palabra, ruta)) {
            file2 << palabra << endl;
        }
    }

    file2.close();
}

bool esPalabraRepetida(string palabra, string ruta) {
    ifstream file(ruta);
    string palabraActual;

    while (file >> palabraActual) {
        if (palabraActual == palabra) {
            cout << palabraActual << endl;
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}