#ifndef __INDEXADOR_H__
#define __INDEXADOR_H__
#include <string>
#include <map>
#include <vector>

#include "PosicionPalabra.h"
#include "Documento.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
static const std::string slash="\\";
#else
static const std::string slash="/";
#endif

#define INDEXADOR_AND 0
#define INDEXADOR_OR 1


using namespace std;

class IndexadorLibros {
    public:
        IndexadorLibros();
        ~IndexadorLibros();
        void indexar(std::string ruta);
        vector<pair<int, float>> buscar(std::string consulta, int operador = INDEXADOR_OR);
        std::string getDocumento(int id_doc);
    private:
        void procesarRuta(const std::string& ruta);
        void indexarDocumento(Documento &documento);
        vector<int> calcularInterseccion(vector<int> &v1, vector<int> &v2);
        vector<int> calcularUnion(vector<int> &v1, vector<int> &v2);
        int contarPalabraEnDocumento(std::string palabra, int id_doc);
        std::map<std::string, std::vector<PosicionPalabra>> indice;
        std::map<int, Documento> mapaDocumentos;
        std::map<int, int> contadorDocumentos;
};
#endif
