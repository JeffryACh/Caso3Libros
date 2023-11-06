#include "PosicionDocumento.h"

/**
 * @brief Constructor de la clase PosicionDocumento
 * 
 * @param doc_id Identificador del documento
 */
PosicionDocumento::PosicionDocumento(int doc_id) {
    this->doc_id = doc_id;
}

PosicionDocumento::~PosicionDocumento() {}

/**
 * @brief Agrega una posición al vector de posiciones de un documento.
 * 
 * @param posicion La posición a agregar.
 */
void PosicionDocumento::agregarPosicion(int posicion) {
    this->posiciones.push_back(posicion);
}

/**
 * @brief Devuelve una referencia a un vector de enteros que representa las posiciones de un documento.
 * 
 * @return std::vector<int>& 
 */
std::vector<int> &PosicionDocumento::getPosiciones() {
    return this->posiciones;
}

/**
 * @brief Obtiene el identificador del documento.
 * 
 * @return int El identificador del documento.
 */
int PosicionDocumento::getDocumento() {
    return this->doc_id;
}

/**
 * @brief Sobrecarga del operador == para comparar dos PosicionDocumento.
 * 
 * @param pd PosicionDocumento a comparar.
 * @return true si los doc_id de ambos objetos son iguales, false en caso contrario.
 */
bool PosicionDocumento::operator==(const PosicionDocumento &pd) const {
    return this->doc_id == pd.doc_id;
}