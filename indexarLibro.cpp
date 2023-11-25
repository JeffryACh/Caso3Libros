#include "indexarLibro.h" // incluye el archivo indexarLibro.h
#include <sstream> // incluye el archivo sstream

using namespace std; // para no tener que escribir std::vector, std::string, etc.

#define MAX_RESULTADOS 10
#define MAX_PARRAFOS 3
#define MULTIPLICADOR_AND 2
#define MULTIPLICADOR_FRASE_COMPLETA 5

indexarLibro::indexarLibro() {
} // constructor

indexarLibro::indexarLibro(string ruta) {
    indexar(ruta);
} // constructor con parámetros

/**
 * @brief Indexa un libro a partir de una ruta especificada.
 * 
 * @param ruta La ruta del libro a indexar.
 */
void indexarLibro::indexar(string ruta) {
    this->procesarRuta(ruta);
    // se itera por el mapa de documentos
    for (auto &x : this->mapaDocumentos) {
        this->indexarDocumento(x.second);
    }
}

/**
 * @brief Indexa asia la tabla hash
 * @param vector de palabras para añadir a la tablahash
*/
void indexarLibro::indexarTablaHash(vector<string> palabras) {
    cout << "Indexando..." << endl;
    for (auto &palabra : palabras) {
        for (auto &pos_doc : this->indice[palabra]) {
            tabla.insertar(palabra, pos_doc.getDocumento());
        }
    }
}
/**
 * @brief imprime el indice invertido
 * 
*/
void indexarLibro::imprimirIndice() {
    for (auto &x : this->indice) {
        std::cout << x.first << std::endl;
        for (auto &y : x.second) {
            cout << "\t" << y.getDocumento().getTitulo() << endl;
            cout << "\t" << y.getDocumento().getAutor() << endl;
            std::cout << "\t" << y.getDocumento().getId() << std::endl;
            for (auto &z : y.getPosiciones()) {
                std::cout << "\t\t" << z << std::endl;
            }
        }
    }
}

/**
 * @brief imprime los documentos indexados
 * 
*/
void indexarLibro::imprimirDocumentos() {
    for (auto &x : this->mapaDocumentos) {
        std::cout << x.first << std::endl;
        std::cout << "\t" << x.second.getTitulo() << std::endl;
        std::cout << "\t" << x.second.getAutor() << std::endl;
        std::cout << "\t" << x.second.getRuta() << std::endl;
        for (auto &y : x.second.getParrafos()) {
            std::cout << "\t\t" << y.first << std::endl;
            std::cout << "\t\t" << y.second.getInicio() << std::endl;
            std::cout << "\t\t" << y.second.getFinal() << std::endl;
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
        this->mapaDocumentos[id_doc] = Documento(id_doc, ruta + slash + str_entrada);
        this->contadorDocumentos[id_doc] = 0;
        std::cout << "Agregando archivo " << str_entrada << " para indexar." << std::endl;
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
vector<pair<int, double>> indexarLibro::buscarConOperador(std::string consulta, int operador) {
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
            if (operador == INDEXAR_AND) {
                docs_resultado = this->calcularInterseccion(docs_resultado, docs);
            } else if (operador == INDEXAR_OR) {
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
            double tf_num = contarPalabrasEnDocumento(palabra, doc_id);
            double tf_denom = this->contadorDocumentos[doc_id];
            double tf = tf_num / tf_denom;
            double  idf_num = this->mapaDocumentos.size();
            double idf_denom = this->indice[palabra].size();
            double idf = std::log10(idf_num / (idf_denom + 1)) + 1;
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
 * Busca en el índice del libro las palabras clave proporcionadas y devuelve los resultados con sus puntajes.
 * 
 * @param consulta La consulta de búsqueda que contiene las palabras clave.
 * @return Un vector de pares que contiene los resultados de la búsqueda, donde el primer elemento del par es el número de documento y el segundo elemento es el puntaje.
 */
vector<pair<int, double>> indexarLibro::buscar(string consulta) {
    vector<pair<int, double>> resultado_and =  this->buscarConOperador(consulta, INDEXAR_AND);
    vector<pair<int, double>> resultado_or =  this->buscarConOperador(consulta, INDEXAR_OR);
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
 * @brief Obtiene la siguiente palabra de una consulta.
 * 
 * @param consulta La consulta de búsqueda.
 * @param palabra La palabra obtenida.
 * @param pos La posición actual de la consulta.
 * @return true si se obtuvo una palabra, false de lo contrario.
 */
int indexarLibro::contarPalabrasEnDocumento(string palabra, int id_doc){
    int contador = 0;
    for (auto &pos_doc: indice[palabra]) {
        if (pos_doc.getDocumento().getId() == id_doc) { // Cambia doc_id a id_doc
            contador += pos_doc.getPosiciones().size();
        }
    }
    return contador;
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
        file.seekg(doc.getParrafos()[id_parrafo].getInicio());
        char c;
        while (file.tellg() < doc.getParrafos()[id_parrafo].getFinal()) {
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

TablaHash indexarLibro::getTablaHash() {
    return tabla;
}