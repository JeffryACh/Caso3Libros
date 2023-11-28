/**
 * @file PosicionPalabra.h
 * 
 * @brief Implementación de la clase PosicionPalabra.
 * 
 * @date 28/11/2023 14:00
 * 
 * @author Jeffry Araya Chaves
*/

#ifndef __POSDOCUMENTO_H__
#define __POSDOCUMENTO_H__
#include <vector>
#include <string>
#include "Documento.h"

using namespace std;
/**
 * Clase que representa la posición de una palabra en un documento.
 * Contiene un vector de posiciones y una referencia al documento asociado a la posición de la palabra.
 * La posición de la palabra es el índice de la palabra en el documento.
 * La clase se utiliza para almacenar las posiciones de una palabra en un documento.
 * @see Documento
*/
class PosicionPalabra {
public:
    PosicionPalabra(string palabra, Documento &documento); // constructor

    ~PosicionPalabra(); // destructor

    // metodo publicos
    void agregarPosicion(int posicion); // agrega una posicion a la lista de posiciones de la palabra
    vector<int> &getPosiciones();   // devuelve una referencia al vector de posiciones
    Documento& getDocumento();  // devuelve el documento asociado a la posicion de la palabra
    string getPalabra();    // devuelve la palabra a buscar en el documento
private:
    // atributos privados
    vector<int> posiciones; // las posiciones de la palabra en el documento
    Documento& doc; // el documento asociado a la posicion de la palabra
    string palabra; // la palabra a buscar en el documento
};
#endif //__POSDOCUMENTO_H__