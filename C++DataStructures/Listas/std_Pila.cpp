#include <iostream>
#include <functional>
#include <cstdlib>
#include <stack>
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

  stack<Virus*> ls;
  ls.push(new Virus("Covid",1));
  ls.push(new Virus("Influenza",2));
  ls.push(new Virus("Colera",3));
  ls.push(new Virus("Helix", 4));
  ls.top()->toString();//ultimo
  cout<<ls.size()<<endl;
  while(ls.size()>0){
      cout<<ls.top()->toString();
      ls.pop();
  }
  cout << ls.size();
}

int main(){

  ejemplo2();

}