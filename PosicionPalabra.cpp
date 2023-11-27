#include "PosicionPalabra.h"

/**
 * @brief Constructor de la clase PosicionPalabra.
 * 
 * Este constructor crea una instancia de la clase PosicionPalabra con la palabra y el documento asociado.
 * 
 * @param palabra La palabra a buscar en el documento.
 * @param documento El documento en el que se buscará la palabra.
 */
PosicionPalabra::PosicionPalabra(string palabra, Documento &documento) : doc(documento) {
    this->palabra = palabra;
}

PosicionPalabra::~PosicionPalabra() {} // destructor

/**
 * Agrega una posición a la lista de posiciones de la palabra.
 * @param posicion La posición a agregar.
 */
void PosicionPalabra::agregarPosicion(int posicion) {
    this->posiciones.push_back(posicion);
}

/**
 * @brief Returns a reference to the vector of positions where the word occurs.
 * 
 * @return A reference to the vector of positions.
 */
vector<int> &PosicionPalabra::getPosiciones() {
    return this->posiciones;
}

/**
 * @brief Obtiene el documento asociado a la posición de la palabra.
 * 
 * @return Una referencia al objeto Documento asociado.
 */
Documento & PosicionPalabra::getDocumento() {
    return this->doc;
}

/**
 * @brief Obtiene la palabra a buscar en el documento.
 * 
 * @return La palabra a buscar en el documento.
 */
string PosicionPalabra::getPalabra() {
    return this->palabra;
}