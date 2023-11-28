/**
 * @file Parrafo.cpp
 * 
 * @brief Implementación de la clase Parrafo.
 * 
 * @date 28/11/2023 14:00
 * 
 * @author Jeffry Araya Chaves
*/

#include "Parrafo.h"

/**
 * @brief Constructor de la clase Parrafo.
 * 
 * @param id El identificador del párrafo.
 * @param inicio La posición de inicio del párrafo en el texto.
 * @param final La posición de fin del párrafo en el texto.
 */
Parrafo::Parrafo(int id, long inicio, long final) {
    this->id = id;
    this->inicio = inicio;
    this->final = final;
}

/**
 * @brief Constructor de copia de la clase Parrafo.
 * 
 * Este constructor crea una nueva instancia de Parrafo a partir de otra instancia existente.
 * Copia los valores de identificación, inicio y final del otro Parrafo.
 * 
 * @param otro Referencia constante al Parrafo que se desea copiar.
 */
Parrafo::Parrafo(const Parrafo &otro) {
    this->id = otro.id;
    this->inicio = otro.inicio;
    this->final = otro.final;
}

/**
 * Obtiene el valor final del párrafo.
 *
 * @return El valor final del párrafo.
 */
long Parrafo::getFinal() {
    return this->final;
}

/**
 * Obtiene el valor de inicio del párrafo.
 * 
 * @return El valor de inicio del párrafo.
 */
long Parrafo::getInicio() {
    return this->inicio;
}

/**
 * Obtiene el identificador del párrafo.
 *
 * @return El identificador del párrafo.
 */
int Parrafo::getId() {
    return this->id;
}

