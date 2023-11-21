#include "indexarLibro.h"

using namespace std;

indexarLibro::indexarLibro() {
}

void indexarLibro::indexar(string ruta) {
    procesarRuta(ruta);

    for (auto it = mapaDocumentos.begin(); it != mapaDocumentos.end(); it++) {
        indexarDocumento(it->second);
    }
}

void indexarLibro::procesarRuta(const string& ruta) {
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(ruta.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            string nombreArchivo = ent->d_name;
            if (nombreArchivo != "." && nombreArchivo != "..") {
                string rutaCompleta = ruta + slash + nombreArchivo;
                if (esDirectorio(rutaCompleta)) {
                    procesarRuta(rutaCompleta);
                } else {
                    indexarDocumento(rutaCompleta);
                }
            }
        }
        closedir(dir);
    } else {
        perror("Error al abrir el directorio");
    }
}

