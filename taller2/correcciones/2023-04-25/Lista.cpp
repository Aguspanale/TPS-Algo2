#include "Lista.h"
#include <cassert>

Lista::Lista():_inicio(nullptr),_final(nullptr),_longitud(0) {
    // Completar
}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    Nodo * actual = _inicio;
    _final = nullptr;
    _inicio = nullptr;
    if(_longitud != 0){
        while(actual->siguiente != nullptr){
            actual = actual->siguiente;
            delete actual->anterior;
        }
        delete actual;
    }
    _longitud = 0;
}

Lista& Lista::operator=(const Lista& aCopiar) {
    Nodo * actual = _inicio;                        //hago lo mismo que en el destructor para borrar la lista si existe.
    _final = nullptr;
    _inicio = nullptr;
    if(_longitud != 0){
        while(actual->siguiente != nullptr){
            actual = actual->siguiente;
            delete actual->anterior;
        }
        delete actual;
    }
    _longitud = 0;                                  //despues genero una lista igual a aCopiar
    actual = aCopiar._inicio;
    if(aCopiar._longitud != 0){
        while(actual->siguiente != nullptr){
            agregarAtras(actual->valor);
            actual = actual->siguiente;
        }
        agregarAtras(actual->valor);
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo * nuevo = new Nodo(nullptr,elem,_inicio);
    if(_longitud != 0){
        _inicio->anterior = nuevo;
        _inicio = nuevo;
    } else {
        _inicio = nuevo;
        _final = nuevo;
    }
   _longitud++;
}

void Lista::agregarAtras(const int& elem) {
    Nodo * nuevo = new Nodo(_final,elem, nullptr);
    if(_longitud != 0){
        _final->siguiente = nuevo;
        _final = nuevo;
    } else {
        _inicio = nuevo;
        _final = nuevo;
    }
    _longitud++;
}

void Lista::eliminar(Nat i) {
    Nodo * actual = _inicio;
    for (; i > 0; --i) {
        actual = actual->siguiente;
    }
    if(actual->siguiente != nullptr){
        actual->siguiente->anterior = actual->anterior;
    } else {
        _final = actual->anterior;
    }
    if(actual->anterior != nullptr){
        actual->anterior->siguiente = actual->siguiente;
    } else {
        _inicio = actual->siguiente;
    }
    delete actual;
    _longitud--;
}

int Lista::longitud() const {
    // Completar
    return _longitud;
}

const int& Lista::iesimo(Nat i) const {
    assert(i < _longitud);
    Nodo* actual = _inicio;
    for (; i > 0; --i){
        actual = actual->siguiente ;
    }
    return actual->valor;
}

int& Lista::iesimo(Nat i) {
    assert(i < _longitud);
    Nodo* actual = _inicio;
    for (; i > 0; --i){
        actual = actual->siguiente ;
    }
    return actual->valor;
}

void Lista::mostrar(ostream& o) {
    // Completar
}
