#include <iostream>
#include <functional>
#include <cstdlib>
#include <queue>
using namespace std;

class Virus{
  string nombre;
  short idx;
  public:
  Virus(string nombre,short idx):nombre(nombre),idx(idx){}
  string getNombre(){return nombre;}
  string toString(){return nombre+" "+to_string(idx)+"\n";}
};



void ejemplo2(){

  queue<Virus*> ls;
  ls.push(new Virus("Covid",1));
  ls.push(new Virus("Influenza",2));
  ls.push(new Virus("Colera",3));
  ls.push(new Virus("Helix", 4));
  ls.front()->toString();//primero
  cout<<ls.size()<<endl;
  while(ls.size()>0){
      cout<<ls.front()->toString();
      ls.pop();
  }
  cout << ls.size();
}

int main(){

  ejemplo2();

}