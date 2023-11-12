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
    Parrafo(int id, long inicio, long final);
    Parrafo(const Parrafo& otro);
    Parrafo() = default;;
    ~Parrafo() = default;

    int getId();
    long getInicio();
    long getFinal();
};
#endif //__PARRAFO_H__
