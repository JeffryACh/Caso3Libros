#ifndef ARBOL_B_H
#define ARBOL_B_H

#include <iostream>
#include <vector>

#include "IndexarLibro.h"
#include "PosicionPalabra.h"
#include "TablaHash.h"


using namespace std;
struct Nodo {
    PosicionPalabra valor;
    Nodo *hijoIzquierdo;
    Nodo *hijoDerecho;
  };

/**
 * @brief Clase que representa un árbol B.
*/
class ArbolB {
public:
  ArbolB(int orden); // Constructor

  ~ArbolB(); // Destructor

  // Métodos públicos
  void insertar(PosicionPalabra valor);

  bool buscar(PosicionPalabra valor);

  void eliminar(PosicionPalabra valor);

  void imprimir();

  void eliminarNodo(Nodo *nodo);

  Nodo* buscarRecursivo(Nodo* nodo, string palabra);

  int cantidadNodos(Nodo *nodo);

  bool esHoja(Nodo *nodo);

private:

  // Atributos privados
  Nodo *raiz;

  int orden;

  // Métodos privados
  void insertar(PosicionPalabra valor, Nodo *nodo);

  bool buscar(PosicionPalabra valor, Nodo *nodo);

  void eliminar(PosicionPalabra valor, Nodo *nodo);

  void imprimir(Nodo *nodo);
  
  void eliminarNodo(Nodo *nodo);

  Nodo* buscarRecursivo(Nodo* nodo, string palabra);

  int cantidadNodos(Nodo *nodo);

  bool esHoja(Nodo *nodo);
};

#endif // ARBOL_B_H
