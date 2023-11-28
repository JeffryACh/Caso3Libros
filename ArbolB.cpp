/**
 * @file ArbolB.cpp
 * 
 * @brief Implementación de la clase ArbolB.
 * 
 * @author Jeffry Araya Ch
 *
 * @date 28/11/2023 14:00 
*/

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
 * @brief Inserta un valor en el árbol B.
 * 
 * @param valor El valor a insertar.
 */
void ArbolB::insertar(string palabra) {
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
 * @brief Elimina un valor del árbol B.
 * 
 * @param valor El valor a eliminar.
 */
void ArbolB::eliminar(PosicionPalabra valor) {
  eliminar(valor, this->raiz);
}

/**
 * Imprime los valores del árbol B.
 */
void ArbolB::imprimir() {
  imprimir(this->raiz);
}

/**
 * @brief Inserta un valor en el árbol B.
 * 
 * @param valor Valor a insertar en el árbol.
 * @param nodo Nodo actual en la búsqueda.
 */
void ArbolB::insertar(string palabra, Nodo *nodo) {
  if (nodo == NULL) {
    Nodo *nuevoNodo = new Nodo();
    pair<string, vector<PosicionPalabra>> *mapa = new pair<string, vector<PosicionPalabra>>();
    mapa->first = palabra;
    mapa->second = indexador.indexarPalabra(palabra);
    nuevoNodo->hijoIzquierdo = NULL;
    nuevoNodo->hijoDerecho = NULL;
    nuevoNodo->hijo = 0;
    nuevoNodo->hijos = nullptr;
    nuevoNodo->valor = mapa;
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
    nuevoNodo->hijo = nodo->hijo + 1;
    nodo->hijoIzquierdo = nuevoNodo;
  }

  if (nodo->hijoIzquierdo != NULL && nodo->hijoIzquierdo->hijo > this->orden - 1) {
    desbalancear(nodo, true);
  }
}

/**
 * @brief Busca un valor en el árbol B.
 * 
 * @param valor Valor a buscar en el árbol.
 * @param nodo Nodo actual en la búsqueda.
 * @return true si el valor se encuentra en el árbol, false en caso contrario.
 */
bool ArbolB:: buscar(PosicionPalabra valor, Nodo *nodo) {
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
 * @brief Elimina un valor específico del árbol B.
 * 
 * @param valor Valor a eliminar del árbol.
 * @param nodo Nodo actual en la búsqueda.
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
 * @brief Imprime los valores del árbol B.
 * 
 * @param nodo Nodo actual en el recorrido del árbol.
 */
void ArbolB::imprimir(Nodo *nodo) {
  if (nodo == NULL) {
    return;
  }

  imprimir(nodo->hijoIzquierdo);
  cout << nodo->valor.first() << endl;
  imprimir(nodo->hijoDerecho);
}

/**
 * @brief Elimina un nodo del árbol B.
 * 
 * @param nodo Nodo a eliminar.
 */
void ArbolB::eliminarNodo(Nodo *nodo) {
  if (nodo == NULL) {
    eliminarNodo(nodo->hijoIzquierdo);
    eliminarNodo(nodo->hijoDerecho);
    delete nodo;
  }
}

/**
 * @brief Busca un valor en el árbol B.
 * 
 * @param valor Valor a buscar en el árbol.
 * @return el nodo que contiene el valor buscado, nullptr en caso de no encontrarlo.
*/
Nodo* ArbolB::buscarRecursivo(string palabra) {
  return buscarRecursivo(palabra, this->raiz);
}

/**
 * @brief Busca un valor en el árbol B.
 * 
 * @param valor Valor a buscar en el árbol.
 * @param nodo Nodo actual en la búsqueda.
 * @return el nodo que contiene el valor buscado, nullptr en caso de no encontrarlo.
*/
Nodo* ArbolB::buscarRecursivo(string palabra, Nodo* nodo) {
  // Aquí va la lógica de búsqueda dentro de un nodo
  int i = 0;
  while (i < nodo->hijo && palabra > nodo->valor.begin()->first()) { // Revisar si es menor o mayor
    i++;
  }

  if (i < nodo->hijo && palabra == nodo->valor.begin()->first()) {
    return nodo;  // Palabra encontrada
  }

  if (esHoja(nodo)) {
    return nullptr;  // Palabra no encontrada
  }

  return buscarRecursivo(nodo->hijos[i], palabra); // Palabra no encontrada, buscar en el hijo correspondiente

}

/**
 * @brief Calcula la cantidad de nodos en el árbol.
 * 
 * @return La cantidad de nodos en el árbol.
*/
int ArbolB::cantidadNodos() {
  return cantidadNodos(this->raiz);
}

/**
 * @brief Calcula la cantidad de nodos en el árbol.
 * 
 * @param nodo Nodo actual en el recorrido del árbol.
 * @return La cantidad de nodos en el árbol.
*/
int ArbolB::cantidadNodos(Nodo *nodo) {
  if (nodo == NULL) {
    return 0;
  }

  return 1 + cantidadNodos(nodo->hijoIzquierdo) + cantidadNodos(nodo->hijoDerecho);
}
/**
 * @brief Determina si un nodo es hoja.
 * 
 * @param nodo Nodo a evaluar.
*/
bool ArbolB::esHoja(Nodo *nodo) {
  return nodo->hijoIzquierdo == NULL && nodo->hijoDerecho == NULL;
}

/**
 * @brief Desbalancea un nodo.
 * 
 * @param nodo Nodo a desbalancear.
 * @param esHijoIzquierdo true si el nodo a desbalancear es hijo izquierdo, false en caso contrario.
*/
void ArbolB::desbalancear(Nodo *nodo, bool esHijoIzquierdo) {
  if (nodo == NULL) {
    cout << "No se puede desbalancear un nodo nulo" << endl;
    return;
  }

  if (esHijoIzquierdo) {
    if (nodo->hijoIzquierdo->hijo > this->orden - 1) {
      Nodo *nuevoNodo = new Nodo();
      nuevoNodo->valor = nodo->valor;
      nuevoNodo->hijoIzquierdo = nodo->hijoIzquierdo->hijoIzquierdo;
      nuevoNodo->hijoDerecho = nodo->hijoIzquierdo->hijoDerecho;
      nodo->valor = nodo->hijoIzquierdo->valor;
      nodo->hijoIzquierdo = nuevoNodo;
      nodo->hijoDerecho = nodo->hijoIzquierdo->hijoDerecho;
      nodo->hijoIzquierdo->hijoDerecho = nodo->hijoIzquierdo->hijoIzquierdo;
      nodo->hijoIzquierdo->hijoIzquierdo = nodo->hijoIzquierdo->hijoIzquierdo;
    } else { // Desbalancear el hijo izquierdo
      desbalancear(nodo->hijoIzquierdo, true);
    }
  } else {
    if (nodo->hijoDerecho->hijo > this->orden - 1) {
      Nodo *nuevoNodo = new Nodo();
      nuevoNodo->valor = nodo->valor;
      nuevoNodo->hijoIzquierdo = nodo->hijoDerecho->hijoIzquierdo;
      nuevoNodo->hijoDerecho = nodo->hijoDerecho->hijoDerecho;
      nodo->valor = nodo->hijoDerecho->valor;
      nodo->hijoIzquierdo = nodo->hijoDerecho->hijoIzquierdo;
      nodo->hijoDerecho = nuevoNodo;
      nodo->hijoDerecho->hijoDerecho = nodo->hijoDerecho->hijoDerecho;
      nodo->hijoDerecho->hijoIzquierdo = nodo->hijoDerecho->hijoIzquierdo;
    } else { // Desbalancear el hijo derecho
      desbalancear(nodo->hijoDerecho, false);
    }
  }
}