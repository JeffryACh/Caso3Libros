#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <dirent.h>
#include <cctype>
#include <algorithm>
#include <set>
#include "IndexadorTFIDF.h"
#include "Documento.h"
#include "Parrafo.h"
#include "PosicionPalabra.h"

#define MAX_RESULTADOS 10
#define MAX_PARRAFOS 3
#define MULTIPLICADOR_AND 2
#define MULTIPLICADOR_FRASE_COMPLETA 5

IndexadorLibros::IndexadorLibros() {}

IndexadorLibros::~IndexadorLibros() {}

void IndexadorLibros::indexar(std::string ruta) {
    this->procesarRuta(ruta);
    // se itera por el mapa de documentos
    for (auto &x : this->mapaDocumentos) {
        this->indexarDocumento(x.second);
    }
}

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

int IndexadorLibros::contarPalabraEnDocumento(std::string palabra, int doc_id) {
    int contador = 0;
    for (auto &pos_doc: indice[palabra]) {
        if (pos_doc.getDocumento().getId() == doc_id) {
            contador += pos_doc.getPosiciones().size();
        }
    }
    return contador;
}

std::string removerCaracteresEspeciales(std::string str) {
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x) {
        return !std::isprint(x);
    }), str.end());
    return str;
}

bool cadenaVacia(std::string str) {
    return str.find_first_not_of(' ') == std::string::npos;
}


void IndexadorLibros::indexarDocumento(Documento &documento) {
    std::cout << "Indexando archivo: " << documento.getRuta() << std::endl;
    std::ifstream file = std::ifstream(documento.getRuta());
    std::string linea;
    int contadorParrafos = 0;
    // para controlar si hay lineas vacias entre parrafos
    int lineasParrafo = 0;
    if (file.is_open()) {
        long ult_pos = file.tellg();
        while (getline(file, linea)) {
            // verificar si la linea es vacia o contiene solo espacios
            if (cadenaVacia(linea)) {
                if (lineasParrafo > 0) {
                    long pos = file.tellg();
                    pos = pos - linea.length() - 3; // se le resta 3 por los dos caracteres de fin de linea
                    // se almacena el numero de parrafo, junto con las posiciones fisicas de inicio y final del mismo
                    // dentro del archivo
                    documento.agregarParrafo(contadorParrafos, ult_pos, pos);
                    // se actualiza la ultima posicion para el siguiente parrafo
                    ult_pos = file.tellg();
                    contadorParrafos++;
                    lineasParrafo = 0;
                }
                continue;
            }
            // revisar si la linea es el titulo
            if (linea.find("Title:") != std::string::npos) {
                // se remueve el titulo del documento
                linea = linea.substr(linea.find("Title:") + 6);
                documento.setTitulo(linea);
                continue;
            }
            else if (linea.find("Author:") != std::string::npos) {
                // se remueve el autor del documento
                linea = linea.substr(linea.find("Author:") + 7);
                documento.setAutor(linea);
                continue;
            }

            lineasParrafo++;
            // dividir la linea en palabras
            std::vector<string> palabras = dividir(linea, " ,.;\":()[]{}-_!¡¿?'*+&%$#@/");
            for (auto &palabra: palabras) {
                // std::cout << palabra << std::endl;
                // se agrega la palabra al indice
                palabra = removerCaracteresEspeciales(palabra);
                if (cadenaVacia(palabra))
                    continue;
                transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
                if (this->indice.find(palabra) == this->indice.end()) {
                    // si no existe la palabra en el indice, se crea
                    this->indice[palabra] = std::vector<PosicionPalabra>();
                    this->indice[palabra].push_back(PosicionPalabra(palabra, documento));
                    this->indice[palabra].back().agregarPosicion(contadorParrafos);
                    continue;
                }
                // se agrega la posicion de la palabra en el documento (nivel parrafo)
                // pero primero hay que buscar si ya existe el documento
                // en el vector de documentos, y si así es, se agrega la contadorParrafos
                bool existe = false;
                for (auto &pos_doc: this->indice[palabra]) {
                    if (pos_doc.getDocumento().getId() == documento.getId()) {
                        pos_doc.agregarPosicion(contadorParrafos);
                        existe = true;
                        break;
                    }
                }
                if (!existe) {
                    this->indice[palabra].push_back(PosicionPalabra(palabra, documento));
                    this->indice[palabra].back().agregarPosicion(contadorParrafos);
                }
                // incrementa el contador de palabras del documento
                this->contadorDocumentos[documento.getId()]++;
            }
        }
        file.close();
    } else {
        std::cerr << "Error abriendo archivo " << documento.getRuta() << std::endl;
    }
}

