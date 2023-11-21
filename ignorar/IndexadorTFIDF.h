#ifndef __INDEXADOR_H__
#define __INDEXADOR_H__
#include <string>
#include <map>
#include <vector>

#include "PosicionPalabra.h"
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

class IndexadorLibros {
public:
    IndexadorLibros();
    ~IndexadorLibros();
    void indexar(std::string ruta);
    vector<pair<int, double>> buscar(std::string consulta);
    Documento& getDocumento(int id_doc);
    vector<pair<int, int>> obtenerParrafosRelevantes(std::string consulta, int id_doc);
    std::string textoParrafo(int id_doc, int id_parrafo);
    int cantidadDocumentos();
private:
    void procesarRuta(const std::string& ruta);
    void indexarDocumento(Documento &documento);
    vector<int> calcularInterseccion(vector<int> &v1, vector<int> &v2);
    vector<int> calcularUnion(vector<int> &v1, vector<int> &v2);
    vector<pair<int, double>> buscarConOperador(std::string consulta, int operador);
    int contarPalabraEnDocumento(std::string palabra, int id_doc);
    std::map<std::string, std::vector<PosicionPalabra>> indice;
    std::map<int, Documento> mapaDocumentos;
    std::map<int, int> contadorDocumentos;
};
#endif
