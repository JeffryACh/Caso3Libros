#ifndef __DOCUMENTO_H__
#define __DOCUMENTO_H__
#include <string>
#include <map>
#include "Parrafo.h"

class Documento {
private:
    int id{};
    std::string ruta;
    std::string titulo;
    std::string autor;
    std::map<int, Parrafo> parrafos;
public:
    Documento();
    Documento(const Documento& otro);
    Documento(int id, std::string ruta);
    ~Documento() = default;;
    int getId();
    const std::string getTitulo();
    const std::string getAutor();
    const std::string getRuta();
    void setTitulo(std::string titulo);
    void setAutor(std::string autor);
    void agregarParrafo(int id, long inicio, long final);
    Parrafo& getParrafo(int id);
};

#endif //__DOCUMENTO_H__