// procesa una ruta a un directorio, buscando todos los archivos, y los guarda en un mapa que asocia
// el titulo completo del archivo a un identificador (entero)
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
        this->mapaDocumentos[id_doc] = Documento(id_doc, ruta + slash + str_entrada);
        this->contadorDocumentos[id_doc] = 0;
        std::cout << "Agregando archivo " << str_entrada << " para indexar." << std::endl;
        id_doc++;
    }

    closedir(dp);
}

vector<int> ordenarVector(vector<int> &v) {
    vector<int> ordenado = v;
    sort(ordenado.begin(), ordenado.end());
    return ordenado;
}

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

vector<int> IndexadorLibros::calcularUnion(vector<int> &v1, vector<int> &v2) {
    v1.insert(v1.end(), v2.begin(), v2.end());
    std::sort(v1.begin(), v1.end());
    auto last = std::unique(v1.begin(), v1.end());
    v1.erase(last, v1.end());
    return v1;
}

/**
 * @brief Busca una frase en el indice, calculando además el ranking de los documentos
 * usando el algoritmo de TF-IDF (Term Frequency - Inverse Document Frequency)
 * Revisar el siguiente enlace: https://en.wikipedia.org/wiki/Tf%E2%80%93idf para referencia
 * Uno de los aspectos mas importantes es que usando TF-IDF, no es necesario filtrar palabras
 * "relevantes", pues la formula asignará pesos muy bajos a las palabras que aparezcan muy frecuentemente
 * en todos los documentos, y también asignará pesos relativamente más altos a palabras menos frecuentes
 * o "raras"
 * @param consulta La frase a consultar
 * @param operador El operador a usar. Si se usa el operador AND, se retornan los documentos
 * que contengan todas las palabras de la consulta. Si se usa el operador OR, se retornan los
 * documentos que contengan al menos una de las palabras de la consulta.
 * En todos los casos se calcula el ranking mencionado
 * @return Un vector de pares (id_documento, ranking) ordenados por ranking descendente
 */
