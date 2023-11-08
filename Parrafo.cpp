#include "Parrafo.h"

// Inicio y final son las posiciones en el archivo correspondiente del documento
Parrafo::Parrafo(int id, int inicio, int final) {
    this->id = id;
    this->inicio = inicio;
    this->final = final;
}

Parrafo::Parrafo(const Parrafo &otro) {
    this->id = otro.id;
    this->inicio = otro.inicio;
    this->final = otro.final;
}

int Parrafo::getFinal() {
    return this->final;
}

int Parrafo::getInicio() {
    return this->inicio;
}

int Parrafo::getId() {
    return this->id;
}

