/**
 * @file Documento.cpp
 * 
 * @brief Implementación de la clase Documento.
 * Un documento es un archivo de texto que contiene un título, un autor y uno o más párrafos.
 * 
 * @author Jeffry Araya Ch
 * 
 * @date 28/11/2023 14:00
*/

#include "Documento.h"
#include <string>


/**
 * @brief Constructor de copia de la clase Documento.
 * 
 * Este constructor crea una nueva instancia de Documento a partir de otra instancia existente.
 * Copia los valores de los atributos de la instancia original a la nueva instancia.
 * 
 * @param otro La instancia de Documento a copiar.
 */
Documento::Documento(const Documento& otro) {
    this->id = otro.id;
    this->ruta = otro.ruta;
    this->titulo = otro.titulo;
    this->autor = otro.autor;
    this->parrafos = otro.parrafos;
}


/**
 * @brief Constructor de la clase Documento.
 * 
 * @param id El identificador del documento.
 * @param ruta La ruta del documento.
 */
Documento::Documento(int id, std::string ruta) {
    this->id = id;
    this->ruta = ruta;
    this->parrafos = std::map<int, Parrafo>();
}

Documento::Documento(std::string ruta) {
    this->id = 1;
    this->ruta = ruta;
    this->parrafos = std::map<int, Parrafo>();
}

/**
 * Obtiene el identificador del documento.
 *
 * @return El identificador del documento.
 */
int Documento::getId() {
    return this->id;
}

/**
 * @brief Obtiene la ruta del documento.
 * 
 * @return La ruta del documento.
 */
const std::string Documento::getRuta() {
    return this->ruta;
}

const std::string Documento::getTitulo() {
    return this->titulo;
}

/**
 * @brief Obtiene el autor del documento.
 * 
 * @return El autor del documento.
 */
const std::string Documento::getAutor() {
    return this->autor;
}

/**
 * @brief Establece el título del documento.
 * 
 * @param titulo El título del documento.
 */
void Documento::setTitulo(std::string titulo) {
    this->titulo = titulo;
}

/**
 * @brief Establece el autor del documento.
 * 
 * @param autor El nombre del autor.
 */
void Documento::setAutor(std::string autor) {
    this->autor = autor;
}

Documento::Documento() = default; // Constructor por defecto de la clase Documento

/**
 * @brief Agrega un nuevo párrafo al documento.
 * 
 * @param id El identificador del párrafo.
 * @param inicio La posición de inicio del párrafo en el documento.
 * @param final La posición de fin del párrafo en el documento.
 */
void Documento::agregarParrafo(int id, long inicio, long final) {
    this->parrafos[id] = Parrafo(id, inicio, final);
}

/**
 * Obtiene el párrafo con el ID especificado.
 *
 * @param id El ID del párrafo a obtener.
 * @return Una referencia al objeto Parrafo correspondiente al ID especificado.
 */
Parrafo& Documento::getParrafo(int id) {
    return this->parrafos[id];
}

/**
 * Obtiene una referencia al map de párrafos del documento.
 *
 * @return Una referencia al map de párrafos del documento.
 */
std::map<int, Parrafo>& Documento::getParrafos() {
    return this->parrafos;
}