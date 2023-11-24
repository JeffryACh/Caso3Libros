#ifndef __DOCUMENTO_H__
#define __DOCUMENTO_H__
#include <string>
#include <map>
#include "Parrafo.h"

class Documento {
private:
    // atributos privados
    int id; // identificador del documento
    std::string ruta; // ruta del documento
    std::string titulo; // titulo del documento
    std::string autor; // autor del documento
    std::map<int, Parrafo> parrafos; // los parrafos del documento (key: id del parrafo, value: el parrafo)
public:
    Documento(); // constructor
    Documento(const Documento& otro); // constructor por copia
    Documento(int id, std::string ruta); // constructor con parametros
    Documento(std::string ruta); // constructor con parametros
    ~Documento() = default; // destructor

    // metodos publicos
    int getId(); // devuelve el id del documento
    const std::string getTitulo(); // devuelve el titulo del documento
    const std::string getAutor(); // devuelve el autor del documento
    const std::string getRuta(); // devuelve la ruta del documento
    void setTitulo(std::string titulo); // establece el titulo del documento
    void setAutor(std::string autor); // establece el autor del documento
    void agregarParrafo(int id, long inicio, long final); // agrega un parrafo al documento (con su id, inicio y fin)
    Parrafo& getParrafo(int id); // devuelve el parrafo con el id especificado
    std::map<int, Parrafo>& getParrafos(); // devuelve una referencia al map de parrafos
};

#endif //__DOCUMENTO_H__
