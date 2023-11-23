#ifndef __POSDOCUMENTO_H__
#define __POSDOCUMENTO_H__
#include <vector>
#include <string>
#include "Documento.h"

using namespace std;
// esta clase almacena la posicion de una palabra en un documento
// la posicion se refiere al número de párrafo
// se usa como valor en la clase del indexador
class PosicionPalabra {
public:
    PosicionPalabra(string palabra, Documento &documento); // constructor

    ~PosicionPalabra();
    void agregarPosicion(int posicion); // agrega una posicion a la lista de posiciones de la palabra
    vector<int> &getPosiciones();   // devuelve una referencia al vector de posiciones
    Documento& getDocumento();  // devuelve el documento asociado a la posicion de la palabra
private:
    vector<int> posiciones; // las posiciones de la palabra en el documento
    Documento& doc; // el documento asociado a la posicion de la palabra
    string palabra; // la palabra a buscar en el documento
};
#endif //__POSDOCUMENTO_H__