vector<pair<int, double>> IndexadorLibros::buscarConOperador(std::string consulta, int operador) {
    std::istringstream iss(consulta);
    std::vector<pair<int, double>> resultado;
    std::vector<int> docs_resultado;
    bool inicializado = false;
    // se busca en el indice
    std::vector<std::string> palabras = dividir(consulta, " ,.;\":()[]{}-_!¡¿?'*+&%$#@/");
    for (auto &palabra : palabras) {
        std::vector<int> docs;
        // se pasa la palabra a minusculas
        transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
        // no se encuentra la palabra en el indice, se continua con la siguiente
        if (this->indice.find(palabra) == this->indice.end()) {
            continue;
        }
        // se obtienen los documentos en los que aparece la palabra
        for (auto &pos_doc : this->indice[palabra]) {
            docs.push_back(pos_doc.getDocumento().getId());
        }
        // se ordenan los documentos en orden ascendente
        sort(docs.begin(), docs.end());
        if (!inicializado) {
            docs_resultado = docs;
            inicializado = true;
            continue;
        }
        else {
            // se opera con los documentos encontrados y con los anteriormente encontrados
            // si el operador es AND se calcula la interseccion, y si es OR se calcula la union
            if (operador == INDEXADOR_AND) {
                docs_resultado = this->calcularInterseccion(docs_resultado, docs);
            } else if (operador == INDEXADOR_OR) {
                docs_resultado = this->calcularUnion(docs_resultado, docs);
            }

            sort(docs_resultado.begin(), docs_resultado.end());
        }
    }
    int i = 0;
    // calcular el tf-idf de cada documento
    for (auto &doc_id : docs_resultado) {
        double tf_idf = 0;
        for (auto &palabra : palabras) {
            // se pasa la palabra a minusculas
            transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
            // se busca la palabra en el indice
            if (this->indice.find(palabra) == this->indice.end()) {
                continue;
            }
            // se calculan todos los valores para tf/idf
            double tf_num = contarPalabraEnDocumento(palabra, doc_id);
            double tf_denom = this->contadorDocumentos[doc_id];
            double tf = tf_num / tf_denom;
            double  idf_num = this->mapaDocumentos.size();
            double idf_denom = this->indice[palabra].size();
            double idf = log10(idf_num / (idf_denom + 1)) + 1;
            // se suman los scores para cada palabra
            tf_idf += (tf * idf);
        }
        resultado.push_back(std::make_pair(doc_id, tf_idf));
        if (++i > MAX_RESULTADOS) {
            // solo se retornan los primeros MAX_RESULTADOS resultados
            break;
        }
    }
    // se ordenan los resultados en orden descendente de score
    sort(resultado.begin(), resultado.end(), [](const std::pair<int, float> &a, const std::pair<int, float> &b) {
        return a.second > b.second;
    });
    return resultado;
}
/**
 * Metodo principal de búsqueda. Realiza los siguientes pasos:
 * 1. Realiza una busqueda para obtener los documentos donde aparezcan TODAS las palabras de la consulta
 * 2. Realiza una busqueda para obtener los documentos donde aparezca CUALQUIER palabra de la consulta
 * 3. Aumenta el peso de los documentos encontrados en el paso 1
 * 4. Obtiene los párrafos relevantes de los documentos encontrados en el paso 1 (AND)
 * 5. Determina si algun parrafo de cada documento contiene TODAS las palabras de la consulta, y si es así, aumenta el peso del documento
 * 6. Une todos los resultados (AND y OR) en un solo vector
 * 7. Ordena los resultados por score descendente
 * 8. Retorna los primeros MAX_RESULTADOS resultados
 *
 * @param consulta
 * @return
 */
vector<pair<int, double>> IndexadorLibros::buscar(std::string consulta) {
    vector<pair<int, double>> resultado_and =  this->buscarConOperador(consulta, INDEXADOR_AND);
    vector<pair<int, double>> resultado_or =  this->buscarConOperador(consulta, INDEXADOR_OR);
    std::vector<std::string> palabras = dividir(consulta, " ,.;\":()[]{}-_!¡¿?'*+&%$#@/");
    // se procesan los resultados del operador AND
    for (auto &par : resultado_and) {
        // se le aumenta el peso a los resultados del operador AND
        par.second *= MULTIPLICADOR_AND;
        // luego se obtienen los párrafos
        vector<pair<int, int>> parrafos = this->obtenerParrafosRelevantes(consulta, par.first);
        // se determina si hay algun elemento en el vector de parrafos cuyo segundo elemento sea igual
        // a la cantidad de palabras
        for (auto &parrafo : parrafos) {
            if (parrafo.second == palabras.size()) {
                // si se encuentra, se le aumenta el peso al resultado
                par.second *= MULTIPLICADOR_FRASE_COMPLETA;
                break;
            }
        }
    }
    // se unen los dos resultados (and y or en un solo vector)
    resultado_and.insert(resultado_and.end(), resultado_or.begin(), resultado_or.end());
    // si hay pares con el mismo primer elemento (id_doc) se suman los scores y se elimina uno de los dos
    for (auto it = resultado_and.begin(); it != resultado_and.end(); ++it) {
        for (auto it2 = it + 1; it2 != resultado_and.end(); ++it2) {
            if (it->first == it2->first) {
                it->second += it2->second;
                it2 = resultado_and.erase(it2);
                --it2;
            }
        }
    }
    // se ordenan los resultados en orden descendente de score
    sort(resultado_and.begin(), resultado_and.end(), [](const std::pair<int, float> &a, const std::pair<int, float> &b) {
        return a.second > b.second;
    });
    // se conservan los diez primeros resultados
    if (resultado_and.size() > MAX_RESULTADOS) {
        resultado_and.resize(MAX_RESULTADOS);
    }
    return resultado_and;
}

