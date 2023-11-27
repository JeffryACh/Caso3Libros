#include "ArbolB.h"
ArbolB::ArbolB(int orden) {
  this->orden = orden;
  this->raiz = NULL;
} // Constructor


ArbolB::~ArbolB() {
  if (this->raiz != NULL) {
    eliminarNodo(this->raiz);
  }
} // Destructor

/**
 * Inserta un valor en el árbol B.
 * @param valor El valor a insertar.
 */

void ArbolB::insertar(PosicionPalabra valor) {
  insertar(valor, this->raiz);
}

/**
 * @brief Busca un valor en el árbol B.
 * 
 * @param valor El valor a buscar.
 * @return true si el valor se encuentra en el árbol, false en caso contrario.
 */

bool ArbolB::buscar(PosicionPalabra valor) {
  return buscar(valor, this->raiz);
}

/**
 * Elimina un valor específico del árbol B.
 * @param valor El valor a eliminar.
 * @tparam T El tipo de dato de los elementos del árbol.
 */

void ArbolB::eliminar(PosicionPalabra valor) {
  eliminar(valor, this->raiz);
}

/**
 * Imprime los elementos del árbol B.
 * @tparam T El tipo de dato de los elementos del árbol.
 */

void ArbolB::imprimir() {
  imprimir(this->raiz);
}

/**
 * Inserta un valor en el árbol B.
 * 
 * @param valor El valor a insertar.
 * @param nodo El nodo actual en el que se está realizando la inserción.
 * @tparam T El tipo de dato de los elementos del árbol.
 */

void ArbolB::insertar(PosicionPalabra valor, Nodo *nodo) {
  if (nodo == NULL) {
    Nodo *nuevoNodo = new Nodo();
    PosicionPalabra *pos = new PosicionPalabra();
    nuevoNodo->valor = 
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

  if (nodo->hijoIzquierdo != NULL && nodo->hijoIzquierdo->hijo > this->orden - 1) {
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

bool ArbolB::buscar(PosicionPalabra valor, Nodo *nodo) {
  if (nodo == NULL) {
    return false;
  }

  if (valor.getPalabra() == nodo->valor.getPalabra()) {
    return true;
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

void ArbolB::eliminar(PosicionPalabra valor, Nodo *nodo) {
  if (nodo == NULL) {
    return;
  }

  int i = 0;
  while (i < this->orden - 1 && valor.getPalabra() == nodo->valor.getPalabra()) {
    i++;
  }

  if (i < this->orden - 1) {
    eliminar(valor, nodo->hijoIzquierdo);
  } else {
    if (nodo->hijoIzquierdo != NULL && nodo->hijoIzquierdo->valor.getPalabra() == valor.getPalabra()) {
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

void ArbolB::imprimir(Nodo *nodo) {
  if (nodo == NULL) {
    return;
  }

  imprimir(nodo->hijoIzquierdo);
  cout << nodo->valor.getPalabra() << endl;
  imprimir(nodo->hijoDerecho);
}

void ArbolB::eliminarNodo(Nodo *nodo) {
  if (nodo == NULL) {
    eliminarNodo(nodo->hijoIzquierdo);
    eliminarNodo(nodo->hijoDerecho);
    delete nodo;
  }
}

Nodo* ArbolB::buscarRecursivo(Nodo* nodo, std::string palabra) {
  // Aquí va la lógica de búsqueda dentro de un nodo
  int i = 0;
  while (i < cantidadNodos(this->raiz) && palabra != nodo->valor.getPalabra()) {
      i++;
  }

  if (i < cantidadNodos(this->raiz) && palabra != nodo->valor.getPalabra()) {
      return nodo;  // Palabra encontrada
  }

  if (esHoja(nodo)) {
      return nullptr;  // Palabra no encontrada
  }

  return buscarRecursivo(nodo, palabra);
}

int ArbolB::cantidadNodos(Nodo *nodo) {
  return cantidadNodos(this->raiz);
}

int ArbolB::cantidadNodos(Nodo *nodo) {
  if (nodo == NULL) {
    return 0;
  }

  return 1 + cantidadNodos(nodo->hijoIzquierdo) + cantidadNodos(nodo->hijoDerecho);
}

bool ArbolB::esHoja(Nodo *nodo) {
  return nodo->hijoIzquierdo == NULL && nodo->hijoDerecho == NULL;
}