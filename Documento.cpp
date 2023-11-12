#include "Documento.h"
#include <string>

Documento::Documento(const Documento& otro) {
    this->id = otro.id;
    this->ruta = otro.ruta;
    this->titulo = otro.titulo;
    this->autor = otro.autor;
    this->parrafos = otro.parrafos;
}

Documento::Documento(int id, std::string ruta) {
    this->id = id;
    this->ruta = ruta;
    this->parrafos = std::map<int, Parrafo>();
}

int Documento::getId() {
    return this->id;
}

const std::string Documento::getRuta() {
    return this->ruta;
}

const std::string Documento::getTitulo() {
    return this->titulo;
}

const std::string Documento::getAutor() {
    return this->autor;
}

void Documento::setTitulo(std::string titulo) {
    this->titulo = titulo;
}

void Documento::setAutor(std::string autor) {
    this->autor = autor;
}

Documento::Documento() = default;

void Documento::agregarParrafo(int id, long inicio, long final) {
    this->parrafos[id] = Parrafo(id, inicio, final);
}

Parrafo& Documento::getParrafo(int id) {
    return this->parrafos[id];
}
