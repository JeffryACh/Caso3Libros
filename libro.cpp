//
// Created by aquir on 27/10/2023.
//

#include "libro.h"
Libro::Libro(std::string &_titulo, std::string &_autor, std::vector<std::string> &_palabrasClave) {
    titulo = _titulo;
    autor = _autor;
    palabrasClave = _palabrasClave;
}