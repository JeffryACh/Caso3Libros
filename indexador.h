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
/**
 * Clase que representa la posición de un documento en el índice invertido.
 */
class PosicionDocumento {
public:
    /**
     * Constructor de la clase PosicionDocumento.
     * @param doc_id Identificador del documento.
     */
    PosicionDocumento(int doc_id);

    /**
     * Destructor de la clase PosicionDocumento.
     */
    ~PosicionDocumento();

    /**
     * Agrega una posición al documento.
     * @param posicion Posición a agregar.
     */
    void agregarPosicion(int posicion);

    /**
     * Obtiene las posiciones del documento.
     * @return Referencia a un vector con las posiciones del documento.
     */
    vector<int> &getPosiciones();

    /**
     * Obtiene el identificador del documento.
     * @return Identificador del documento.
     */
    int getDocumento();

    /**
     * Sobrecarga del operador == para comparar dos objetos de tipo PosicionDocumento.
     * @param pd Objeto de tipo PosicionDocumento a comparar.
     * @return true si los objetos son iguales, false en caso contrario.
     */
    bool operator == (const PosicionDocumento& pd) const {
        return this->doc_id == pd.doc_id;
    }

private:
    vector<int> posiciones; // Vector con las posiciones del documento.
    int doc_id; // Identificador del documento.
};

/**
 * Clase que se encarga de indexar y buscar libros en una ruta dada.
 */
class IndexadorLibros {
public:
    /**
     * Constructor de la clase IndexadorLibros.
     */
    IndexadorLibros();
    
    /**
     * Destructor de la clase IndexadorLibros.
     */
    ~IndexadorLibros();
    
    /**
     * Indexa los libros en la ruta dada.
     * @param ruta La ruta donde se encuentran los libros a indexar.
     */
    void indexar(std::string ruta);
    
    /**
     * Busca los libros que contienen la consulta dada.
     * @param consulta La consulta a buscar en los libros.
     * @return Un vector con los ids de los documentos que contienen la consulta.
     */
    vector<int> buscar(std::string consulta);
    
    /**
     * Obtiene el contenido del documento con el id dado.
     * @param id_doc El id del documento a obtener.
     * @return El contenido del documento con el id dado.
     */
    std::string getDocumento(int id_doc);
    
private:
    /**
     * Procesa la ruta dada para obtener los archivos a indexar.
     * @param ruta La ruta a procesar.
     */
    void procesarRuta(const std::string& ruta);
    
    /**
     * Indexa el archivo dado con el id de documento dado.
     * @param archivo El archivo a indexar.
     * @param id_doc El id del documento a indexar.
     */
    void indexarArchivo(const std::string& archivo, int id_doc);
    
    /**
     * Calcula la intersección entre dos vectores de enteros.
     * @param v1 El primer vector.
     * @param v2 El segundo vector.
     * @return Un vector con los elementos que se encuentran en ambos vectores.
     */
    vector<int> calcularInterseccion(vector<int> &v1, vector<int> &v2);
    
    std::map<std::string, std::vector<PosicionDocumento>> indice; /**< Mapa que almacena el índice de los términos en los documentos. */
    std::map<int, std::string> mapaDocumentos; /**< Mapa que almacena los documentos indexados. */
};
#endif
