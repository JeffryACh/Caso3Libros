#include "Documento.h"
#include <string>

Documento::Documento(const Documento& otro) {
    this->id = otro.id;
    this->ruta = otro.ruta;
    this->nombre = otro.nombre;
    this->autor = otro.autor;
}

Documento::Documento(int id, std::string ruta) {
    this->id = id;
    this->ruta = ruta;
}

int Documento::getId() {
    return this->id;
}

const std::string Documento::getRuta() {
    return this->ruta;
}

const std::string Documento::getNombre() {
    return this->nombre;
}

const std::string Documento::getAutor() {
    return this->autor;
}

void Documento::setNombre(std::string nombre) {
    this->nombre = nombre;
}

void Documento::setAutor(std::string autor) {
    this->autor = autor;
}

Documento::Documento() = default;


