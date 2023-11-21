#ifndef __PARRAFO_H__
#define __PARRAFO_H__
/**
 * Esta clase almacena la información de un párrafo, en particular el offset de donde
 * inicia y donde termina en el archivo correspondiente al documento.
 */
class Parrafo {
private:
    int id;
    long inicio;
    long final;
public:
    Parrafo(int id, long inicio, long final); // Constructor
    Parrafo(const Parrafo& otro); // Constructor por copia
    Parrafo() = default;; // Constructor por defecto
    ~Parrafo() = default;

    int getId(); // Devuelve el id del párrafo
    long getInicio(); // Devuelve el offset de inicio del párrafo
    long getFinal(); // Devuelve el offset de fin del párrafo
};
#endif //__PARRAFO_H__
