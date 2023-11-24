#include "indexarLibro.h"

using namespace std;

indexarLibro::indexarLibro() {
}

void indexarLibro::indexar(string ruta) {
    procesarRuta(ruta);

    for (auto it = tabla
}

void indexarLibro::procesarRuta(const string& ruta) {
    ifstream archivo(ruta);
    string linea;
    int id_doc = 0;
    Documento documento;
    while (getline(archivo, linea)) {
        if (linea == "<doc>") {
            id_doc++;
            documento = Documento(id_doc, ruta);
        } else if (linea == "</doc>") {
            indexarDocumento(documento);
        } else {
            documento.agregarParrafo(id_doc, archivo.tellg() - static_cast<std::streamoff>(linea.length() + 1), archivo.tellg());
        }
    }
}

void indexarLibro::indexarDocumento(Documento &documento) {
    unordered_map<string, int> palabras;
    string palabra;
    int pos = 0;
    while (documento.obtenerPalabra(palabra, pos)) {
        transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
        if (palabras.find(palabra) == palabras.end()) {
            palabras[palabra] = 1;
        } else {
            palabras[palabra]++;
        }
    }

    for (auto it = palabras.begin(); it != palabras.end(); ++it) {
        tabla[it->first].push_back(make_pair(documento.getId(), it->second));
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