template <typename T>
string_map<T>::string_map():_raiz(),_size(0){
    _raiz = new Nodo();
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& aCopiar) {
    vector<string> aBorrar = _raiz->stringsADefinir(string());
    for(string s : aBorrar){
        erase(s);
    } //despues de borrar todos::
    vector<string> aDefinir;
    aDefinir = aCopiar._raiz->stringsADefinir(string());
    for(string cl : aDefinir){
            insert(make_pair(cl,aCopiar.at(cl)));
    }
    return *this;
}

template <typename T>
vector<string> string_map<T>::Nodo::stringsADefinir(string s){ // divide and conquer, primero me  consigo los strings (claves)
    vector<string> strings;
    for (int i = 0; i < 256 ; ++i) {

        if(siguientes[i] != nullptr){
            if(siguientes[i]->definicion != nullptr){
                string claveActual = s;
                claveActual.push_back(char(i));
                strings.push_back(claveActual);
            }
            string claveActual = s;
            claveActual.push_back(char(i));
            strings = concatenar(strings, siguientes[i]->stringsADefinir(claveActual));
        }
    }
    return strings;
}



template <typename T>
string_map<T>::~string_map(){
    vector<string> aBorrar = _raiz->stringsADefinir(string());
    for(string s : aBorrar){
        erase(s);
    }
    delete _raiz;
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& p){
    Nodo* actual = _raiz;
    string clave = p.first;
    for (char c : clave) {
        if(actual->siguientes[int(c)] == nullptr){
            actual->siguientes[int(c)] = new Nodo();
        }
        actual = actual->siguientes[int(c)];
    }
    if(actual->definicion == nullptr){
        actual->definicion = new T;
        _size++;
    }
    *(actual->definicion) = p.second;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){

}


template <typename T>
int string_map<T>::count(const string& clave) const{
    Nodo* actual = _raiz;
    for (char c : clave) {
        if(actual->siguientes[int(c)] == nullptr){
            return 0;
        }
        actual = actual->siguientes[int(c)];
    }
    if(actual->definicion == nullptr){return 0;}
    return 1;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* actual = _raiz;
    for (char c : clave) {
        actual = actual->siguientes[int(c)];
    }
    return *(actual->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* actual = _raiz;
    for (char c : clave) {
        actual = actual->siguientes[int(c)];
    }
    return *(actual->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* actual = _raiz;
    char ultimoChar = clave[0];
    vector<Nodo*> aBorrar; // vector que tiene la cadena de posibles nodos a borrar, comenzando por el que si se borraran apuntaria a nulo (ese no se borra a menos que sea la raiz)
    for (char c : clave) {
        if(esDeNulosMenos(actual->siguientes, int(c)) && actual->definicion == nullptr){
            aBorrar.push_back(actual);
        } else {
            aBorrar.clear();
            aBorrar.push_back(actual);
            ultimoChar = c;
        }
        actual = actual->siguientes[int(c)];
    }
    delete actual->definicion;
    actual->definicion = nullptr;
    if(esDeNulosMenos(actual->siguientes, -1)){ // -1 para decir es de nulos, pues no es un indice valido
        delete actual;
    } else {
        aBorrar.clear();
        return;
    }
    borrarTodosMenosPrimero(aBorrar);
    aBorrar[0]->siguientes[int(ultimoChar)] = nullptr;

}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    for(Nodo* p : _raiz->siguientes){
        if(p != nullptr){
            return false;
        }
    }
    return true;
}
template <typename T>
bool esDeNulosMenos(T* v[],int n){
    for (int i = 0; i < 256; ++i) {
        if(v[i] != nullptr && i != n){
            return false;
        }
    }
    return true;
}
template <typename T>
void borrarTodosMenosPrimero(vector<T*> v){
    for (int i = 1; i < v.size(); ++i) {
        delete v[i];
    }
}