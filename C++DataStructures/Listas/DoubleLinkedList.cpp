#include <iostream>
#include <functional>
#include <cstdlib>
using namespace std;

template <typename Tipo>
struct Nodo{
  Tipo elemento;
  Nodo<Tipo>* siguiente;
  Nodo<Tipo> *anterior;
  Nodo(Tipo e){elemento=e; siguiente = anterior = nullptr;}
};     

template <typename Tipo>
class ListaDoble{
  public:
  Nodo<Tipo>* inicio;
  Nodo<Tipo>* fin;
  long cantidad;
public:
  ListaDoble(){
      inicio = fin = nullptr;
      cantidad = 0;      
  }

void insertarInicio(Tipo e){
    Nodo<Tipo> *nuevo = new Nodo<Tipo>(e);
    if(inicio==nullptr)
        inicio = fin = nuevo;
    else{
        inicio->anterior = nuevo;
        nuevo->siguiente = inicio;
    }
    inicio = nuevo;
    inicio->anterior = nullptr;
    cantidad++;
}


//HECHO POR XIOMARA PICON
void eliminarInicio(){
  if(cantidad > 0){
    Nodo<Tipo>* aux=inicio;
    inicio=inicio->siguiente;
    inicio->anterior = nullptr;

    delete aux;
    cantidad--;
  }
}


//HECHO POR XIOMARA PICON
void eliminarPosicion(int pos){
  if (pos > cantidad)
    return;

  if (pos == 0)
    eliminarInicio();
  else{
    Nodo<Tipo>* aux = inicio;
    for (int i = 1; i < pos; i++)
      aux=aux->siguiente;
    aux->siguiente->siguiente->anterior = aux;
    aux->siguiente = aux->siguiente->siguiente;
    delete aux;
    cantidad--;


  }
}


//HECHO POR IVAN MORAN
void reverseList(){
  if(cantidad<=1)
    return;
  else{
    fin = inicio;
    Nodo<Tipo> *current, *temp;
    current = inicio;
    temp = nullptr;
  
    while (current != NULL){

      temp = current->anterior;
      current->anterior = current->siguiente;
      current->siguiente = temp;
      current = current->anterior;
    }
  inicio = temp->anterior;//CORROBORRAR
  }
}

//HECHO POR FARID IZQUIERDO
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


//HECHO POR JULIO ASILLO
void insertarFinal(Tipo e) {//O(1)
  Nodo<Tipo>* nuevo = new Nodo<Tipo>(e);
  if (inicio == nullptr) {
      insertarInicio(e);
  } 
  else{
    fin->siguiente = nuevo;
    nuevo->anterior = fin;
    fin = nuevo;   
  }
  ++cantidad;
}



Tipo rotateList(int k){

  if(k<1)
    return inicio->elemento;

  Nodo<Tipo> *current = fin;
  fin->siguiente = inicio;
  inicio->anterior = fin;
  for (int i = 1; i <= k && current != nullptr; i++){
      inicio = inicio->siguiente;
      current = current->siguiente;
  }
   
  fin = current;
  fin->siguiente = nullptr;
  inicio->anterior = nullptr;
  return inicio->elemento;
}


void mostrar(function<void(Tipo)>funMostrar){
    Nodo<Tipo> *aux = inicio;
    while (aux->siguiente != nullptr)
    {
        //cout<<aux->elemento<<" ";
        funMostrar(aux->elemento);
        aux = aux->siguiente;
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

  ListaDoble<int> ls;

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
  ListaDoble <Virus*>ls;   
  ls.insertarFinal(new Virus("Covid",1));
  ls.insertarFinal(new Virus("Influenza",2));
  ls.insertarFinal(new Virus("Colera",3));
  //ls.insertarFinal(new Virus("Helix", 4));
  ls.insertarFinal(new Virus("Ivan", 18));
  ls.eliminarPosicion(2);
  ls.mostrar([](Virus*v){cout<<v->toString()<<" ";});
  /*ls.reverseList();
  cout << "Reversed List:";
  ls.mostrar([](Virus*v){cout<<v->toString()<<" ";});
  cout << "Fin: " << ls.fin->elemento->toString();
  cout << "Inicio: " << ls.inicio->elemento->toString();
  cout << "Rotated List: " << endl;
  ls.rotateList(1);
  ls.mostrar([](Virus*v){cout<<v->toString()<<" ";});
  cout << "Fin: " << ls.fin->elemento->toString();
  cout << "Inicio: " << ls.inicio->elemento->toString();*/
  cout<<ls.cantidad<<endl;

}

int main(){

  ejemplo2();

}