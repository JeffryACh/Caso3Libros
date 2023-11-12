#include <iostream>
#include <iomanip>
#include <sstream>
#include "IndexadorTFIDF.h"

void imprimirIndentado(const std::string& texto, int nivelIndentado) {
    std::istringstream iss(texto);
    std::string line;
    std::string indent(nivelIndentado, ' ');

    while (std::getline(iss, line)) {
        std::cout << indent << line << std::endl;
    }
}

int main(int argc, char **argv) {
    IndexadorLibros indexador = IndexadorLibros();
    if (argc > 1) {
        indexador.indexar(argv[1]);
        bool salir = false;
        while (!salir) {
            std::string consulta;
            std::cout << "*************************************************************" << std::endl;
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
                vector<pair<int, double>> resultado = indexador.buscar(consulta);
                if (resultado.size() > 0) {
                    int cant = 0;
                    std::cout << "Se encontraron " << resultado.size() << " coincidencias de un total de "
                              << indexador.cantidadDocumentos() << " libros" << std::endl;
                    std::cout << "Libros de referencia: " << std::endl;
                    for (auto &doc_id : resultado) {
                        Documento& doc = indexador.getDocumento(doc_id.first);
                        double rank = doc_id.second < 0.0 ? 0.0 : doc_id.second;
                        std::cout << "Libro: " << doc.getTitulo() << "(" << doc.getAutor() << "). Ranking:  "
                                      << std::fixed << std::setprecision(8) << rank << std::endl;
                        if (rank > 0.0) {
                            cant++;
                        }
                        vector<pair<int, int>> parrafos = indexador.obtenerParrafosRelevantes(consulta, doc_id.first);
                        if (!parrafos.empty()) {
                            std::cout << ">>>> Parrafos relevantes <<<<" << std::endl;
                        }
                        for (auto &parrafo_id : parrafos) {
                            std::cout << "<<< Parrafo #" << parrafo_id.first + 1 << " >>> " << std::endl;
                            imprimirIndentado(indexador.textoParrafo(doc_id.first, parrafo_id.first), 4);
                        }
                    }
                    if (cant == 0) {
                        std::cout << "Trate de especificar una consulta con más palabras para resultados más relevantes " << std::endl;
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
