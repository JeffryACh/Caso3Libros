#ifndef __DOCUMENTO_H__
#define __DOCUMENTO_H__
#include <string>

class Documento {
private:
    int id{};
    std::string ruta;
    std::string nombre;
    std::string autor;
public:
    Documento();
    Documento(const Documento& otro);
    Documento(int id, std::string ruta);
    ~Documento() = default;;
    int getId();
    const std::string getNombre();
    const std::string getAutor();
    const std::string getRuta();
    void setNombre(std::string nombre);
    void setAutor(std::string autor);
};

#endif //__DOCUMENTO_H__
