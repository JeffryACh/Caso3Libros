#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <dirent.h>
#include "indexador.h"


PosicionDocumento::PosicionDocumento(int doc_id) {
    this->doc_id = doc_id;
}

PosicionDocumento::~PosicionDocumento() {}

void PosicionDocumento::agregarPosicion(int posicion) {
    this->posiciones.push_back(posicion);
}

vector<int> &PosicionDocumento::getPosiciones() {
    return this->posiciones;
}
int PosicionDocumento::getDocumento() {
    return this->doc_id;
}

IndexadorLibros::IndexadorLibros() {}

IndexadorLibros::~IndexadorLibros() {}

void IndexadorLibros::indexar(std::string ruta) {
    this->procesarRuta(ruta);
    // se itera por el mapa de documentos
    for (auto const& x : this->mapaDocumentos) {
        this->indexarArchivo(x.second, x.first);
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

vector<int> IndexadorLibros::buscar(std::string consulta) {
    std::vector<std::string> palabras;
    std::string palabra;
    std::istringstream iss(consulta);
    while (iss >> palabra) {
        palabras.push_back(palabra);
    }
    std::vector<int> resultado;
    bool inicializado = false;
    // se busca en el indice
    for (auto &palabra : palabras) {
        std::vector<int> docs;
        transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
        if (this->indice.find(palabra) == this->indice.end()) {
            continue;
        }
        for (auto &pos_doc : this->indice[palabra]) {
            docs.push_back(pos_doc.getDocumento());
        }
        sort(docs.begin(), docs.end());
        if (docs.size() > 0) {
            std::cout << "Se encontró la palabra " << palabra << " en " << docs.size() << " documentos." << std::endl;
        }
        if (!inicializado) {
            resultado = docs;
            inicializado = true;
            continue;
        }
        else {
            resultado = this->calcularInterseccion(resultado, docs);
        }
    }
    return resultado;
}

std::string IndexadorLibros::getDocumento(int id_doc) {
    return this->mapaDocumentos[id_doc];
}