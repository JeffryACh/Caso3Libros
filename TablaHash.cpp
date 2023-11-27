#include "TablaHash.h"
#include <iostream>
#include <string>

using namespace std;

TablaHash::TablaHash() {
} // constructor

/**
 * @brief Inserta una palabra y un libro en la tabla hash.
 * 
 * Si la palabra no se encuentra en la tabla, se crea un nuevo vector vacío y se agrega el libro con una frecuencia de 1.
 * Si la palabra ya existe en la tabla, se busca el libro en el vector asociado a la palabra.
 * Si el libro se encuentra, se incrementa su frecuencia en 1.
 * Si el libro no se encuentra, se agrega al vector con una frecuencia de 1.
 * 
 * @param palabra La palabra a insertar.
 * @param libro El libro asociado a la palabra.
 */
void TablaHash::insertar(string palabra, Documento libro) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se crea un vector vacío
        vector<pair<Documento, int>> libros;
        libros.push_back(make_pair(libro, 1));
        tabla[palabra] = libros;
    } else {
        bool libroEncontrado = false;
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) { // se busca el libro en el vector asociado a la palabra
            if (it->first.getTitulo() == libro.getTitulo()) { // si el libro se encuentra, se incrementa su frecuencia en 1
                it->second++; // se incrementa la frecuencia del libro en 1
                libroEncontrado = true;
                break;
            }
        }
        if (!libroEncontrado) {
            tabla[palabra].push_back(make_pair(libro, 1));
        }
    }
}

/**
 * @brief Busca una palabra en la tabla hash y devuelve los documentos asociados a esa palabra.
 * 
 * @param palabra La palabra a buscar en la tabla hash.
 * @return Un vector de pares (Documento, int) que representa los documentos asociados a la palabra.
 *         Si la palabra no se encuentra, se retorna un vector vacío.
 */
vector<pair<Documento, int> > TablaHash::buscar(string palabra) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se retorna un vector vacío
        return vector<pair<Documento, int>>();
    } else {
        return tabla[palabra];
    }
}

/**
 * Imprime los elementos almacenados en la tabla hash.
 * 
 * Recorre la tabla hash e imprime cada elemento junto con su cantidad.
 * 
 * @param None
 * @return None
 */
void TablaHash::imprimir() {
    for (auto it = tabla.begin(); it != tabla.end(); it++) {
        cout << it->first << ": " << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << "\t" << it2->first.getTitulo() << " (" << it2->second << ")" << endl;
        }
    }
}

/**
 * Imprime los libros almacenados en la tabla hash.
 * 
 * Recorre la tabla hash e imprime los títulos y autores de los libros almacenados.
 */
void TablaHash::imprimirLibros() {
    for (auto it = tabla.begin(); it != tabla.end(); it++) {
        cout << it->first << ": " << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << "Titulo: " << it2->first.getTitulo() << " - " << "Autor: "<< it2->first.getAutor() << endl;
        }
    }
}

/**
 * @brief Clase que representa un documento.
 * 
 * @param palabra La palabra a buscar en la tabla hash.
 * 
 * Esta clase representa un documento y contiene información sobre el mismo, como el título, el autor y el número de apariciones de una palabra en el documento.
 * 
 * @return Un Documento que representa el libro con más apariciones de la palabra.
 */
Documento TablaHash::buscarLibroConMasApariciones(string palabra) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se retorna un libro vacío
        return Documento();
    } else {
        int max = 0;
        Documento libroConMasApariciones;
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->second > max) {
                max = it->second;
                libroConMasApariciones = it->first;
            }
        }
        return libroConMasApariciones;
    }
}

/**
 * Obtiene los documentos con las mejores coincidencias para una palabra dada.
 * 
 * @param palabra La palabra para la cual se desean obtener las mejores coincidencias.
 * @return Un vector de Documento con los documentos que tienen las mejores coincidencias para la palabra dada.
 *         Si no se encuentra la palabra, se retorna un vector vacío.
 */
vector<Documento> TablaHash::getTopMatches(string palabra) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se retorna un vector vacío
        return vector<Documento>();
    } else {
        vector<Documento> topMatches;
        int max = 0;
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->second > max) {
                max = it->second;
            }
        }
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->second == max) {
                topMatches.push_back(it->first);
            }
        }
        return topMatches;
    }
}

/**
 * Obtiene los documentos con las mejores 10 coincidencias para un conjunto de palabras dadas.
 * 
 * @param palabras El conjunto de palabras para las cuales se desean obtener las mejores coincidencias.
 * @return Un vector de Documento con los documentos que tienen las mejores coincidencias para las palabras dadas.
 *         Si no se encuentra alguna de las palabras, se retorna un vector vacío.
 */

