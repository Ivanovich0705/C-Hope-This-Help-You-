#pragma once

template <typename T>
class Node {
public:
    T elemento;
    Node<T>* siguiente;
    Node<T>* anterior;
    Node(T e) { elemento = e; siguiente = anterior = nullptr; }
};


template <typename T>
class BlockChain {
public:
    Node<T>* inicio;
    Node<T>* fin;
    long cantidad;
public:

    BlockChain() {
        inicio = fin = nullptr;
        cantidad = 0;
    }

    void insertarInicio(T e) {
        Node<T>* nuevo = new Node<T>(e);
        if (inicio == nullptr)
            inicio = fin = nuevo;
        else {
            inicio->anterior = nuevo;
            nuevo->siguiente = inicio;
        }
        inicio = nuevo;
        inicio->anterior = nullptr;
        cantidad++;
    }


    void eliminarInicio() {
        if (cantidad > 0) {
            Node<T>* aux = inicio;
            inicio = inicio->siguiente;
            inicio->anterior = nullptr;

            delete aux;
            cantidad--;
        }
    }


    void eliminarPosicion(int pos) {
        if (pos > cantidad)
            return;

        if (pos == 0)
            eliminarInicio();
        else {
            Node<T>* aux = inicio;
            for (int i = 1; i < pos; i++)
                aux = aux->siguiente;
            aux->siguiente->anterior = aux->anterior;
            aux->anterior->siguiente = aux->siguiente;
            delete aux;
            cantidad--;
        }
    }


    T At(int pos) {
        if (pos >= 0 && pos < cantidad) {
            Node<T>* aux = inicio;
            for (int i = 0; i < pos; i++)
                aux = aux->siguiente;
            if (aux != nullptr)return aux->elemento;//HERE
        }
        else
            return nullptr;
    }

    void showObj(function<bool(T)> cmp, function<void(T)>funMostrar) {

        bool cont = false;
        Node<T>* aux = inicio;
        while (aux != nullptr) {

            if (cmp(aux->elemento)) {
                funMostrar(aux->elemento);
                aux = aux->siguiente;
                cont = true;
            }
            else
                aux = aux->siguiente;
        }
        if (cont != true)
            cout << "ERROR 404";
        return;

    }

    void updateBlockChain(T temp){//NOTACIÓN DETALLADA O(n) 
        Node<T>* aux = inicio; // 1

        while (aux->elemento != temp) {// n(1 + .....)
            aux = aux->siguiente;// 1
        }//2n
        
        aux->elemento->reloadHash();             // 1
        aux->siguiente;         // 1
        while (aux != fin) {            // n(1 + ...)
            aux->elemento->uptadeHash(aux->anterior->elemento->getKey());        // 1 + 1
            aux = aux->siguiente;       // 1
        }       // n(4)
        aux->elemento->uptadeHash(aux->anterior->elemento->getKey()); // 1 + 1
        // Notación detallada: 6n + 5
    }

    T recieveUser(function<bool(T)> cmp) {

        Node<T>* aux = inicio;
        while (aux != nullptr) {

            if (cmp(aux->elemento)) {

                return aux->elemento;
            }
            else
                aux = aux->siguiente;
        }
        cout << "ERROR 404";

    }

    bool existe(function<bool(T)> cmp) {

        Node<T>* aux = inicio;
        while (aux != nullptr)
        {
            if (cmp(aux->elemento)) {

                return true;
            }
            else
                aux = aux->siguiente;
        }
        return false;
    }

    void deleteAllNodes() {
        Node<T>* temp = new Node<T>(nullptr);

        while (inicio != nullptr) {
            temp = inicio;
            inicio = inicio->siguiente;
            free(temp);
        }
    }

    void insertarFinal(T e) {//O(1)
        Node<T>* nuevo = new Node<T>(e);
        if (inicio == nullptr) {
            insertarInicio(e);
        }
        else {
            fin->siguiente = nuevo;
            nuevo->anterior = fin;
            fin = nuevo;
        }
        ++cantidad;
    }

    void mostrar(function<void(T)>funMostrar) {
        Node<T>* aux = inicio;
        while (aux->siguiente != nullptr) {

            funMostrar(aux->elemento);
            aux = aux->siguiente;
        }
        funMostrar(aux->elemento);
    }

    string returnString(function<string(T)>funMostrar) {
        string print;
        Node<T>* aux = inicio;
        if (aux == nullptr)return "";
        while (aux->siguiente != nullptr) {

            print += funMostrar(aux->elemento);
            aux = aux->siguiente;
        }
        print += funMostrar(aux->elemento);
        return print;
    }

    void compare(function<bool(T, T)>cmp, function<void(T)>print) {

        Node<T>* aux = inicio;
        while (aux->siguiente != nullptr) {

            if (aux->anterior != nullptr && cmp(aux->elemento, aux->anterior->elemento)) {

                cout << "CORRECT" << endl;
                print(aux->elemento);
            }
            else {
                if (aux->anterior != nullptr) {
                    cout << "ERROR ERROR ERROR ERROR" << endl;
                    print(aux->anterior->elemento);
                }
            }
            aux = aux->siguiente;
        }

    }

    int size() {
        short c = 0;
        Node<T>* aux = inicio;
        while (aux != nullptr) {
            c++;
            aux = aux->siguiente;
        }

        return c;
    }

};