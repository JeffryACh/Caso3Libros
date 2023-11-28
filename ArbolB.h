#ifndef ARBOL_B_H
#define ARBOL_B_H

#include <iostream>
#include <vector>

#include "IndexarLibro.h"
#include "PosicionPalabra.h"
#include "TablaHash.h"


using namespace std;
struct Nodo {
    map<string, vector<PosicionPalabra>> valor;
    Nodo *hijoIzquierdo;
    Nodo *hijoDerecho;
    int hijo;
  };

/**
 * @brief Clase que representa un árbol B.
*/
class ArbolB {
public:
  ArbolB(int orden); // Constructor

  ~ArbolB(); // Destructor

  // Métodos públicos
  void insertar(string palabra);

  bool buscar(PosicionPalabra valor);

  void eliminar(PosicionPalabra valor);

  void imprimir();

  void eliminarNodo(Nodo *nodo);

  Nodo* buscarRecursivo(string palabra);

  int cantidadNodos();

  bool esHoja(Nodo *nodo);

private:

  // Atributos privados
  Nodo *raiz;

  int orden;

  indexarLibro indexador;

  // Métodos privados
  void insertar(string palabra, Nodo *nodo);

  bool buscar(PosicionPalabra valor, Nodo *nodo);

  void eliminar(PosicionPalabra valor, Nodo *nodo);

  void imprimir(Nodo *nodo);
  
  void eliminarNodo(Nodo *nodo);

  Nodo* buscarRecursivo( string palabra, Nodo* nodo);

  int cantidadNodos(Nodo *nodo);

  bool esHoja(Nodo *nodo);

  void desbalancear(Nodo *nodo, bool esHijoIzquierdo);
};

#endif // ARBOL_B_H
