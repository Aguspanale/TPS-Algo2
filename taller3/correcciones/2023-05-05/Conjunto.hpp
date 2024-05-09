
template <class T>
Conjunto<T>::Conjunto():_cardinal(0),_raiz(nullptr){
}

template <class T>
Conjunto<T>::~Conjunto() {
    if(_raiz != nullptr){
        _raiz -> borrarDescendencia();
        delete _raiz;
        _raiz = nullptr;
    }

}
template<class T>
void Conjunto<T>::Nodo::borrarDescendencia() {
    if(der != nullptr){
        der->borrarDescendencia();
        delete der;
    }
    if(izq != nullptr){
        izq->borrarDescendencia();
        delete izq;
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* actual = _raiz;
    while(actual != nullptr){
        if(actual -> valor == clave){
            return true;
        } else if ( actual -> valor < clave){
            actual = actual ->der;
        } else {
            actual = actual ->izq;
        }
    }
    return false;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if(_raiz == nullptr){
        _raiz = new Nodo(clave, nullptr, nullptr);
        _cardinal++;
    } else {
        Nodo* actual = _raiz;
        Nodo* anterior;
        while(actual != nullptr){
            if(actual -> valor == clave){
                anterior = actual;
                actual = nullptr;
            } else if ( actual -> valor < clave){
                anterior = actual;
                actual = actual ->der;
            } else {
                anterior = actual;
                actual = actual ->izq;
            }
        }
        if(anterior -> valor < clave){
            anterior -> der = new Nodo(clave, nullptr, nullptr);
            _cardinal++;
        } else if (anterior -> valor > clave){
            anterior -> izq = new Nodo(clave, nullptr, nullptr);
            _cardinal++;
        }
    }
}


template <class T>
void Conjunto<T>::remover(const T& clave) {
    if(_raiz != nullptr) {
        if(_raiz->valor == clave){ // 3 casos, nodo solo, nodo con 1 hoja y nodo con 2 hojas
            if(_raiz->der == nullptr && _raiz->izq == nullptr){
                delete _raiz;
                _raiz = nullptr;
                _cardinal--;
            } else if(_raiz->der == nullptr) { // si tiene solo rama izq
                Nodo* aBorrar = _raiz;
                _raiz = _raiz->izq;
                delete aBorrar;
                _cardinal--;
            }  else if(_raiz->der == nullptr) { // si tiene solo rama der
                Nodo* aBorrar = _raiz;
                _raiz = _raiz->izq;
                delete aBorrar;
                _cardinal--;
            } else { // si tiene 2 hijos :(
                T minimoADerecha = _raiz->der->minimo();
                remover(minimoADerecha); // si tengo tiempo hago que esto aproveche que ya se donde esta y lo optimizo mas
                _raiz -> valor = minimoADerecha;
            }


        } else {
            Nodo *actual = _raiz;
            Nodo *anterior = _raiz;
            bool actualADerecha = false; // true si el nodo anterior apunta al nodo actual en su rama derecha, false si no
            while (actual != nullptr && actual -> valor != clave) {
                if (actual->valor < clave) {
                    anterior = actual;
                    actual = actual->der;
                    actualADerecha = true;
                } else {
                    anterior = actual;
                    actual = actual->izq;
                    actualADerecha = false;
                }
            }
            if(actual != nullptr){ // osea salio del while porque valor = clave, hay casos, hoja, 1 hijo o 2 hijos
                if(actual -> der == nullptr && actual -> izq == nullptr){ // si es hoja :)
                    if(actualADerecha){

                        anterior -> der = nullptr;
                        delete actual;
                        _cardinal--;
                    } else{

                        anterior -> izq = nullptr;
                        delete actual;
                        _cardinal--;
                    }
                } else if (actual -> der == nullptr){ // si solo tiene hijo izquierdo :|
                    if(actualADerecha){

                        anterior -> der = actual -> izq;
                        delete actual;
                        _cardinal--;
                    } else{

                        anterior -> izq = actual -> izq;
                        delete actual;
                        _cardinal--;
                    }
                } else if (actual -> izq == nullptr){ // si solo tiene hijo derecho :|
                    if(actualADerecha){
                        anterior -> der = actual -> der;
                        delete actual;
                        _cardinal--;
                    } else{
                        anterior -> izq = actual -> der;
                        delete actual;
                        _cardinal--;
                    }
                } else { // si tiene 2 hijos :(
                    T minimoADerecha = actual->der->minimo();
                    remover(minimoADerecha); // si tengo tiempo hago que esto aproveche que ya se donde esta y lo optimizo mas
                    actual -> valor = minimoADerecha;
                }
            }
        }
    }
}
template <class T>
const T& Conjunto<T>::Nodo::minimo() {
    if(izq == nullptr){
        return valor;
    } else {
        Nodo * actual = izq;
        while(actual->izq != nullptr){
            actual = actual -> izq;
        }
        return actual->valor;
    }
}
template <class T>
const T& Conjunto<T>::Nodo::maximo() {
    if(der == nullptr){
        return valor;
    } else {
        Nodo * actual = der;
        while(actual->der != nullptr){
            actual = actual -> der;
        }
        return actual->valor;
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    assert(pertenece(clave));
    Nodo* actual = _raiz;
    Nodo* posibleSiguiente;
    while(true){ // pre:pertenece
        if(actual -> valor == clave){
            if(actual->der != nullptr){
                return actual->der->minimo();
            } else {
                break;
            }

        } else if ( actual -> valor < clave){
            actual = actual ->der;
        } else {
            posibleSiguiente = actual;
            actual = actual ->izq;
        }
    }
    return posibleSiguiente->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    assert(_raiz != nullptr);
    return _raiz->minimo();
}

template <class T>
const T& Conjunto<T>::maximo() const {
    assert(_raiz != nullptr);
    return _raiz->maximo();
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _cardinal;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

