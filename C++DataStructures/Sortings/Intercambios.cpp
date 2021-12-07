#include <iostream>
#include <functional>
#include <cstdlib>
using namespace std;


void intercambio1(int a[], int n){

    for (int i = 0; i < 1;i++){
        for (int k = i + 1; k < n;k++){
            if(a[i]>a[k]){
                int aux = a[i];
                a[i] = a[k];
                a[k] = aux;
            }
        }
    }
    for (int i = 0; i < 6;i++)
        cout << a[i] << endl;
}

void intercambio2(int a[], int n){
    bool ordenado;
    int cambios = 0;
    for (int i = 0; i < 3;i++){
        ordenado = true;
        for (int j = 0; j < n - (i + 1); j++)
        {
            if(a[j]>a[j+1]){
                
                int aux = a[j];
                a[j] = a[j + 1];
                a[j + 1] = aux;
                ordenado = false;
                cambios++;
            }
        }
        if(ordenado)
            break;
    }
    cout << "cambio: " << cambios << endl;
}

int main(){
    int a[]={5, 3, 6, 1, 9, 2};
    intercambio2(a, 6);
    
}