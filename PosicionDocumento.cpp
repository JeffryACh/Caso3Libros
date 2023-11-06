#include "PosicionDocumento.h"

PosicionDocumento::PosicionDocumento(int doc_id) {
    this->doc_id = doc_id;
}

PosicionDocumento::~PosicionDocumento() {}

void PosicionDocumento::agregarPosicion(int posicion) {
    this->posiciones.push_back(posicion);
}

std::vector<int> &PosicionDocumento::getPosiciones() {
    return this->posiciones;
}

int PosicionDocumento::getDocumento() {
    return this->doc_id;
}