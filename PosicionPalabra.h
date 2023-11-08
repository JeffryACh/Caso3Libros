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
    PosicionPalabra(string palabra, Documento &documento);

    ~PosicionPalabra();
    void agregarPosicion(int posicion);
    vector<int> &getPosiciones();
    Documento& getDocumento();
private:
    vector<int> posiciones;
    Documento& doc;
    string palabra;
};
#endif //__POSDOCUMENTO_H__
