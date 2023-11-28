#ifndef ARBOL_B_H
#define ARBOL_B_H

#include <iostream>
#include <vector>
#include <map>

#include "IndexarLibro.h"
#include "PosicionPalabra.h"
#include "TablaHash.h"


using namespace std;

/**
 * @brief Struct que representa un nodo del árbol B.
 * 
 * map<string, vector<PosicionPalabra>> valor: valor del nodo.
 * Nodo *hijoIzquierdo: hijo izquierdo del nodo.
 * Nodo *hijoDerecho: hijo derecho del nodo.
 * int hijo: cantidad de hijos del nodo.
 * vector<Nodo*> hijos: vector de hijos del nodo.
*/
struct Nodo {
    map<string, vector<PosicionPalabra>> valor;
    Nodo *hijoIzquierdo;
    Nodo *hijoDerecho;
    int hijo;
    vector<Nodo*> hijos;
  };

/**
 * @brief Clase que representa un árbol B.
*/
class ArbolB {
public:
  ArbolB(int orden); // Constructor

  ~ArbolB(); // Destructor

  // Métodos públicos
  void insertar(string palabra); // Inserta un valor en el árbol B.

  bool buscar(PosicionPalabra valor); // Busca un valor en el árbol B.

  void eliminar(PosicionPalabra valor); // Elimina un valor del árbol B.

  void imprimir(); // Imprime los valores del árbol B.

  void eliminarNodo(Nodo *nodo); // Elimina un nodo del árbol B.

  Nodo* buscarRecursivo(string palabra); // Busca un valor en el árbol B.

  int cantidadNodos(); // Retorna la cantidad de nodos del árbol B.

  bool esHoja(Nodo *nodo); // Retorna true si el nodo es hoja, false en caso contrario.

private:

  // Atributos privados
  Nodo *raiz; // Raíz del árbol B.

  int orden; // Orden del árbol B.

  indexarLibro indexador; // Indexador de libros.

  // Métodos privados
  void insertar(string palabra, Nodo *nodo); // Inserta un valor en el árbol B.

  bool buscar(PosicionPalabra valor, Nodo *nodo); // Busca un valor en el árbol B.

  void eliminar(PosicionPalabra valor, Nodo *nodo); // Elimina un valor del árbol B.

  void imprimir(Nodo *nodo); // Imprime los valores del árbol B.
  
  void eliminarNodo(Nodo *nodo); // Elimina un nodo del árbol B.

  Nodo* buscarRecursivo( string palabra, Nodo* nodo); // Busca un valor en el árbol B.

  int cantidadNodos(Nodo *nodo); // Retorna la cantidad de nodos del árbol B.

  bool esHoja(Nodo *nodo); // Retorna true si el nodo es hoja, false en caso contrario.

  void desbalancear(Nodo *nodo, bool esHijoIzquierdo); // Desbalancea el árbol B.
};

#endif // ARBOL_B_H
