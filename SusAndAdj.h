#ifndef CASO3LIBROS_SUSANDADJ_H
#define CASO3LIBROS_SUSANDADJ_H

#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <fstream> // Add this line to import the fstream library
#include <algorithm>

using namespace std;

class SusAndAdj {
    private:
        vector<string> sustantivos;
        vector<string> adjetivos;
    public:
        SusAndAdj();
        void cargarNSustantivos(int n);
        void cargarNAdjetivos(int n);
        bool esSustantivo(string palabra);
        bool esAdjetivo(string palabra);
        string setearPalabra(string palabra); // quita las comillas de los palabras y demas caracteres especiales
};

#endif //CASO3LIBROS_SUSANDADJ_H