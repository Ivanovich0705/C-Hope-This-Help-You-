#include <iostream>
#include <functional>
#include <cstdlib>
using namespace std;

template <typename Tipo>
struct Nodo{
  Tipo elemento;
  Nodo<Tipo>* siguiente;
  Nodo<Tipo> *anterior;
  Nodo(Tipo e){elemento=e;siguiente = anterior = nullptr;}
};

template <typename Tipo>
class Cola{
public:
  Nodo<Tipo>* inicio;
  Nodo<Tipo>* fin;
  long cantidad;
public:
  Cola(){
    inicio = fin = nullptr;
    cantidad = 0;
  }


void push(Tipo e) {//O(1)
  Nodo<Tipo>* nuevo = new Nodo<Tipo>(e);
  if (inicio == nullptr) {
    inicio = fin = nuevo;
  } 
  else{
    nuevo->anterior = fin;
    fin->siguiente = nuevo;
    fin = nuevo;   
  }
  ++cantidad;
}

void front(function<void(Tipo)>funFront){
  funFront(inicio->elemento);
}

void pop(){
    if(cantidad==0)
        return;
        else if(cantidad==1){
            delete inicio;
            inicio = fin = nullptr;
        }
        else{
            Nodo<Tipo> *aux = inicio;
            inicio = aux->siguiente;
            inicio->anterior = nullptr;
            delete aux;
        }
        cantidad--;
}

Tipo front(){
  if(inicio!=nullptr)
    return inicio->elemento;
}

int size(){
  short c=0;
  Nodo<Tipo>* aux=inicio;
  while(aux!=nullptr){
    c++;
    aux=aux->siguiente;
  }

  return c;
}

};

class Virus{
  string nombre;
  short idx;
  public:
  Virus(string nombre,short idx):nombre(nombre),idx(idx){}
  string getNombre(){return nombre;}
  string toString(){return nombre+" "+to_string(idx)+"\n";}
};


void ejemplo2(){

  Cola<Virus*> ls;   
  ls.push(new Virus("Covid",1));
  ls.push(new Virus("Influenza",2));
  ls.push(new Virus("Colera",3));
  ls.push(new Virus("Helix", 4));
  ls.front([](Virus*v){cout<<v->toString()<<" ";});
  cout<<ls.size()<<endl;
  ls.pop();
  ls.front([](Virus*v){cout<<v->toString()<<" ";});
  cout<<ls.size()<<endl;
}

int main(){

  ejemplo2();

}