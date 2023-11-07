#include "indexadorLibros.h"
#include "RankingLibros.h"


int main(int argc, char **argv) {
    IndexadorLibros indexador = IndexadorLibros();
    string ruta = "Libros";
    argc = 30;
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
                std::cout << "Debe ingresar una consulta" << std::endl;
                continue;
            }
            else {
                cout << "Buscando " << consulta << endl;
                std::unordered_map<std::string, int> resultado = RankingLibros(indexador).getTopMatches(consulta);
                if (resultado.size() > 0) {
                    for (const auto& match : resultado) {
                        std::cout << "Documento: " << match.first << " - Relevancia: " << match.second << std::endl;
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
