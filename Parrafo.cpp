#include "Parrafo.h"

// Inicio y final son las posiciones en el archivo correspondiente del documento
Parrafo::Parrafo(int id, long inicio, long final) {
    this->id = id;
    this->inicio = inicio;
    this->final = final;
}

Parrafo::Parrafo(const Parrafo &otro) {
    this->id = otro.id;
    this->inicio = otro.inicio;
    this->final = otro.final;
}

long Parrafo::getFinal() {
    return this->final;
}

long Parrafo::getInicio() {
    return this->inicio;
}

int Parrafo::getId() {
    return this->id;
}

