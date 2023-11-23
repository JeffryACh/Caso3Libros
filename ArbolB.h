#ifndef ARBOL_B_H
#define ARBOL_B_H

#include <iostream>

using namespace std;

template <typename T> // Clase genérica para el tipo de dato T
class ArbolB {
public:

  ArbolB(int orden); // Constructor

  ~ArbolB();  // Destructor

  void insertar(T valor); // Insertar un valor en el árbol

  bool buscar(T valor); // Buscar un valor en el árbol

  void eliminar(T valor); // Eliminar un valor del árbol

  void imprimir();  // Imprimir el árbol

private:

  int orden;  // Orden del árbol

  struct Nodo {
    T valor;  // Valor del nodo
    Nodo *hijoIzquierdo;  // Puntero al hijo izquierdo
    Nodo *hijoDerecho;  // Puntero al hijo derecho
  };

  Nodo *raiz; // Puntero a la raíz del árbol

  void insertar(T valor, Nodo *nodo); // Insertar un valor en el árbol

  bool buscar(T valor, Nodo *nodo); // Buscar un valor en el árbol

  void eliminar(T valor, Nodo *nodo); // Eliminar un valor del árbol

  void imprimir(Nodo *nodo);  // Imprimir el árbol

};

#endif // ARBOL_B_H