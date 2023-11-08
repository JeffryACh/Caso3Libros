#include <iostream>
#include "IndexadorTFIDF.h"

int main(int argc, char **argv) {
    IndexadorLibros indexador = IndexadorLibros();
    if (argc > 1) {
        indexador.indexar(argv[1]);
        bool salir = false;
        while (!salir) {
            std::string consulta;
            std::cout << "Ingrese la consulta a buscar (\"salir\" termina el programa): ";
            std::getline(std::cin, consulta);
            if (consulta == "salir") {
                salir = true;
            }
            else if (consulta.empty()) {
                continue;
            }
            else {
                cout << "Buscando " << consulta << endl;
                vector<pair<int, float>> resultado = indexador.buscar(consulta, INDEXADOR_OR);
                if (resultado.size() > 0) {
                    std::cout << "Libros de referencia: " << std::endl;
                    for (auto &doc_id : resultado) {
                        std::cout << "Archivo: " << indexador.getDocumento(doc_id.first) << ". Score:  " << doc_id.second << std::endl;
                    }
                } else {
                    std::cout << "No se encontraron libros de referencia para las palabras buscadas" << std::endl;
                }
            }
        }
    } else {
        cout << "Debe ingresar la ruta de los archivos a indexar" << endl;
    }
    return 0;
}
