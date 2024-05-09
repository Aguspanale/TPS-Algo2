#include <iostream>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
  public:
    Fecha(int mes, int dia);
    int mes();
    int dia();
    #if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
    #endif
    void incrementar_dia();

  private:
    int mes_;
    int dia_;
};

Fecha::Fecha(int mes, int dia): mes_(mes),dia_(dia){}

int Fecha::mes(){
    return mes_;
}
int Fecha::dia(){
    return dia_;
}



ostream& operator<<(ostream& os, Fecha F){
    os << F.dia() << "/" << F.mes();
    return os;
}




#if EJ >= 9

bool Fecha::operator==(Fecha o){
    return dia_ == o.dia_ && mes_ == o.mes_;
}



/*bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia();
    // Completar igualdad (ej 9)
    return igual_dia;
} */

#endif
void Fecha::incrementar_dia() {
    if(dia_ < dias_en_mes(mes_)){
        dia_++;
    } else {dia_ = 1;mes_++;}
}
// Ejercicio 11, 12

class Horario {
public:
    Horario(uint hora, uint min);
    uint hora();
    uint min();
    bool operator==(Horario otro);
    bool operator<(Horario otro);
private:
    uint hora_;
    uint min_;
};
Horario::Horario(uint hora, uint min): hora_(hora),min_(min){}

uint Horario::hora(){
    return hora_;
}
uint Horario::min(){
    return min_;
}

bool Horario::operator==(Horario otro){
    return hora_== otro.hora_ && min_ == otro.min_;
}

ostream& operator<<(ostream& os, Horario h){
    os << h.hora() << ":" << h.min();
    return os;
}

bool Horario::operator<(Horario otro){
    if (hora_ == otro.hora_){
        return min_ < otro.min_;
    } else {return hora_ < otro.hora_;}
}



// Ejercicio 13

typedef string Mensaje;


class Recordatorio {
    public:
        Recordatorio(Fecha f, Horario h, Mensaje m);
        Fecha fecha();
        Horario horario();
        Mensaje mensaje();
    private:
        Fecha fecha_;
        Horario horario_;
        Mensaje mensaje_;
};

Recordatorio::Recordatorio(Fecha f, Horario h, Mensaje m): fecha_(f), horario_(h), mensaje_(m) {}

Fecha Recordatorio::fecha() {
    return fecha_;
}

Horario Recordatorio::horario() {
    return horario_;
}

Mensaje Recordatorio::mensaje() {
    return mensaje_;
}

ostream& operator<<(ostream& os, Recordatorio r){
    os << r.mensaje() << " @ " << r.fecha() << " " << r.horario();
    return os;
}

// Ejercicio 14
#include <list>
class Agenda {
public:
    Agenda(Fecha fecha_i);
    void agregar_recordatorio(Recordatorio rec);
    void incrementar_dia();
    list<Recordatorio> recordatorios_de_hoy();
    Fecha hoy();
private:
    Fecha fecha_;
    list<Recordatorio> recordatorios_;
};

Agenda::Agenda(Fecha fecha_i):fecha_(fecha_i),recordatorios_() {}

void Agenda::agregar_recordatorio(Recordatorio rec){
    if(recordatorios_.empty()){
        recordatorios_.push_back(rec);
    }
    else {
        list<Recordatorio>::iterator it;
        for (it = recordatorios_.begin(); it != recordatorios_.end() ; advance(it,1)) {  // it == puntero
            Recordatorio recordatorioActual = *it;                                              // *it elemento de la lista al que apunta el puntero
            if(!(recordatorioActual.horario() < rec.horario())){
                recordatorios_.insert(it,1,rec);
                break;
            }
        } if(it == recordatorios_.end()){recordatorios_.push_back(rec);}
    }
}

void Agenda::incrementar_dia(){
    fecha_.incrementar_dia();
}

list<Recordatorio> Agenda::recordatorios_de_hoy() {
    list<Recordatorio> res;
    for(Recordatorio r : recordatorios_){
        if(r.fecha() == fecha_){
            res.push_back(r);
        }
    }
    return res;
}

Fecha Agenda::hoy(){
    return fecha_;
}

ostream& operator<<(ostream& os, Agenda a){
    os << a.hoy() << endl << "=====" << endl;
    for(Recordatorio r : a.recordatorios_de_hoy()){
        os << r << endl;
    }
    return os;
}