vector<Documento> TablaHash::getTopMatches(vector<string> palabras) {
    vector<Documento> topMatches;
    vector<Documento> topMatchesAux;
    Documento libro;
    for (auto& palabra : palabras) {
        cout << "Palabra: " << palabra << endl;
        topMatchesAux = getTopMatches(palabra);
        topMatches.push_back(libroConMasApariciones( topMatchesAux, palabra));
    }
    topMatches = interseccion(topMatches, topMatchesAux);
    topMatches = quitarLibrosRepetidos(topMatches);
    cout << "Salio del primer for" << endl;
    if (topMatches.size() < 10) {
        cout << "Top matches: " << topMatches.size() << endl;
        while(topMatches.size() != 10) {
            for (auto& palabra : palabras){
                topMatchesAux = getLibrosDePalabra(palabra);
                Documento librito;
                librito = segundoLibroConMasApariciones(palabra, topMatchesAux);
                if (libroExiste(topMatches, librito)) {
                    librito = tercerLibroConMasApariciones(palabra, topMatchesAux);
                    if (libroExiste(topMatches, librito)) {
                        librito = libroConMasApariciones(palabra);
                        if (libroExiste(topMatches, librito)){
                            librito = segundoLibroConMasApariciones(palabra);
                            topMatches.push_back(librito);
                        }
                        else {
                            cout << "Libro no existe" << endl;
                            cout << "Libro: " << librito.getTitulo() << endl;
                            topMatches.push_back(librito);
                        }
                    }
                    else {
                        cout << "Libro no existe" << endl;
                        cout << "Libro: " << librito.getTitulo() << endl;
                        topMatches.push_back(librito);
                    }
                }
                else {
                    cout << "Libro no existe" << endl;
                    cout << "Libro: " << librito.getTitulo() << endl;
                    topMatches.push_back(librito);
                }
                if (topMatches.size() == 10) {
                    break;
                }
            } 
        }
    }
    else {
        cout << "Top matches: " << topMatches.size() << endl;
        while(topMatches.size() != 10) {
            std::vector<Documento> nuevosTopMatches;
            for (auto& libro : topMatches) {
                bool libroValido = true;
                for (auto& palabra : palabras) {
                    if (vecesPalabraEnLibro(palabra, libro) == 0) {
                        cout << "Libro no valido" << endl;
                        libroValido = false;
                        break;
                    }
                }
                if (libroValido) {
                    nuevosTopMatches.push_back(libro);
                }
            }
            if (nuevosTopMatches.size() == 0) {
                break;
            }
            topMatches = nuevosTopMatches;
        }
    }
    topMatches = quitarLibrosRepetidos(topMatches);
    return topMatches;
}

/**
 * Retorna la tabla hash.
 * 
 * @return La tabla hash.
 */

unordered_map<string, vector<pair<Documento, int> > > TablaHash::getTabla() {
    return tabla;
}

/**
 * Retorna la cantidad de veces que aparece una palabra en un libro.
 * 
 * @param palabra La palabra a buscar.
 * @param libro El libro en el cual se busca la palabra.
 * @return La cantidad de veces que aparece la palabra en el libro.
 *         Si no se encuentra la palabra, se retorna 0.
 */
int TablaHash::cantidadDePalabrasEnLibro(string palabra, Documento libro) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se retorna 0
        return 0;
    } else {
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->first.getTitulo() == libro.getTitulo()) {
                return it->second;
            }
        }
        return 0;
    }
}

/**
 * Retorna el libro con más apariciones.
 * 
 * @return El libro con más apariciones.
 */
Documento TablaHash::libroConMasApariciones() {
    int max = 0;
    Documento libroConMasApariciones;
    for (auto it = tabla.begin(); it != tabla.end(); it++) { // se recorre la tabla hash
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {   // se recorre el vector asociado a la palabra
            if (it2->second > max) {   // si la frecuencia del libro es mayor que el máximo, se actualiza el máximo
                max = it2->second; 
                libroConMasApariciones = it2->first;
            }
        }
    }
    cout << "Libro con más apariciones: " << libroConMasApariciones.getTitulo() << " (" << max << ")" << endl; // se imprime el libro con más apariciones
    return libroConMasApariciones; 
}

/**
 * Retorna los libros asociados a una palabra.
 * 
 * @param palabra La palabra a buscar.
 * @return Un vector de Documento con los libros asociados a la palabra.
 *         Si no se encuentra la palabra, se retorna un vector vacío.
 */
