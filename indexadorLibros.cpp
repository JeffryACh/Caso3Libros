#include "indexadorLibros.h"

IndexadorLibros::IndexadorLibros() {} // constructor

IndexadorLibros::~IndexadorLibros() {} // destructor

/**
 * @brief Indexa los documentos en la ruta especificada.
 * 
 * @param ruta La ruta donde se encuentran los documentos a indexar.
 */
void IndexadorLibros::indexar(std::string ruta) {
    this->procesarRuta(ruta);
    // se itera por el mapa de documentos
    for (auto const& x : this->mapaDocumentos) {
        this->indexarArchivo(x.second, x.first);
    }
}

/**
 * @brief Vector de cadenas de caracteres.
 * @param s La cadena de caracteres a dividir.
 * @param delimitadores Los delimitadores para dividir la cadena.
 * @return Un vector con las cadenas de caracteres divididas.
 */
std::vector<std::string> dividir(std::string s, std::string delimitadores) {
    std::vector<std::string> tokens;
    std::string token;
    size_t pos = 0;
    while ((pos = s.find_first_of(delimitadores)) != std::string::npos) {
        token = s.substr(0, pos);
        if (!token.empty())
            tokens.push_back(token);
        s.erase(0, pos + 1);
    }
    tokens.push_back(s);
    return tokens;
}


/**
 * @brief Indexa un archivo de texto y lo agrega al índice de palabras del objeto IndexadorLibros.
 * 
 * @param archivo Ruta del archivo a indexar.
 * @param id_doc Identificador del documento.
 */
void IndexadorLibros::indexarArchivo(const std::string &archivo, int id_doc) {
    std::cout << "Indexando archivo: " << archivo << std::endl;
    std::ifstream file = std::ifstream(archivo);
    std::string linea;
    int posicion = 0;
    if (file.is_open()) {
        while (getline(file, linea)) {
            // dividir la linea en palabras
            std::vector<string> palabras = dividir(linea, " ,.;\":()[]{}-_!¡¿?'*+&%$#@/");
            for (auto &palabra: palabras) {
                // std::cout << palabra << std::endl;
                // se agrega la palabra al indice
                transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
                if (this->indice.find(palabra) == this->indice.end()) {
                    // si no existe la palabra en el indice, se crea
                    this->indice[palabra] = std::vector<PosicionDocumento>();
                    this->indice[palabra].push_back(PosicionDocumento(id_doc));
                    this->indice[palabra].back().agregarPosicion(posicion);
                    continue;
                }
                // se agrega la posicion de la palabra en el documento
                // pero primero hay que buscar si ya existe el documento
                // en el vector de documentos, y si así es, se agrega la posicion
                bool existe = false;
                for (auto &pos_doc: this->indice[palabra]) {
                    if (pos_doc.getDocumento() == id_doc) {
                        pos_doc.agregarPosicion(posicion);
                        existe = true;
                        break;
                    }
                }
                if (!existe) {
                    this->indice[palabra].push_back(PosicionDocumento(id_doc));
                    this->indice[palabra].back().agregarPosicion(posicion);
                }
                posicion++;
            }
        }
        file.close();
    } else {
        std::cerr << "Error abriendo archivo " << archivo << std::endl;
    }
}

// procesa una ruta a un directorio, buscando todos los archivos, y los guarda en un mapa que asocia
// el nombre completo del archivo a un identificador (entero)
/**
 * @brief Procesa una ruta de directorio y agrega los archivos encontrados al mapa de documentos.
 * 
 * @param ruta La ruta del directorio a procesar.
 */
void IndexadorLibros::procesarRuta(const std::string& ruta) {
    DIR *dp;
    struct dirent *entrada;

    dp = opendir(ruta.c_str());
    if (dp == NULL) {
        std::cerr << "Error abriendo directorio " << ruta << std::endl;
        return;
    }
    std::cout << "Procesando directorio " << ruta << " ..." << std::endl;

    int id_doc = 0;
    while((entrada = readdir(dp))) {
        std::string str_entrada = std::string(entrada->d_name);
        if (str_entrada == "." || str_entrada == "..") {
            continue;
        }
        this->mapaDocumentos[id_doc] = ruta + slash + str_entrada;
        std::cout << "Agregando archivo " << str_entrada << " para indexar." << std::endl;
        id_doc++;
    }

    closedir(dp);
}

/**
 * @brief Ordena un vector de enteros de forma ascendente.
 * 
 * @param v Vector de enteros a ordenar.
 * @return Vector ordenado de forma ascendente.
 */
vector<int> ordenarVector(vector<int> &v) {
    vector<int> ordenado = v;
    sort(ordenado.begin(), ordenado.end());
    return ordenado;
}

