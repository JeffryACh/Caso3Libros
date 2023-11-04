#include <iostream>
#include "indexador.h"

int main(int argc, char **argv) {
    IndexadorLibros indexador = IndexadorLibros();
    string ruta = "Libros";
    argc = 2;
    if (argc > 1) {
        indexador.indexar(ruta);
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
                vector<int> resultado;
                resultado = indexador.buscar(consulta);
                vector<string> ranking;
                ranking = indexador.ranking(resultado);
                if (resultado.size() > 0) {
                    std::cout << "Ranking: " << std::endl;
                    std ::cout << "Los siguientes archivos contienen ALGUNA de las palabras buscadas: " << std::endl;
                    std::cout << ranking.size() << std::endl;
                    for (auto &doc_id : ranking) {
                        std::cout << "Documento: " << indexador.getDocumento(std::stoi(doc_id)) << std::endl;
                        std::cout << "Puntaje: " << std::stoi(doc_id) << std::endl;
                        std::cout << doc_id << std::endl;
                    }
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
