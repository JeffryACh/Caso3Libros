#include "indexarLibro.h"

using namespace std;

indexarLibro::indexarLibro() {
}

void indexarLibro::indexar(string ruta) {
    procesarRuta(ruta);

    // se calcula el tf-idf(palabra, documento) para cada palabra y cada documento
    for (auto &palabra: this->indice) {
        for (auto &pos_doc: palabra.second) {
            double tf = (double)pos_doc.getPosiciones().size() / (double)this->contadorDocumentos[pos_doc.getDocumento().getId()];
            double idf = log10((double)this->contadorDocumentos.size() / (double)palabra.second.size());
            pos_doc.setTfIdf(tf * idf);
        }
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

std::string removerCaracteresEspeciales(std::string str) {
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x) {
        return !std::isprint(x);
    }), str.end());
    return str;
}

bool cadenaVacia(std::string str) {
    return str.find_first_not_of(' ') == std::string::npos;
}

std::string removerUltimoCaracter(std::string str) {
    return str.substr(0, str.size() - 1);
}

void indexarLibro::procesarRuta(const string& ruta) {
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
        std::string ruta_completa = ruta + slash + str_entrada;
        Documento documento(ruta_completa, id_doc);
        indexarDocumento(documento);
        mapaDocumentos[id_doc] = documento;
        id_doc++;
    }
    closedir(dp);
}

void indexarLibro::indexarDocumento(Documento &documento) {
    std::cout << "Indexando archivo: " << documento.getRuta() << std::endl;
    std::ifstream file = std::ifstream(documento.getRuta());
    std::string linea;
    int contadorParrafos = 0;
    // para controlar si hay lineas vacias entre parrafos
    int lineasParrafo = 0;
    if (file.is_open()) {
        long ult_pos = file.tellg();
        while (getline(file, linea)) {
            if (EN_WINDOWS) {
                // en el caso de Windows, se remueve el caracter \r del final
                linea = removerUltimoCaracter(linea);
            }
            // verificar si la linea es vacia o contiene solo espacios
            if (cadenaVacia(linea)) {
                if (lineasParrafo > 0) {
                    long pos = file.tellg();
                    pos = pos - linea.length() - 2 * (LARGO_CAMBIOLINEA) - 1; // se le restan dos cambios de linea por los dos caracteres de fin de linea
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

vector<pair<int, double>> indexarLibro::buscar(string consulta) {
    vector<pair<int, double>> resultado;
    vector<string> palabras;
    string palabra;
    int pos = 0;
    while (obtenerPalabra(consulta, palabra, pos)) {
        transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
        palabras.push_back(palabra);
    }

    int tipo = INDEXADOR_AND;
    if (palabras.size() > 0 && palabras[palabras.size() - 1] == "or") {
        tipo = INDEXADOR_OR;
        palabras.pop_back();
    }

    if (palabras.size() > 0) {
        vector<int> docs = tabla[palabras[0]][0];
        for (int i = 1; i < palabras.size(); i++) {
            if (tipo == INDEXADOR_AND) {
                docs = calcularInterseccion(docs, tabla[palabras[i]][0]);
            } else {
                docs = calcularUnion(docs, tabla[palabras[i]][0]);
            }
        }

        for (int i = 0; i < docs.size(); i++) {
            double puntaje = 0;
            for (int j = 0; j < palabras.size(); j++) {
                puntaje += tabla[palabras[j]][1][i];
            }
            resultado.push_back(make_pair(docs[i], puntaje));
        }
    }

    return resultado;
}

vector<int> indexarLibro::calcularInterseccion(vector<int> &v1, vector<int> &v2) {
    vector<int> resultado;
    int i = 0, j = 0;
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] == v2[j]) {
            resultado.push_back(v1[i]);
            i++;
            j++;
        } else if (v1[i] < v2[j]) {
            i++;
        } else {
            j++;
        }
    }
    return resultado;
}

vector<int> indexarLibro::calcularUnion(vector<int> &v1, vector<int> &v2) {
    vector<int> resultado;
    int i = 0, j = 0;
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] == v2[j]) {
            resultado.push_back(v1[i]);
            i++;
            j++;
        } else if (v1[i] < v2[j]) {
            resultado.push_back(v1[i]);
            i++;
        } else {
            resultado.push_back(v2[j]);
            j++;
        }
    }
    while (i < v1.size()) {
        resultado.push_back(v1[i]);
        i++;
    }
    while (j < v2.size()) {
        resultado.push_back(v2[j]);
        j++;
    }
    return resultado;
}

Documento& indexarLibro::getDocumento(int id_doc) {
    return documentos[id_doc];
}

vector<pair<int, int>> indexarLibro::obtenerParrafosRelevantes(string consulta, int id_doc) {
    vector<pair<int, int>> resultado;
    vector<string> palabras;
    string palabra;
    int pos = 0;
    while (obtenerPalabra(consulta, palabra, pos)) {
        transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
        palabras.push_back(palabra);
    }

    int tipo = INDEXADOR_AND;
    if (palabras.size() > 0 && palabras[palabras.size() - 1] == "or") {
        tipo = INDEXADOR_OR;
        palabras.pop_back();
    }

    if (palabras.size() > 0) {
        vector<int> docs = tabla[palabras[0]][0];
        for (int i = 1; i < palabras.size(); i++) {
            if (tipo == INDEXADOR_AND) {
                docs = calcularInterseccion(docs, tabla[palabras[i]][0]);
            } else {
                docs = calcularUnion(docs, tabla[palabras[i]][0]);
            }
        }

        for (int i = 0; i < docs.size(); i++) {
            if (docs[i] == id_doc) {
                for (int j = 0; j < palabras.size(); j++) {
                    for (auto &pos_doc: indice[palabras[j]]) {
                        if (pos_doc.getDocumento().getId() == id_doc) {
                            for (auto &pos: pos_doc.getPosiciones()) {
                                resultado.push_back(make_pair(pos, pos_doc.getDocumento().getParrafos()[pos]));
                            }
                        }
                    }
                }
                break;
            }
        }
    }

    return resultado;
}

string indexarLibro::textoParrafo(int id_doc, int id_parrafo) {
    string resultado;
    Documento doc = documentos[id_doc];
    ifstream file = ifstream(doc.getRuta());
    if (file.is_open()) {
        file.seekg(doc.getParrafos()[id_parrafo].first);
        char c;
        while (file.tellg() < doc.getParrafos()[id_parrafo].second) {
            file.get(c);
            resultado += c;
        }
        file.close();
    }
    return resultado;
}

int indexarLibro::cantidadDocumentos() {
    return documentos.size();
}