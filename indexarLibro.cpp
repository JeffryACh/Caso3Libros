#include "indexarLibro.h" // incluye el archivo indexarLibro.h

using namespace std; // para no tener que escribir std::vector, std::string, etc.

indexarLibro::indexarLibro() {
} // constructor

/**
 * @brief Indexa un libro a partir de una ruta especificada.
 * 
 * @param ruta La ruta del libro a indexar.
 */
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

/**
 * @brief Vector de cadenas de texto.
 * 
 * Un std::vector<std::string> es una estructura de datos que almacena una secuencia de cadenas de texto.
 * Permite agregar, eliminar y acceder a las cadenas de texto de manera eficiente.
 * @param s La cadena de texto a dividir.
 * @param delimitadores Los delimitadores que se utilizarán para dividir la cadena de texto.
 * @return Un vector de cadenas de texto.
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
 * Cuenta el número de veces que una palabra aparece en un documento específico.
 * 
 * @param palabra La palabra a contar.
 * @param doc_id El ID del documento en el que se busca la palabra.
 * @return El número de veces que la palabra aparece en el documento.
 */
int IndexadorLibros::contarPalabraEnDocumento(std::string palabra, int doc_id) {
    int contador = 0;
    for (auto &pos_doc: indice[palabra]) {
        if (pos_doc.getDocumento().getId() == doc_id) {
            contador += pos_doc.getPosiciones().size();
        }
    }
    return contador;
}

/**
 * @brief Remueve los caracteres especiales de una cadena de texto.
 * 
 * @param str La cadena de texto de la cual se removerán los caracteres especiales.
 * @return La cadena de texto sin caracteres especiales.
 */
std::string removerCaracteresEspeciales(std::string str) {
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x) {
        return !std::isprint(x);
    }), str.end());
    return str;
}

/**
 * @brief Remueve los caracteres especiales de una cadena de texto.
 * 
 * @param str La cadena de texto de la cual se removerán los caracteres especiales.
 * @return La cadena de texto sin caracteres especiales.
 */
std::string removerCaracteresEspeciales(std::string str) {
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x) {
        return !std::isprint(x);
    }), str.end());
    return str;
}

/**
 * Verifica si una cadena está vacía.
 * 
 * @param str La cadena a verificar.
 * @return true si la cadena está vacía, false de lo contrario.
 */
bool cadenaVacia(std::string str) {
    return str.find_first_not_of(' ') == std::string::npos;
}

/**
 * @brief Función que remueve el último carácter de una cadena de texto.
 * 
 * @param str Cadena de texto de la cual se desea remover el último carácter.
 * @return std::string Cadena de texto resultante después de remover el último carácter.
 */
std::string removerUltimoCaracter(std::string str) {
    return str.substr(0, str.size() - 1);
}

/**
 * Procesa una ruta de directorio, indexando los documentos encontrados en ella.
 * 
 * @param ruta La ruta del directorio a procesar.
 */
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

/**
 * @brief Indexa un documento, extrayendo información relevante como título, autor y palabras clave.
 * 
 * @param documento El documento a indexar.
 */
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

/**
 * Busca en el índice del libro las palabras clave proporcionadas y devuelve los resultados con sus puntajes.
 * 
 * @param consulta La consulta de búsqueda que contiene las palabras clave.
 * @return Un vector de pares que contiene los resultados de la búsqueda, donde el primer elemento del par es el número de documento y el segundo elemento es el puntaje.
 */
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

/**
 * Calcula la intersección entre dos vectores.
 * 
 * @param v1 El primer vector.
 * @param v2 El segundo vector.
 * @return Un vector que contiene los elementos comunes entre v1 y v2.
 */
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

/**
 * Calcula la unión de dos vectores ordenados.
 * 
 * @param v1 El primer vector ordenado.
 * @param v2 El segundo vector ordenado.
 * @return Un vector que contiene la unión de los elementos de v1 y v2, en orden ascendente.
 */
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

/**
 * @brief Obtiene el documento con el ID especificado.
 * 
 * @param id_doc El ID del documento a obtener.
 * @return Una referencia al documento con el ID especificado.
 */
Documento& indexarLibro::getDocumento(int id_doc) {
    return documentos[id_doc];
}

/**
 * Obtiene los párrafos relevantes de un documento dado una consulta y un ID de documento.
 * 
 * @param consulta La consulta de búsqueda.
 * @param id_doc El ID del documento.
 * @return Un vector de pares de enteros que representan las posiciones y los párrafos relevantes encontrados.
 */
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

/**
 * @brief Obtiene el texto de un párrafo específico de un documento.
 * 
 * @param id_doc El ID del documento.
 * @param id_parrafo El ID del párrafo.
 * @return El texto del párrafo especificado.
 */
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