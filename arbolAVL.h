#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "TablaHash.h"
using namespace std;

class AVL_Libros {
public:
    AVL_Libros* Hizq, * Hder; // Hijos izquierdo y derecho
    int FB; // Factor de balance

    TablaHash tablaHash; // Tabla hash que almacena las palabras clave del libro




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
    /**
     * @brief Realiza una rotación doble a la izquierda en el árbol AVL.
     * 
     * @param n1 Puntero al puntero del nodo que se va a rotar.
     * @param n2 Puntero al nodo que se va a rotar.
     */
    void RotacionDobleIzquierda(AVL_Libros** n1, AVL_Libros* n2);

    /**
     * @brief Realiza una rotación doble a la derecha en el árbol AVL.
     * 
     * @param n1 Puntero al puntero del nodo que se va a rotar.
     * @param n2 Puntero al nodo que se va a rotar.
     */
    void RotacionDobleDerecha(AVL_Libros** n1, AVL_Libros* n2);

    /**
     * @brief Realiza una rotación simple a la izquierda en el árbol AVL.
     * 
     * @param n1 Puntero al puntero del nodo que se va a rotar.
     * @param n2 Puntero al nodo que se va a rotar.
     */
    void RotacionSimpleIzquierda(AVL_Libros** n1, AVL_Libros* n2);

    /**
     * @brief Realiza una rotación simple a la derecha en el árbol AVL.
     * 
     * @param n1 Puntero al puntero del nodo que se va a rotar.
     * @param n2 Puntero al nodo que se va a rotar.
     */
    void RotacionSimpleDerecha(AVL_Libros** n1, AVL_Libros* n2);

    /**
     * @brief Destruye el árbol AVL.
     * 
     * @param raiz Puntero al puntero de la raíz del árbol.
     */
    void destruirArbol(AVL_Libros** raiz);

    /**
     * @brief Inserta un nodo en el árbol AVL y balancea el árbol si es necesario.
     * 
     * @param r Puntero al puntero de la raíz del árbol.
     * @param Hh Puntero a un booleano que indica si la altura del árbol ha crecido.
     * @param libro Nombre del libro a insertar.
     * @param titulo Título del libro a insertar.
     * @param autor Autor del libro a insertar.
     */
    void InsertarBalanceado(AVL_Libros** r, bool* Hh, string libro, string titulo, string autor);

public:
    AVL_Libros* raiz; // Puntero a la raíz del árbol AVL
    bool Hh; // Verdadero si la altura del árbol ha crecido

    /**
     * @brief Constructor de la clase AVL_Principal.
     * 
     * Inicializa el puntero raiz en NULL y el booleano Hh en true.
     */
    AVL_Principal() {
        raiz = NULL;
        Hh = true;
    }

    /**
     * @brief Destructor de la clase AVL_Principal.
     * 
     * Destruye el árbol AVL.
     */
    ~AVL_Principal();

    /**
     * @brief Inserta un nodo en el árbol AVL.
     * 
     * @param libro Nombre del libro a insertar.
     * @param titulo Título del libro a insertar.
     * @param autor Autor del libro a insertar.
     */
    void insertarNodo(string libro, string titulo, string autor);

    /**
     * @brief Busca un libro en el árbol AVL.
     * 
     * @param raiz Puntero a la raíz del árbol.
     * @param titulo Título del libro a buscar.
     * @return Puntero al nodo que contiene el libro buscado, o NULL si no se encuentra.
     */
    AVL_Libros* buscarLibro(AVL_Libros* raiz, string titulo);

    /**
     * @brief Inserta un nodo en el árbol AVL utilizando el título del libro como clave.
     * 
     * @param titulo Título del libro a insertar.
     */
    void insertarPorTitulo(string titulo);

    /**
     * @brief Busca un libro en el árbol AVL utilizando el título del libro como clave.
     * 
     * @param titulo Título del libro a buscar.
     * @return Puntero al nodo que contiene el libro buscado, o NULL si no se encuentra.
     */
    AVL_Libros* buscarLibroPorTitulo(string titulo);
};