/**
 * Obtienen el documento con el id indicado
 * @param id_doc
 * @return Un objeto documento con el id indicado
 */
Documento& IndexadorLibros::getDocumento(int id_doc) {
    return this->mapaDocumentos[id_doc];
}

/**
 * @brief Obtiene los parrafos relevantes de un documento para una consulta. El algoritmo ordena según la cantidad
 * de las palabras de la consulta que aparezcan en un mismo párrafo.
 * De momento, no considera si las palabras aparecen en el mismo orden o la distancia entre las mismas
 * @param consulta La consulta del usuario
 * @param id_doc El documento del cual se obtendrán los párrafos relevantes
 * @return Un vector con una tupla que contiene hasta 3 identificadores de parrafo junto con la cantidad de palabras que
 * se encontraron en el mismo
 */
vector<pair<int, int>> IndexadorLibros::obtenerParrafosRelevantes(std::string consulta, int id_doc) {
    // mapa que se usará para colectar cada párrafo y las palabras de la consulta que ocurren en el mismo
    // luego usando este colector se realiza el ordenamiento según cuántas palabras de la consulta
    // ocurren en cada párrafo
    std::map<int, set<string>> colector;
    // se separa la consulta en palabras
    std::vector<std::string> palabras = dividir(consulta, " ,.;\":()[]{}-_!¡¿?'*+&%$#@/");
    vector<int> posiciones;
    vector<pair<int, int>> resultado;
    // se busca en el indice
    for (auto &palabra : palabras) {
        // se pasa la palabra a minusculas
        transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
        // no se encuentra la palabra en el indice, se continua con la siguiente
        if (this->indice.find(palabra) == this->indice.end()) {
            continue;
        }
        // se obtienen los documentos en los que aparece la palabra
        for (auto &pos_doc: this->indice[palabra]) {
            // se buscan las ocurrencias de la palabra en el documento
            if (pos_doc.getDocumento().getId() == id_doc) {
                posiciones = pos_doc.getPosiciones();
                for (auto &pos: posiciones) {
                    colector[pos].insert(palabra);
                }
            }
        }
    }
    // se ordenan los documentos en el colector en orden descendente según el tamano del set
    std::vector<std::pair<int, set<string>>> colector_vec(colector.begin(), colector.end());
    sort(colector_vec.begin(), colector_vec.end(), [](const std::pair<int, set<string>> &a, const std::pair<int, set<string>> &b) {
        return a.second.size() > b.second.size();
    });
    // se carga el vector de pares que sera el resultado
    for (int i = 0; i < colector_vec.size() && i < MAX_PARRAFOS; i++) {
        resultado.push_back(std::make_pair(colector_vec[i].first, colector_vec[i].second.size()));
    }
    return resultado;
}

/**
 * Lee el texto de un parrafo de un documento, dado su identificador. Se utilizan las posiciones
 * guardadas en el indice para leer el texto del parrafo (inicio y final)
 * @param id_doc El identificador del documento
 * @param id_parrafo El identificador del parrafo
 * @return El texto del parrafo
 */
std::string IndexadorLibros::textoParrafo(int id_doc, int id_parrafo) {
    string ruta = this->mapaDocumentos[id_doc].getRuta();
    std::ifstream archivo(ruta);
    // now, read the chunk of the file between start and end of the paragraph
    Parrafo parrafo = this->mapaDocumentos[id_doc].getParrafo(id_parrafo);
    archivo.seekg(parrafo.getInicio());
    std::string texto;
    texto.resize(parrafo.getFinal() - parrafo.getInicio());
    archivo.read(&texto[0], parrafo.getFinal() - parrafo.getInicio());
    archivo.close();
    return texto;
}

int IndexadorLibros::cantidadDocumentos() {
    return this->mapaDocumentos.size();
}