/**
 * Calcula la intersección entre dos vectores de enteros.
 * @param v1 Vector de enteros.
 * @param v2 Vector de enteros.
 * @return Vector de enteros con la intersección entre v1 y v2.
 */
vector<int> IndexadorLibros::calcularInterseccion(vector<int> &v1, vector<int> &v2) {
    vector<int> interseccion;
    int i = 0;
    int j = 0;
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] == v2[j]) {
            interseccion.push_back(v1[i]);
            i++;
            j++;
        } else if (v1[i] < v2[j]) {
            i++;
        } else {
            j++;
        }
    }
    return interseccion;
}

/**
 * @brief Separa una frase en palabras individuales y las almacena en un vector.
 * 
 * @param frase La frase a separar.
 * @return std::vector<string> El vector que contiene las palabras individuales.
 */
vector<string> IndexadorLibros::separarFrase(std::string frase) {
    std::vector<string> tokens;
    std::string token;
    size_t pos = 0;
    while ((pos = frase.find_first_of(" ")) != std::string::npos) {
        token = frase.substr(0, pos);
        if (!token.empty())
            tokens.push_back(token);
        frase.erase(0, pos + 1);
    }
    tokens.push_back(frase);
    return tokens;
}

/**
 * @brief Busca una consulta en el índice de libros y devuelve los documentos donde se encontró la palabra.
 * 
 * @param consulta La palabra a buscar en el índice.
 * @return std::vector<int> Un vector con los documentos donde se encontró la palabra consultada.
 */
vector<int> IndexadorLibros::buscar(vector<string> consultas) {
    std::vector<int> resultado;
    for (auto &consulta: consultas) {
        transform(consulta.begin(), consulta.end(), consulta.begin(), ::tolower);
        if (this->indice.find(consulta) == this->indice.end()) {
            std::cerr << "No se encontró la palabra " << consulta << std::endl;
            continue;
        }
        std::cout << "Se encontró la palabra " << consulta << std::endl;
        std::vector<PosicionDocumento> posiciones = this->indice[consulta];
        for (auto &posicion: posiciones) {
            resultado.push_back(posicion.getDocumento());
        }
    }
    return resultado;
}

/**
 * @brief Retorna un vector de strings con los nombres de los documentos en el orden especificado por el vector de enteros docs.
 * 
 * @param docs Vector de enteros que especifica el orden en que se deben retornar los nombres de los documentos.
 * @return vector<string> Vector de strings con los nombres de los documentos en el orden especificado por el vector de enteros docs.
 */
vector<string> IndexadorLibros::ranking(vector<int> &docs) {
    vector<string> ranking;
    // se calcula el ranking
    for (auto &doc_id : docs) {
        if (this->mapaDocumentos.find(doc_id) == this->mapaDocumentos.end()) {
            std::cerr << "No se encontró el documento con id " << doc_id << std::endl;
            continue;
        } else {
            std::cout << "Se encontró el documento con id " << doc_id << std::endl;
        }
        ranking.push_back(std::to_string(doc_id));
    }
    return ranking;
}

/**
 * @brief Devuelve el documento correspondiente al id dado.
 * 
 * @param id_doc El id del documento a buscar.
 * @return std::string El documento correspondiente al id dado.
 */
std::string IndexadorLibros::getDocumento(int id_doc) {
    return this->mapaDocumentos[id_doc];
}

/**
 * @brief Función que calcula el ranking de los libros que contienen una palabra específica en su título.
 * 
 * @param docs Vector de enteros que contiene los ids de los documentos que contienen la palabra buscada.
 * @param consulta Palabra que se desea buscar en los títulos de los libros.
 * @return Vector de strings que contiene los títulos de los libros ordenados por ranking.
 */
unordered_map<int, std::string> IndexadorLibros::rankeadorDeLibros(vector<int> &docs, vector<string> consulta) {
    std::unordered_map<int, std::string> ranking;

    int i = 0;
    for (auto &doc_id : docs) {
        if (this->mapaDocumentos.find(doc_id) == this->mapaDocumentos.end()) {
            std::cerr << "No se encontró el documento con id " << doc_id << std::endl;
            continue;
        } else if (this->mapaDocumentos.find(doc_id) != this->mapaDocumentos.end() && this->mapaDocumentos[doc_id] == "Libros/." + consulta[i]) {
            std::cout << "Se encontró el documento con id " << doc_id << std::endl;
        }
        ranking[doc_id] = this->mapaDocumentos[doc_id];
        std::cout << "Se encontró el documento con id " << doc_id << std::endl;
        std::cout << "El libro se llama: " << this->mapaDocumentos[doc_id] << std::endl;
        i++;
    }

    return ranking;
}
