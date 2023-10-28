

#pragma once
#include <iostream>
using namespace std;

class AVL_Libros {
public:
    AVL_Libros* Hizq, * Hder; // Hijos izquierdo y derecho
    int FB; // Factor de balance

    string libro;
    string titulo;
    string autor;




    /**
     * @brief Constructor de la clase AVL_Libros
     * 
     * @param libro Nombre del libro
     * @param titulo Título del libro
     * @param autor Autor del libro
     * @param der Puntero al subárbol derecho
     * @param izq Puntero al subárbol izquierdo
     */
    AVL_Libros( string libro,string titulo,string autor,AVL_Libros* der = NULL, AVL_Libros* izq = NULL) {
        Hizq = izq;
        Hder = der;
        this->libro=libro;
        this->titulo=titulo;
        this->autor=autor;

        FB = 0; // Factor de balance
    }

    friend class AVL_Principal; // AVL_Principal puede acceder a los miembros privados de AVL_Libros
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
    bool Hh; // Verdadero si la altura del árbol ha crecido

    /**
     * @brief Constructor de la clase AVL_Principal
     * 
     * Inicializa el puntero raiz en NULL y el booleano Hh en true.
     */
    AVL_Principal() {
        raiz = NULL;
        Hh = true;
    }
    ~AVL_Principal();

    void insertarNodo(string libro,string titulo,string autor);
    AVL_Libros* buscarLibro(AVL_Libros* raiz, string titulo);

    void insertarPorTitulo(string titulo);
    AVL_Libros* buscarLibroPorTitulo(string titulo);

};
