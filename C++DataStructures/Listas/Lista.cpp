#include <iostream>
#include <functional>
#include <cstdlib>
using namespace std;

template <typename Tipo>
struct Nodo{
  Tipo elemento;
  Nodo<Tipo>* siguiente;
  Nodo(Tipo e){elemento=e;siguiente=nullptr;}

};

template <typename Tipo>
class ListaSimple{
  public:
  Nodo<Tipo>* inicio;
  Nodo<Tipo>* fin;
  long cantidad;
public:
  ListaSimple(){
    inicio=fin=nullptr;
    cantidad=0;      
  }

  void insertar(Nodo<Tipo>* n){
  //para 0 elementos
  if(inicio==nullptr)
    inicio=n;
    //para 1--m elementos
  else{
    Nodo<Tipo>* aux=inicio;
    while(aux->siguiente!=nullptr)
       aux=aux->siguiente;
    aux->siguiente=n;
  }
}


void insertarInicio(Tipo e){
  Nodo<Tipo>* nuevo=new Nodo<Tipo>(e);
  if(nuevo!=nullptr){
    inicio=nuevo;
    cantidad++;
  }
}

void eliminarInicio(){
  if(cantidad>0){
    Nodo<Tipo>* aux=inicio;
    inicio=inicio->siguiente;
    delete aux;
    cantidad--;
  }
}


void eliminarPosicion(int pos){
  if (pos > cantidad)
    return;

  if (pos == 0)
    eliminarInicio();
  else{
    Nodo<Tipo>* aux = inicio;
    for (int i = 1; i < pos; i++)
      aux=aux->siguiente;
    Nodo<Tipo> *aux2 = aux->siguiente;
    aux->siguiente = aux->siguiente->siguiente;
    delete aux2;
    cantidad--;


  }
}


void reverseList(){
  if(cantidad<=1)
    return;
  else{
    fin = inicio;
    Nodo<Tipo> *current, *prev, *next;
    current = inicio;
    prev = NULL;
  
    while (current != NULL){

      next = current->siguiente;
      current->siguiente = prev;
      prev = current;
      current = next;
    }
  inicio = prev;
  }
}

Tipo recuperarPosicion(int pos){
  if (pos >= 0 && pos < cantidad){
    Nodo<Tipo> *aux = inicio;
    for (int i = 0; i < pos;i++)
      aux = aux->siguiente;
    return aux->elemento;
  }
  else
    return nullptr;
}


void insertar(Tipo e) {//O(1)
  Nodo<Tipo>* nuevo = new Nodo<Tipo>(e);
  if (inicio == nullptr) {
    inicio = fin = nuevo;
  } 
  else{
    fin->siguiente = nuevo;
    fin = nuevo;   
  }
  ++cantidad;
}


Tipo rotateList(int k){

  if(k<1)
    return inicio->elemento;

  Nodo<Tipo> *current = inicio;
  Nodo<Tipo> *kNode = nullptr;
  for (int i = 1; i < k && current != nullptr; i++)
    current = current->siguiente;

  if(current==nullptr)
    return nullptr;

  kNode = current;
  current = fin;
  fin = kNode;
  current->siguiente = inicio;
  inicio = kNode->siguiente;
  kNode->siguiente = nullptr;
  return inicio->elemento;
}


void mostrar(function<void(Tipo)>funMostrar){
  Nodo<Tipo>* aux=inicio;
  while(aux->siguiente!=nullptr){
  //cout<<aux->elemento<<" ";
    funMostrar(aux->elemento);
    aux=aux->siguiente;
  }
  funMostrar(aux->elemento);
}

};

class Virus{
  string nombre;
  short idx;
  int edad;

public:
  Virus(string nombre,short idx):nombre(nombre),idx(idx){}
  string getNombre(){return nombre;}
  string toString(){return nombre+" "+to_string(idx)+"\n";}
};

void ejemplo1(){

  ListaSimple<int> ls;

   /* ls.insertar(new Nodo<int>(15));
    ls.insertar(new Nodo<int>(25));
    ls.insertar(new Nodo<int>(35));
    ls.insertar(new Nodo<int>(45));
    ls.insertar(new Nodo<int>(55));
    ls.insertar(15);
    ls.insertar(25);
    ls.insertar(35);
    ls.insertar(45);
    ls.insertar(55);*/
  ls.mostrar([](int v){cout<<v<<" ";});

}

void ejemplo2(){
  ListaSimple<Virus*> ls;   
  ls.insertar(new Virus("Covid",1));
  ls.insertar(new Virus("Influenza",2));
  ls.insertar(new Virus("Colera",3));
  ls.insertar(new Virus("Helix", 4));
  ls.mostrar([](Virus*v){cout<<v->toString()<<" ";});
  /*ls.reverseList();
  cout << "Reversed List:";
  ls.mostrar([](Virus*v){cout<<v->toString()<<" ";});
  cout << "Fin: " << ls.fin->elemento->toString();
  cout << "Inicio: " << ls.inicio->elemento->toString();*/
  cout << "Rotated List: " << endl;
  ls.rotateList(1);
  ls.mostrar([](Virus*v){cout<<v->toString()<<" ";});
  cout << "Fin: " << ls.fin->elemento->toString();
  cout << "Inicio: " << ls.inicio->elemento->toString();
  cout<<ls.cantidad<<endl;

}

int main(){

  ejemplo2();

}
