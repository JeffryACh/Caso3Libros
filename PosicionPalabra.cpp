#include "PosicionPalabra.h"

PosicionPalabra::PosicionPalabra(string palabra, Documento &documento) : doc(documento) {
    this->palabra = palabra;
}

PosicionPalabra::~PosicionPalabra() {}

void PosicionPalabra::agregarPosicion(int posicion) {
    this->posiciones.push_back(posicion);
}

vector<int> &PosicionPalabra::getPosiciones() {
    return this->posiciones;
}
Documento & PosicionPalabra::getDocumento() {
    return this->doc;
}

