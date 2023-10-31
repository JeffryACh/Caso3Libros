#include "arbolAVL.h"

// **********************************************
// *	   ARBOL AVL de Libros                  *
// **********************************************

/**
 * @brief Destructor de la clase AVL_Principal que destruye el árbol AVL.
 * 
 */
AVL_Principal::~AVL_Principal() {
    destruirArbol(&(this->raiz));
}

void AVL_Principal::destruirArbol(AVL_Libros** raiz) {
    if (*raiz) {
        destruirArbol(&((*raiz)->Hizq));
        destruirArbol(&((*raiz)->Hder));
        delete* raiz;
        *raiz = NULL; // Asigna a NULL después de eliminar el nodo
    }
}

AVL_Libros* AVL_Principal::buscarLibro(AVL_Libros* raiz, string titulo) {
    if (!raiz)
        return nullptr;
    else if (raiz->titulo == titulo)
        return raiz;
    else {
        if (titulo < raiz->titulo)
            return buscarLibro(raiz->Hizq, titulo);
        else
            return buscarLibro(raiz->Hder, titulo);
    }
}

void AVL_Principal::insertarNodo(string libro, string titulo, string autor) {
    InsertarBalanceado(&(this->raiz), &(this->Hh), libro, titulo,autor);
}

/**
 * Inserta un nuevo nodo en el árbol AVL de manera balanceada.
 * @param ra Puntero al puntero de la raíz del árbol.
 * @param Hh Puntero a una variable booleana que indica si hubo un cambio de altura en el árbol.
 * @param libro Cadena de caracteres que representa el identificador del libro a insertar.
 * @param titulo Cadena de caracteres que representa el título del libro a insertar.
 * @param autor Cadena de caracteres que representa el autor del libro a insertar.
 */
/**
 * Inserta un nuevo nodo en el árbol AVL de manera balanceada.
 * @param ra Puntero doble a la raíz del árbol AVL.
 * @param Hh Puntero a un booleano que indica si hubo un cambio en la altura del árbol.
 * @param libro Cadena de caracteres que representa el código del libro a insertar.
 * @param titulo Cadena de caracteres que representa el título del libro a insertar.
 * @param autor Cadena de caracteres que representa el autor del libro a insertar.
 */
void AVL_Principal::InsertarBalanceado(AVL_Libros** ra, bool* Hh, string libro, string titulo, string autor ) {
    AVL_Libros* n1;

    if (*ra == NULL) {
        *ra = new AVL_Libros(libro, titulo,autor);
        *Hh = true;
    }
    else {
        if (libro < (*ra)->libro) {
            InsertarBalanceado(&((*ra)->Hizq), Hh, libro, titulo,autor);

            if (Hh) {
                switch ((*ra)->FB) {
                    case 1:
                        (*ra)->FB = 0;
                        *Hh = false;
                        break;

                    case 0:
                        (*ra)->FB = -1;
                        break;

                    case -1:
                        n1 = (*ra)->Hizq;
                        if (n1->FB == -1)
                            RotacionSimpleIzquierda(ra, n1);
                        else
                            RotacionDobleIzquierda(ra, n1);

                        *Hh = false;
                        break;
                }
            }
        }
        else if (libro > (*ra)->libro) {
            InsertarBalanceado(&((*ra)->Hder), Hh, libro, titulo,autor);

            if (Hh) {
                switch ((*ra)->FB) {
                    case -1:
                        (*ra)->FB = 0;
                        *Hh = false;
                        break;

                    case 0:
                        (*ra)->FB = 1;
                        break;

                    case 1:
                        n1 = (*ra)->Hder;
                        if (n1->FB == 1)
                            RotacionSimpleDerecha(ra, n1);
                        else
                            RotacionDobleDerecha(ra, n1);

                        *Hh = false;
                        break;
                }
            }
        }
        else {
            *Hh = false;
            return;
        }
    }
}

/**
 * Realiza una rotación doble a la izquierda en un árbol AVL.
 * @param n Puntero al puntero de la raíz del árbol AVL.
 * @param n1 Puntero al nodo que se encuentra desbalanceado.
 */
void AVL_Principal::RotacionDobleIzquierda(AVL_Libros** n, AVL_Libros* n1) {
    AVL_Libros* n2;
    n2 = n1->Hder;
    (*n)->Hizq = n2->Hder;
    n2->Hder = (*n);
    n1->Hder = n2->Hizq;
    n2->Hizq = n1;

    if (n2->FB == 1)
        n1->FB = -1;
    else
        n1->FB = 0;

    if (n2->FB == -1)
        (*n)->FB = 1;
    else
        (*n)->FB = 0;

    n2->FB = 0;
    (*n) = n2;
}

/**
 * Realiza una rotación doble a la derecha en un árbol AVL.
 * @param n Puntero al puntero de la raíz del árbol AVL.
 * @param n1 Puntero al nodo que se encuentra en la posición del desbalanceo.
 */
void AVL_Principal::RotacionDobleDerecha(AVL_Libros** n, AVL_Libros* n1) {
    AVL_Libros* n2;
    n2 = n1->Hizq;
    (*n)->Hder = n2->Hizq;
    n2->Hizq = (*n);
    n1->Hizq = n2->Hder;
    n2->Hder = n1;

    if (n2->FB == 1)
        (*n)->FB = -1;
    else
        (*n)->FB = 0;

    if (n2->FB == -1)
        n1->FB = 1;
    else
        n1->FB = 0;

    n2->FB = 0;
    (*n) = n2;
}

/**
 * Realiza una rotación simple a la derecha en un árbol AVL.
 * @param n Puntero doble al nodo raíz del árbol.
 * @param n1 Puntero al nodo que será la nueva raíz del subárbol.
 */
void AVL_Principal::RotacionSimpleDerecha(AVL_Libros** n, AVL_Libros* n1) {
    (*n)->Hder = n1->Hizq;
    n1->Hizq = (*n);

    if (n1->FB == 1) {
        (*n)->FB = 0;
        n1->FB = 0;
    }
    else {
        (*n)->FB = 1;
        n1->FB = -1;
    }
    (*n) = n1;
}

/**
 * Realiza una rotación simple a la izquierda en un árbol AVL.
 * @param n Puntero doble al nodo raíz del subárbol a rotar.
 * @param n1 Puntero al nodo que será la nueva raíz del subárbol rotado.
 */
void AVL_Principal::RotacionSimpleIzquierda(AVL_Libros** n, AVL_Libros* n1) {
    (*n)->Hizq = n1->Hder;
    n1->Hder = (*n);

    if (n1->FB == -1) {
        (*n)->FB = 0;
        n1->FB = 0;
    }
    else {
        (*n)->FB = -1;
        n1->FB = -1;
    }
    (*n) = n1;
}

/**
 * @brief Inserta un libro en el árbol AVL por su título.
 * 
 * @param titulo El título del libro a insertar.
 */
void insertarPorTitulo(const std::string& titulo) {
    InsertarBalanceado(&(this->raiz), &(this->Hh), libro, titulo, autor);
}