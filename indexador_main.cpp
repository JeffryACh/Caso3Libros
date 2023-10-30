#include <iostream>
#include "indexador.h"

int main(int argc, char **argv) {
    IndexadorLibros indexador = IndexadorLibros();
    if (argc > 1) {
        indexador.indexar(argv[1]);
        vector<int> resultado = indexador.buscar("A room furnished comfortably and tastefully");
        for (auto &doc_id : resultado) {
            cout << doc_id << endl;
        }
    } else {
        cout << "Debe ingresar la ruta de los archivos a indexar" << endl;
    }
    return 0;
}
