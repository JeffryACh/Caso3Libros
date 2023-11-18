//
// Created by aquir on 27/10/2023.
//

#ifndef CASO3_EDATOS_LIBRO_H
#define CASO3_EDATOS_LIBRO_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Libro {
public:
    string titulo;
    string autor;
    vector<string> palabrasClave;

    Libro(string& _titulo, const char *_autor, vector<string>& _palabrasClave) {
        titulo = _titulo;
        autor = _autor;
        palabrasClave = _palabrasClave;
    }
};


#endif //CASO3_EDATOS_LIBRO_H
