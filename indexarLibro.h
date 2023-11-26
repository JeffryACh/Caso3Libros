#ifndef CASO3_INDEXARLIBRO_H
#define CASO3_INDEXARLIBRO_H

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <dirent.h>
#include <set>

#include "PosicionPalabra.h"
#include "TablaHash.h"
#include "Documento.h"
#include "SusAndAdj.h"



#if defined(__CYGWIN__) || defined(__MINGW32__) || defined(WIN32)
static const std::string slash="\\";
#define EN_WINDOWS true
#define LARGO_CAMBIOLINEA 2
#else
static const std::string slash="/";
#define EN_WINDOWS false
#define LARGO_CAMBIOLINEA 1
#endif

#define INDEXAR_AND 0
#define INDEXAR_OR 1

using namespace std;

class indexarLibro{
private:
    // atributos
    TablaHash tabla = TablaHash(); // la key es la palabra, el value es un vector de pares <Libro, int> (libro, cantidad de veces que aparece la palabra en el libro)
    map<int, int> contadorDocumentos; // map que almacena la cantidad de palabras de cada documento
    map<string, vector<PosicionPalabra>> indice; // map que almacena el índice invertido (la key es la palabra, el value es un vector de PosicionPalabra)
    map<int, Documento> mapaDocumentos; // map que almacena los documentos indexados
    vector<Documento> documentos; // vector que almacena los documentos indexados

    // métodos privados
    void procesarRuta(const std::string& ruta); // procesa la ruta de un libro
    void indexarDocumento(Documento &documento); // indexa un documento
    
public:
    indexarLibro(); // constructor
    indexarLibro(std::string); // constructor con parámetros

    // métodos públicos
    void indexar(string ruta); // indexa los libros en la ruta dada
    vector<pair<int, double>> buscar(string consulta); // retorna los documentos que contienen la consulta
    Documento& getDocumento(int id_doc); // retorna el documento con el id dado
    vector<pair<int, int>> obtenerParrafosRelevantes(string consulta, int id_doc); // retorna los párrafos relevantes de un documento
    string textoParrafo(int id_doc, int id_parrafo); // retorna el texto de un párrafo
    int cantidadDocumentos(); // retorna la cantidad de documentos indexados
    vector<int> calcularUnion(vector<int> &v1, vector<int> &v2); // calcula la unión entre dos vectores
    vector<int> calcularInterseccion(vector<int> &v1, vector<int> &v2); // calcula la intersección entre dos vectores
    int contarPalabrasEnDocumento(string palabra, int id_doc); // cuenta la cantidad de veces que aparece una palabra en un documento
    vector<pair<int, double>> buscarConOperador(string consulta, int operador); // retorna los documentos que contienen la consulta
    void imprimirIndice(); // imprime el índice invertido
    void imprimirDocumentos(); // imprime los documentos indexados
    void indexarTablaHash(vector<string>); // indexa los libros en la ruta dada
    TablaHash getTablaHash(); // retorna la tabla hash
    void actualizarTablaHash(vector<string>); // indexa los libros en la ruta dada
};

#endif //CASO3_INDEXARLIBRO_H