/**
 * @file PosicionDocumento.h
 * 
 * @brief Implementación de la clase PosicionDocumento.
 * 
 * @date 28/11/2023 14:00
 * 
 * @author Jeffry Araya Chaves
*/

#ifndef POSICIONDOCUMENTO_H
#define POSICIONDOCUMENTO_H

#include <vector>

/**
 * Clase que representa la posición de una palabra en un documento dado por su identificador (doc_id).
 */
class PosicionDocumento {
public:
    /**
     * Constructor de la clase PosicionDocumento.
     * @param doc_id Identificador del documento.
     */
    PosicionDocumento(int doc_id);

    /**
     * Destructor de la clase PosicionDocumento.
     */
    ~PosicionDocumento();

    /**
     * Agrega una posición al documento.
     * @param posicion Posición a agregar.
     */
    void agregarPosicion(int posicion);

    /**
     * Obtiene las posiciones del documento.
     * @return Referencia a un vector con las posiciones del documento.
     */
    std::vector<int> &getPosiciones();

    /**
     * Obtiene el identificador del documento.
     * @return Identificador del documento.
     */
    int getDocumento();

    /**
     * Sobrecarga del operador == para comparar dos objetos de tipo PosicionDocumento.
     * @param pd Objeto de tipo PosicionDocumento a comparar.
     * @return true si los objetos son iguales, false en caso contrario.
     */
    bool operator==(const PosicionDocumento &pd) const;

private:
    std::vector<int> posiciones; // Vector con las posiciones del documento.
    int doc_id;                 // Identificador del documento.
};

#endif