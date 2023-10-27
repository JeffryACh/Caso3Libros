//
// Created by aquir on 27/10/2023.
//

#ifndef CASO3_EDATOS_LIBRO_H
#define CASO3_EDATOS_LIBRO_H
#include <string>
using namespace std;

class Libro {
public:
    string titulo;
    string autor;
    string cont;

    Libro(string& _titulo, const char *_autor, string&_cont);
};


#endif //CASO3_EDATOS_LIBRO_H
