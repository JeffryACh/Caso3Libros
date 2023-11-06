#ifndef __INDEXADOR_H__
#define __INDEXADOR_H__
#include <string>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <dirent.h> 
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include "PosicionDocumento.h"
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
    vector<int> buscar(vector<string> consulta);

    /**
     * @brief Función que recibe un string y devuelve un vector de strings con las palabras que contiene el string.
     * 
     * @param consulta String que contiene las palabras a separar.
     * @return vector<string> Vector de strings con las palabras que contiene el string.
     */
    vector<string> separarFrase(string consulta);
    
    /**
     * Obtiene el ranking de los documentos que contienen la consulta dada.
     * @param docs Los ids de los documentos que contienen la consulta.
     * @return Un vector con los ids de los documentos que contienen la consulta.
     */
    vector<string> ranking(vector<int> &docs);
    
    /**
     * Obtiene el contenido del documento con el id dado.
     * @param id_doc El id del documento a obtener.
     * @return El contenido del documento con el id dado.
     */
    std::string getDocumento(int id_doc);
    
    
    /**
     * @brief Función que recibe un vector de enteros y una consulta en forma de string, y devuelve un vector de strings con los libros rankeados según su relevancia con respecto a la consulta.
     * 
     * @param docs Vector de enteros que representa los documentos a rankear.
     * @param consulta String que representa la consulta a utilizar para rankear los documentos.
     * @return vector<string> Vector de strings con los libros rankeados según su relevancia con respecto a la consulta.
     */
    unordered_map<int, std::string> rankeadorDeLibros(vector<int> &docs, vector<string> consulta);

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
