#include "pch.h"
#include <vector>
#include <functional>
#include <iostream>
#include <string>
using namespace std;
using namespace System;

class Student {
    string nombre;
    int edad;
public:
    Student(string nombre, int edad): nombre(nombre), edad(edad){}
    string getNombre() { return nombre; }
    int getEdad() { return edad; }
    string toString() { return nombre + "\t" + to_string(edad) + "\n"; }

    friend ostream& operator<<(ostream& os, const Student& r) {
        os << r.nombre << " " << r.edad << endl;
        return os;
    }
    bool operator<(const Student& r) const{
        return this->edad < r.edad;
    }
    bool operator>(const Student& r)const {
        return this->edad > r.edad;
    }

};

template<class T>
int binarySearch( const vector<T>& v,  const T& x) {
    int low = 0, high = v.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (v[mid] < x)
            low = mid + 1;
        else if (v[mid] > x)
            high = mid - 1;
        else 
            return mid;

    }
    return -1;
}

int main()
{
    vector<Student> database;
    database.push_back(Student("Pepe", 10));
    database.push_back(Student("Juan", 20));
    database.push_back(Student("Ivan", 30));
    database.push_back(Student("Luis", 40));
    database.push_back(Student("Ricardo", 50));
    database.push_back(Student("Matias", 60));
    database.push_back(Student("Diego", 70));
    database.push_back(Student("Walter", 80));
    database.push_back(Student("Mundaca", 90));
    database.push_back(Student("Felipe", 100));

    for (int i = 0; i < database.size(); i++) {

        cout << database.at(i);
    }


    cout << binarySearch(database, Student("Luis", 40)) + 1;
    
    return 0;
}
