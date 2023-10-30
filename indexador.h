#ifndef __INDEXADOR_H__
#define __INDEXADOR_H__
#include <string>
#include <map>
#include <vector>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
static const std::string slash="\\";
#else
static const std::string slash="/";
#endif


using namespace std;
// esta clase almacena la posicion de una palabra en un documento
// se usa como valor en la clase del indexador
class PosicionDocumento {
    public:
        PosicionDocumento(int doc_id);
        ~PosicionDocumento();
        void agregarPosicion(int posicion);
        vector<int> &getPosiciones();
        int getDocumento();
        bool operator == (const PosicionDocumento& pd) const {
            return this->doc_id == pd.doc_id;
        }
    private:
        vector<int> posiciones;
        int doc_id;
};

class IndexadorLibros {
    public:
        IndexadorLibros();
        ~IndexadorLibros();
        void indexar(std::string ruta);
        vector<int> buscar(std::string consulta);
    private:
        void procesarRuta(const std::string& ruta);
        void indexarArchivo(const std::string& archivo, int id_doc);
        vector<int> calcularInterseccion(vector<int> &v1, vector<int> &v2);
        std::map<std::string, std::vector<PosicionDocumento>> indice;
        std::map<std::string, int> mapaDocumentos;
};
#endif
