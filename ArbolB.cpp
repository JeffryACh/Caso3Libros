#include "ArbolB.h"

template <typename T>
ArbolB<T>::ArbolB(int orden) {
  this->orden = orden;
  this->raiz = NULL;
} // Constructor

template <typename T>
ArbolB<T>::~ArbolB() {
  if (this->raiz != NULL) {
    eliminarNodo(this->raiz);
  }
} // Destructor

/**
 * Inserta un valor en el árbol B.
 * @param valor El valor a insertar.
 */
template <typename T>
void ArbolB<T>::insertar(T valor) {
  insertar(valor, this->raiz);
}

/**
 * @brief Busca un valor en el árbol B.
 * 
 * @param valor El valor a buscar.
 * @return true si el valor se encuentra en el árbol, false en caso contrario.
 */
template <typename T>
bool ArbolB<T>::buscar(T valor) {
  return buscar(valor, this->raiz);
}

/**
 * Elimina un valor específico del árbol B.
 * @param valor El valor a eliminar.
 * @tparam T El tipo de dato de los elementos del árbol.
 */
template <typename T>
void ArbolB<T>::eliminar(T valor) {
  eliminar(valor, this->raiz);
}

/**
 * Imprime los elementos del árbol B.
 * @tparam T El tipo de dato de los elementos del árbol.
 */
template <typename T>
void ArbolB<T>::imprimir() {
  imprimir(this->raiz);
}

/**
 * Inserta un valor en el árbol B.
 * 
 * @param valor El valor a insertar.
 * @param nodo El nodo actual en el que se está realizando la inserción.
 * @tparam T El tipo de dato de los elementos del árbol.
 */
template <typename T>
void ArbolB<T>::insertar(T valor, Nodo *nodo) {
  if (nodo == NULL) {
    Nodo *nuevoNodo = new Nodo();
    nuevoNodo->valor = valor;
    nuevoNodo->hijoIzquierdo = NULL;
    nuevoNodo->hijoDerecho = NULL;
    this->raiz = nuevoNodo;
    return;
  }

  int i = 0;
  while (i < this->orden - 1 && valor > nodo->valor) {
    i++;
  }

  if (i < this->orden - 1) {
    insertar(valor, nodo->hijoIzquierdo);
  } else {
    Nodo *nuevoNodo = new Nodo();
    nuevoNodo->valor = valor;
    nuevoNodo->hijoIzquierdo = nodo->hijoIzquierdo;
    nuevoNodo->hijoDerecho = nodo->hijoDerecho;
    nodo->hijoIzquierdo = nuevoNodo;
  }

  if (nodo->hijoIzquierdo != NULL && nodo->hijoIzquierdo->hijos > this->orden - 1) {
    desbalancear(nodo, true);
  }
}

/**
 * @brief Busca un valor en el árbol B.
 * 
 * @tparam T Tipo de dato de los valores en el árbol.
 * @param valor Valor a buscar en el árbol.
 * @param nodo Nodo actual en la búsqueda.
 * @return true si el valor se encuentra en el árbol, false en caso contrario.
 */
template <typename T>
bool ArbolB<T>::buscar(T valor, Nodo *nodo) {
  if (nodo == NULL) {
    return false;
  }

  if (valor == nodo->valor) {
    return true;
  } else if (valor < nodo->valor) {
    return buscar(valor, nodo->hijoIzquierdo);
  } else {
    return buscar(valor, nodo->hijoDerecho);
  }
}

/**
 * Elimina un valor específico del árbol B.
 * 
 * @param valor El valor a eliminar.
 * @param nodo El nodo actual en el recorrido del árbol.
 */
template <typename T>
void ArbolB<T>::eliminar(T valor, Nodo *nodo) {
  if (nodo == NULL) {
    return;
  }

  int i = 0;
  while (i < this->orden - 1 && valor > nodo->valor) {
    i++;
  }

  if (i < this->orden - 1) {
    eliminar(valor, nodo->hijoIzquierdo);
  } else {
    if (nodo->hijoIzquierdo != NULL && nodo->hijoIzquierdo->valor == valor) {
      eliminarNodo(nodo->hijoIzquierdo);
      nodo->hijoIzquierdo = NULL;
    } else {
      eliminar(valor, nodo->hijoDerecho);
    }
  }
}

/**
 * Imprime los valores de un árbol B en orden ascendente.
 * 
 * @param nodo Puntero al nodo raíz del árbol.
 * @tparam T Tipo de dato de los valores en el árbol.
 */
template <typename T>
void ArbolB<T>::imprimir(Nodo *nodo) {
  if (nodo == NULL) {
    return;
  }

  imprimir(nodo->hijoIzquierdo);
  cout << nodo->valor << endl;
  imprimir(nodo->hijoDerecho);
}