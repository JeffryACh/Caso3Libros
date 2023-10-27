#include "arbolAVL.h"

// **********************************************
// *	   ARBOL AVL de Libros                  *
// **********************************************

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
