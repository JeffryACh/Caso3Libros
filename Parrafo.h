#ifndef __PARRAFO_H__
#define __PARRAFO_H__
class Parrafo {
private:
    int id;
    int inicio;
    int final;
public:
    Parrafo(int id, int inicio, int final);
    Parrafo(const Parrafo& otro);
    Parrafo() = default;;
    ~Parrafo() = default;

    int getId();
    int getInicio();
    int getFinal();
};
#endif //__PARRAFO_H__
