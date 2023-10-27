

#pragma once
#include <iostream>
using namespace std;

class AVL_Libros {
public:
    AVL_Libros* Hizq, * Hder;
    int FB; // Factor de balance

    string libro;
    string titulo;
    string autor;




    AVL_Libros( string libro,string titulo,string autor,AVL_Libros* der = NULL, AVL_Libros* izq = NULL) {
        Hizq = izq;
        Hder = der;
        this->libro=libro;
        this->titulo=titulo;
        this->autor=autor;

        FB = 0;
    }

    friend class AVL_Principal;
};

class AVL_Principal {
private:
    void RotacionDobleIzquierda(AVL_Libros** n1, AVL_Libros* n2);
    void RotacionDobleDerecha(AVL_Libros** n1, AVL_Libros* n2);
    void RotacionSimpleIzquierda(AVL_Libros** n1, AVL_Libros* n2);
    void RotacionSimpleDerecha(AVL_Libros** n1, AVL_Libros* n2);
    void destruirArbol(AVL_Libros** raiz);
    void InsertarBalanceado(AVL_Libros** r, bool*, string libro,string titulo,string autor);

public:
    AVL_Libros* raiz;
    bool Hh;

    AVL_Principal() {
        raiz = NULL;
        Hh = true;
    }
    ~AVL_Principal();

    void insertarNodo(string libro,string titulo,string autor);
    AVL_Libros* buscarLibro(AVL_Libros* raiz, string titulo);

};