vector<Documento> TablaHash::getLibrosDePalabra(string palabra) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se retorna un vector vacío
        return vector<Documento>();
    } else {
        vector<Documento> libros;
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            libros.push_back(it->first);
        }
        return libros;
    }
}

/**
 * Verifica si una palabra existe en la tabla hash.
 * 
 * @param palabra La palabra a buscar.
 * @return true si la palabra existe en la tabla hash, false en caso contrario.
 */
bool TablaHash::existePalabra(string palabra) {
    return tabla.find(palabra) != tabla.end();
}

/**
 * Verifica si la tabla hash está vacía.
 * 
 * @return true si la tabla hash está vacía, false en caso contrario.
 */
bool TablaHash::estaVacia() {
    return tabla.empty();
}

/**
 * @brief Retorna los libros que hacen match con las palabras ingresadas. 
 * 
 * @param palabras El conjunto de palabras para las cuales se desean obtener los libros que hacen match.
 * @return Un vector de Documento con los libros que hacen match con las palabras ingresadas.
*/
vector<Documento> TablaHash::getLibrosMacth(vector<string> palabras) {
    vector<Documento> librosMatch;
    for (auto& palabra : palabras) { // se recorre el vector de palabras
        if (existePalabra(palabra)) { // si la palabra se encuentra en la tabla hash
            for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) { // se recorre el vector asociado a la palabra
                librosMatch.push_back(it->first); // se agrega el libro al vector de libros match
            }
        }
    }
    return librosMatch;
}

/**
 * Retorna la cantidad de veces que aparece una palabra en un libro.
 * 
 * @param palabra La palabra a buscar.
 * @param libro El libro en el cual se busca la palabra.
 * @return La cantidad de veces que aparece la palabra en el libro.
 *         Si no se encuentra la palabra, se retorna 0.
 */
int TablaHash::vecesPalabraEnLibro(string palabra, Documento libro) {
    if (tabla.find(palabra) == tabla.end()) { // si no se encuentra la palabra, se retorna 0
        return 0;
    } else {
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->first.getTitulo() == libro.getTitulo()) {
                return it->second;
            }
        }
        return 0;
    }
}

/**
 * Retorna la intersección de dos vectores de libros.
 * 
 * @param libros1 El primer vector de libros.
 * @param libros2 El segundo vector de libros.
 * @return Un vector de Documento con la intersección de los dos vectores de libros.
 */
vector<Documento> TablaHash::interseccion(vector<Documento> libros1, vector<Documento> libros2) {
    vector<Documento> interseccion;
    for (auto& libro1 : libros1) { // se recorre el primer vector de libros
        for (auto& libro2 : libros2) { // se recorre el segundo vector de libros
            if (libro1.getTitulo() == libro2.getTitulo()) { // si el libro se encuentra en los dos vectores, se agrega a la intersección
                interseccion.push_back(libro1);
            }
        }
    }
    return interseccion;
}

/**
 * @brief Saca el libro con más apariciones de una palabra.
 * 
 * @param palabra La palabra a buscar.
 * @return El libro con más apariciones de una palabra.
 *        Si no se encuentra la palabra, se retorna un libro vacío.
 */
Documento TablaHash::libroConMasApariciones(string palabra) {
    if (!existePalabra(palabra)) { // si no se encuentra la palabra, se retorna un libro vacío
        return Documento();
    } else {
        int max = 0;
        Documento libroConMasApariciones;
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->second > max) {
                max = it->second;
                libroConMasApariciones = it->first;
            }
        }
        return libroConMasApariciones;
    }
}

/**
 * @brief Saca el libro con más apariciones de una palabra.
 * 
 * @param libros El vector de libros.
 * @param palabra La palabra a buscar.
 * @return El libro con más apariciones de una palabra.
 *        Si no se encuentra la palabra, se retorna un libro vacío.
 */
Documento TablaHash::libroConMasApariciones(vector<Documento> libros, string palabra) {
    if (!existePalabra(palabra)) { // si no se encuentra la palabra, se retorna un libro vacío
        return Documento();
    } else {
        int max = 0;
        Documento Libro;
        for (auto& libro : libros) {
            if (vecesPalabraEnLibro(palabra, libro) > max) {
                max = vecesPalabraEnLibro(palabra, libro);
                Libro = libro;
            }
        }
        return Libro;
    }
}

