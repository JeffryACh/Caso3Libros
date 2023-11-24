#ifndef CASO3_INDEXARLIBRO_H
#define CASO3_INDEXARLIBRO_H

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <dirent.h>

#include "PosicionPalabra.h"
#include "TablaHash.h"
#include "Documento.h"



#if defined(__CYGWIN__) || defined(__MINGW32__) || defined(WIN32)
static const std::string slash="\\";
#define EN_WINDOWS true
#define LARGO_CAMBIOLINEA 2
#else
static const std::string slash="/";
#define EN_WINDOWS false
#define LARGO_CAMBIOLINEA 1
#endif

#define INDEXADOR_AND 0
#define INDEXADOR_OR 1

using namespace std;

class indexarLibro{
private:
    TablaHash tabla; // la key es la palabra, el value es un vector de pares <Libro, int> (libro, cantidad de veces que aparece la palabra en el libro)
    map<int, Documento> documentos; // map que almacena los documentos indexados
    map<int, int> contadorDocumentos; // map que almacena la cantidad de palabras de cada documento
    map<string, vector<PosicionPalabra>> indice; // map que almacena el índice invertido
    void procesarRuta(const std::string& ruta); // procesa la ruta de un libro
    void indexarDocumento(Documento &documento); // indexa un documento
    vector<int> calcularInterseccion(vector<int> &v1, vector<int> &v2); // calcula la intersección entre dos vectores
    
public:
    indexarLibro();

    void indexar(string ruta); // indexa los libros en la ruta dada
    vector<pair<int, double>> buscar(string consulta); // retorna los documentos que contienen la consulta
    Documento& getDocumento(int id_doc); // retorna el documento con el id dado
    vector<pair<int, int>> obtenerParrafosRelevantes(string consulta, int id_doc); // retorna los párrafos relevantes de un documento
    string textoParrafo(int id_doc, int id_parrafo); // retorna el texto de un párrafo
    int cantidadDocumentos(); // retorna la cantidad de documentos indexados


};

#endif //CASO3_INDEXARLIBRO_H