#include <iostream>
#include "indexador.h"

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
                vector<int> resultado = indexador.buscar(consulta);
                if (resultado.size() > 0) {
                    std::cout << "Los siguientes archivos contienen TODAS las palabras buscadas: " << std::endl;
                    for (auto &doc_id : resultado) {
                        std::cout << indexador.getDocumento(doc_id) << std::endl;
                    }
                } else {
                    std::cout << "No se encontraron archivos que contengan TODAS las palabras buscadas" << std::endl;
                }
            }
        }
    } else {
        cout << "Debe ingresar la ruta de los archivos a indexar" << endl;
    }
    return 0;
}