bool TablaHash::libroExiste(vector<Documento> libros, Documento libro) {
    for (auto& libroAux : libros) {
        if (libroAux.getTitulo() == libro.getTitulo()) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Saca el segundo libro con más apariciones de una palabra.
 * 
 * @param palabra La palabra a buscar.
 * @return El segundo libro con más apariciones de una palabra.
 *        Si no se encuentra la palabra, se retorna un libro vacío.
 */
Documento TablaHash::segundoLibroConMasApariciones(string palabra, vector<Documento> libros) {
    if (!existePalabra(palabra)) { // si no se encuentra la palabra, se retorna un libro vacío
        return Documento();
    } else {
        int max = 0;
        Documento libroConMasApariciones;
        for (auto& libro : libros) {
            if (vecesPalabraEnLibro(palabra, libro) > max) {
                max = vecesPalabraEnLibro(palabra, libro);
                libroConMasApariciones = libro;
            }
        }
        int segundoMax = 0;
        Documento segundoLibroConMasApariciones;
        for (auto& libro : libros) {
            if (vecesPalabraEnLibro(palabra, libro) > segundoMax && libro.getTitulo() != libroConMasApariciones.getTitulo()) {
                segundoMax = vecesPalabraEnLibro(palabra, libro);
                segundoLibroConMasApariciones = libro;
            }
        }
        return segundoLibroConMasApariciones;
    }
}

/**
 * @brief Quita los libros repetidos de un vector de libros.
 * 
 * @param libros El vector de libros.
 * @return Un vector de Documento con los libros sin repetir.
 */
vector<Documento> TablaHash::quitarLibrosRepetidos(vector<Documento> libros) {
    vector<Documento> librosSinRepetir;
    for (auto& libro : libros) {
        if (!libroExiste(librosSinRepetir, libro)) {
            librosSinRepetir.push_back(libro);
        }
    }
    return librosSinRepetir;
}

/**
 * @brief Saca el tercer libro con más apariciones de una palabra.
 * 
 * @param palabra La palabra a buscar.
 * @return El tercer libro con más apariciones de una palabra.
 *        Si no se encuentra la palabra, se retorna un libro vacío.
 */
Documento TablaHash::tercerLibroConMasApariciones(string palabra, vector<Documento> libros) {
    if (!existePalabra(palabra)) { // si no se encuentra la palabra, se retorna un libro vacío
        return Documento();
    } else {
        int max = 0;
        Documento libroConMasApariciones;
        for (auto& libro : libros) {
            if (vecesPalabraEnLibro(palabra, libro) > max) {
                max = vecesPalabraEnLibro(palabra, libro);
                libroConMasApariciones = libro;
            }
        }
        int segundoMax = 0;
        Documento segundoLibroConMasApariciones;
        for (auto& libro : libros) {
            if (vecesPalabraEnLibro(palabra, libro) > segundoMax && libro.getTitulo() != libroConMasApariciones.getTitulo()) {
                segundoMax = vecesPalabraEnLibro(palabra, libro);
                segundoLibroConMasApariciones = libro;
            }
        }
        int tercerMax = 0;
        Documento tercerLibroConMasApariciones;
        for (auto& libro : libros) {
            if (vecesPalabraEnLibro(palabra, libro) > tercerMax && libro.getTitulo() != libroConMasApariciones.getTitulo() && libro.getTitulo() != segundoLibroConMasApariciones.getTitulo()) {
                tercerMax = vecesPalabraEnLibro(palabra, libro);
                tercerLibroConMasApariciones = libro;
            }
        }
        return tercerLibroConMasApariciones;
    }
}

/**
 * @brief Saca el segundo libro con más apariciones de una palabra.
 * 
 * @param palabra La palabra a buscar.
 * @return El segundo libro con más apariciones de una palabra.
 *        Si no se encuentra la palabra, se retorna un libro vacío.
 */
Documento TablaHash::segundoLibroConMasApariciones(string palabra) {
    if (!existePalabra(palabra)) { // si no se encuentra la palabra, se retorna un libro vacío
        return Documento();
    } else {
        int max = 0;
        Documento libroConMasApariciones;
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->second > max) {
                max = it->second;
                libroConMasApariciones = it->first;
            }
        }
        int segundoMax = 0;
        Documento segundoLibroConMasApariciones;
        for (auto it = tabla[palabra].begin(); it != tabla[palabra].end(); it++) {
            if (it->second > segundoMax && it->first.getTitulo() != libroConMasApariciones.getTitulo()) {
                segundoMax = it->second;
                segundoLibroConMasApariciones = it->first;
            }
        }
        return segundoLibroConMasApariciones;
    }
}