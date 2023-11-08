#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <dirent.h>
#include <cctype>
#include <algorithm>
#include "IndexadorTFIDF.h"
#include "Documento.h"
#include "Parrafo.h"
#include "PosicionPalabra.h"

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


void IndexadorLibros::indexarDocumento(Documento &documento) {
    std::cout << "Indexando archivo: " << documento.getRuta() << std::endl;
    std::ifstream file = std::ifstream(documento.getRuta());
    std::string linea;
    int contadorParrafos = 0, ult_pos = 0;
    if (file.is_open()) {
        while (getline(file, linea)) {
            // verificar si la linea es vacia o contiene solo espacios
            if (linea.find_first_not_of(' ') == std::string::npos) {
                contadorParrafos++;
                continue;
            }
            // dividir la linea en palabras
            std::vector<string> palabras = dividir(linea, " ,.;\":()[]{}-_!¡¿?'*+&%$#@/");
            for (auto &palabra: palabras) {
                // std::cout << palabra << std::endl;
                // se agrega la palabra al indice
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
// el nombre completo del archivo a un identificador (entero)
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
 * @param consulta La frase a consultar
 * @param operador El operador a usar. Si se usa el operador AND, se retornan los documentos
 * que contengan todas las palabras de la consulta. Si se usa el operador OR, se retornan los
 * documentos que contengan al menos una de las palabras de la consulta.
 * En todos los casos se calcula el ranking mencionado
 * @return Un vector de pares (id_documento, ranking) ordenados por ranking descendente
 */
vector<pair<int, float>> IndexadorLibros::buscar(std::string consulta, int operador) {
    std::vector<std::string> palabras;
    std::string palabra;
    std::istringstream iss(consulta);
    // se separan las palabras de la consulta
    while (iss >> palabra) {
        palabras.push_back(palabra);
    }
    std::vector<pair<int, float>> resultado;
    std::vector<int> docs_resultado;
    bool inicializado = false;
    // se busca en el indice
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
            else {
                std::cerr << "Operador no válido." << std::endl;
                return {};
            }
            sort(docs_resultado.begin(), docs_resultado.end());
        }
    }
    // calcular el tf-idf de cada documento
    for (auto &doc_id : docs_resultado) {
        float tf_idf = 0;
        for (auto &palabra : palabras) {
            // se pasa la palabra a minusculas
            transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
            // se busca la palabra en el indice
            if (this->indice.find(palabra) == this->indice.end()) {
                continue;
            }
            // se calculan todos los valores para tf/idf
            float tf_num = contarPalabraEnDocumento(palabra, doc_id);
            float tf_denom = this->contadorDocumentos[doc_id];
            float tf = tf_num / tf_denom;
            float idf_num = this->mapaDocumentos.size();
            float idf_denom = this->indice[palabra].size();
            float idf = log10(idf_num / idf_denom);
            // se suman los scores para cada palabra
            tf_idf += (tf * idf);
        }
        resultado.push_back(std::make_pair(doc_id, tf_idf));
    }
    // se ordenan los resultados en orden descendente de score
    sort(resultado.begin(), resultado.end(), [](const std::pair<int, float> &a, const std::pair<int, float> &b) {
        return a.second > b.second;
    });
    return resultado;
}

std::string IndexadorLibros::getDocumento(int id_doc) {
    return this->mapaDocumentos[id_doc].getRuta();
}