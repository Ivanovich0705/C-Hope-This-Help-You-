#include "pch.h"
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include <functional>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <sys/stat.h>
#include "Solution.h"
using namespace std;
using namespace System;

template <class T>
class Nodo {
public:
	T elemento;
	Nodo* izq;
	Nodo* der;
	Nodo(T elemento) {
		this->elemento = elemento;
		izq = der = nullptr;

	}
	Nodo() {  }
};

template <class T>
class ArbolB {
	Nodo<T>* raiz;

private:
	bool _insertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new Nodo<T>(e);
		}
		else if (e < nodo->elemento) {
			return _insertar(nodo->izq, e);
		}
		else if (e >= nodo->elemento) {
			return _insertar(nodo->der, e);
		}
	}
	void _enOrden(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);
		cout << nodo->elemento << " ";
		_enOrden(nodo->der);
	}

	bool _vacio() {
		return raiz == nullptr;
	}
	int _cantidad(Nodo<T>* nodo) {
		//La cantidad de nodos del árbol es:
		//	0 si es vacío
		//	1 + la cantidad de nodos por la izquierda + la cantidad de nodos por la derecha
		if (nodo == nullptr)
			return 0;
		else
		{
			int ci, cd;
			ci = _cantidad(nodo->izq);
			cd = _cantidad(nodo->der);
			return 1 + ci + cd;
		}

	}
public:
	ArbolB() {

		raiz = nullptr;
	}
	bool insertar(T e) {
		return _insertar(raiz, e);
	}
	void enOrden() {
		_enOrden(raiz);
	}
	int cantidad() {
		return _cantidad(raiz);
	}
	int altura() {
		return _altura(raiz);
	}
};

class Algorithms {

	template<typename K>
	void MergeSortedIntervals(vector<K>& v, int s, int m, int e, function<bool(K, K)>cmp) {

		vector<K> temp;
		int i, j;
		i = s;
		j = m + 1;

		while (i <= m && j <= e) {

			if (cmp(v[i], v[j])) {
				temp.push_back(v[i]);
				++i;
			}
			else {
				temp.push_back(v[j]);
				++j;
			}

		}

		while (i <= m) {
			temp.push_back(v[i]);
			++i;
		}

		while (j <= e) {
			temp.push_back(v[j]);
			++j;
		}

		for (int i = s; i <= e; ++i)
			v[i] = temp[i - s];

	}


public:
	bool isPrime(int n) {

		if (n <= 1)  return false;
		if (n <= 3)  return true;

		if (n % 2 == 0 || n % 3 == 0) return false;

		for (int i = 5; i * i <= n; i = i + 6)
			if (n % i == 0 || n % (i + 2) == 0)
				return false;

		return true;
	}


	string encryptString(string s, int crypt) {
		string e;
		for (int i = 0; i < s.length(); i++) {
			e.push_back(s.at(i));
			for (int j = 0; j < to_string(crypt).length(); j++)
				e.push_back(to_string(crypt).at(j));

		}
		return e;
	}

	string capitalizeString(string s) {
		transform(s.begin(), s.end(), s.begin(),
			[](unsigned char c) { return toupper(c); });
		return s;
	}

	template<class K>
	void adjacent_find(vector<K> v, function<bool(K, K)> cmp, function<void(K,K)>print) {
		int it = 0;
		if (v.at(it) != v.at(v.size() - 1)) {
			int next = it + 1;
			while (v.at(next) != v.at(v.size() - 1) ) {
				if (cmp(v.at(it), v.at(next))) {
					print(v.at(it), v.at(next));
					return;
				}
				++next; ++it;
			}
		}
	}

	template<class K>
	void MergeSort(vector<K>& v, int s, int e, function<bool(K, K)>cmp) {
		if (s < e) {
			int m = (s + e) / 2;
			this->MergeSort(v, s, m, cmp);
			this->MergeSort(v, m + 1, e, cmp);
			this->MergeSortedIntervals(v, s, m, e, cmp);
		}
	}

	template<class K>
	void for_each(vector<K> table, function<void(K)>toDo) {
		int it = 0;
		while (it != table.size()) {

			if (table.at(it) == nullptr) cout << "OBJECT NULLPTR 404\n";
			else
				toDo(table.at(it));

			it++;
		}

	}

	template <class K>
	void unique(vector<K>& v, function<bool(K,K)>cmp) {
		int erased = 0;
		int it = 0;
		int result = 0;
		while (v.at(it++) != v.at(v.size() - 1)) {

			if (cmp(v.at(result), v.at(it))) {
				v.erase(v.begin() + it);
				cout << "ERASED:\n" << it + 1 << endl;
				result++;
				erased++;
			}
		}
		cout << "HAN SIDO ELIMINADOS " << erased << " ELEMENTOS." << endl;
	}

	template<class K>
	void find_if(vector<K> table, function<bool(K)>cmp, function<void(K)>toDo) {
		int it = 0;
		while (it != table.size() - 1) {
			if (table.at(it) != nullptr && cmp(table.at(it))) {
				toDo(table.at(it));
			}
			++it;
		}
	}

	template<class K>
	void find_first_of(vector<K> table, function<bool(K)>cmp, function<void(K)>toDo) {
		int it = 0;
		while (it != table.size() - 1) {
			if (table.at(it) != nullptr && cmp(table.at(it))) {
				toDo(table.at(it));
				return;
			}
			++it;
		}
	}

	template<class K>
	void randomShuffle(vector<K>& v) {
		for (int i = v.size() - 1; i > 0; i--) {
			int j = rand() % (i + 1);
			swap(v.at(i), v.at(j));
		}
	}
	

	template<class K>
	void mismatch(vector<K> arr_table, function<bool(K, K)>cmp, function<void(K, K)>print) {
		vector<K> auxVector = arr_table;
		this->stable_sort<K>(auxVector, cmp);
			
		int it = 0;
		while (it != arr_table.size() - 1) {
			if (cmp(arr_table.at(it), auxVector.at(it))) {
				print(arr_table[it], auxVector[it]);
				vector<K>().swap(auxVector);
				auxVector.clear();
				return;
			}
			++it;
		}
	}



	template<class K>
	void stable_sort(vector<K>& arr_table, function<bool(K,K)>cmp) {

		for (int i = 0; i < arr_table.size() - 1; i++)	{

			int min = i;
			for (int j = i + 1; j < arr_table.size(); j++)
				if (cmp(arr_table[min], arr_table[j]))//a[min] > a[j]
					min = j;

			K key = arr_table.at(min);

			while (min > i)	{

				arr_table[min] = arr_table[min - 1];
				min--;
			}
			arr_table[i] = key;
		}
	}
	

	template<class K, class T>
	void copy_if(vector<K>& arr_table, vector<T>& aux_table, function<bool(K)>cmp) {
		int it = 0;
		while (it < arr_table.size() - 1) {
			if (arr_table.at(it) != nullptr)
				if (cmp(arr_table.at(it)))
					aux_table.push_back(arr_table.at(it)->getValue());
			++it;
		}
	}

};

template<class T>
class HashTable:public Algorithms {

	vector<HashEntidad<T>*> table;
	vector<T> DataList;
    int cant;
    int bucket;
public:
	HashTable(int bucket = 3250) {
		this->bucket = FindNextPrime(bucket * 2);
		for (long i = 0; i < this->bucket; i++) 
			table.push_back(nullptr);
        
        this->cant = 0;
    }

	vector<HashEntidad<T>*> getVector() { return table; }
	vector<T> getAuxVector() { return this->DataList; }
	vector<T>& getModifiableAuxVector() { return this->DataList; }

	int maxCapacity() {	return bucket;}

	int actualSize() { return cant;	}

    long HashFunction(string key) {
		//cout << endl << bucket;
        int decrypt = 0;
        for (unsigned int i = 0; i < key.length(); i++) {
            decrypt += (int(key.at(i) - 64) + pow(27, key.length() - 1 - i));

        }
		//cout << "decrypt:" << decrypt << endl;
        return abs(decrypt % bucket);
    }

	int FindNextPrime(int n) {

		if (n <= 1)
			return 2;

		int prime = n;
		bool found = false;

		while (!found) {
			prime++;

			if (this->isPrime(prime))
				found = true;
		}

		return prime;
		//Algoritmo de Criba de Erastotenes
	}

	void addEntity(string key, T value) {
		int base, step, hash;
		if (cant == bucket) { 
			cout << "ERROR, MAX CAPACITY FILLED \n";
			return;
		}
		base = HashFunction(key);
		hash = base;
		step = 0;
		while (table.at(hash) != nullptr) {

			hash = (base + step) % bucket;
			step++;
		}
		table.at(hash) = new HashEntidad<T>(key, value);
		cant++;
	}

	void modifyData(string key, T value) {
		int step = 0;
		int i, base;
		i = base = HashFunction(key);
		int cont = 0;
		bool ended = false;
		while (!ended) {

			if (tabla.at(i) == nullptr) {

				ended = true;
			}
			else if (tabla.at(i)->getKey() == key) {
				tabla.at(i)->setValue(value);
				ended = true;
				return;
			}
			else {
				step++;
				cont++;
				if (cont == bucket) ended = true;
			}

			i = (base + step) % bucket;
		}

	}

	void eraseData(string key) {
		int step = 0;
		int i, base;
		i = base = HashFunction(key);
		int cont = 0;
		bool ended = false;
		while (!ended) {

			if (tabla.at(i) == nullptr) {
				ended = true;
			}
			else if (tabla.at(i)->getKey() == key) {
				cant--;
				tabla.at(i) = nullptr;
				ended = true;
				return;
			}
			else {
				step++;
				cont++;
				if (cont == bucket) ended = true;
			}

			i = (base + step) % bucket;
		}
		
	}

	void returnEntity(string key, function<void(HashEntidad<T>*)>print) {
		int step = 0;
		int i, base;
		i = base = this->HashFunction(key);
		int cont = 0;
		for (int j = 0; j < bucket; j++) {

			if (table.at(i) == nullptr) {}
			else if (table.at(i)->getKey() == key) {
				print(table.at(i));
				return;
			}

			step++;

			i = (base + step) % bucket;
		}
		cout << "ERROR 404";
	}


	void saveToAux() {
		int it = 0;
		while (it != table.size()) {
			if (table.at(it) != nullptr)
				DataList.push_back(table.at(it)->getValue());
			it++;
		}		
	}

	void saveData(string archName) {
		int it = 0;
		int crypt = HashFunction(archName);
		ofstream DataBase("Data/" + encryptString(archName, to_string(crypt).at(0)) + ".txt");
		this->randomShuffle(DataList);
		while (it != DataList.size() - 1) {
			DataBase << *DataList.at(it);
			it++;
		}

	}

	inline bool dataExist(const std::string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

	bool loadHashData(string key) {
		short year, rank;
		string name, platform, genre, publisher, dummy;
		string t_year, t_rank, t_NA_Sales, t_EU_Sales, t_JP_Sales, t_Global_Sales;
		float NA_Sales, EU_Sales, JP_Sales, Global_Sales;
		int crypt = HashFunction(key);
		if (dataExist("Data/" + encryptString(key, to_string(crypt).at(0)) + ".txt")) {
			ifstream DataBase("Data/" + encryptString(key, to_string(crypt).at(0)) + ".txt");
			while (DataBase >> t_rank >> name >> platform >> t_year >> genre >> publisher >> t_NA_Sales >> t_EU_Sales >> t_JP_Sales >> t_Global_Sales) {
				year = stoi(t_year);
				rank = stoi(t_rank);
				NA_Sales = stof(t_NA_Sales);
				EU_Sales = stof(t_EU_Sales);
				JP_Sales = stof(t_JP_Sales);
				Global_Sales = stof(t_Global_Sales);
				DataList.push_back(new Game(rank, name, platform, year, genre, publisher, NA_Sales, EU_Sales, JP_Sales, Global_Sales));
			}
			DataBase.close();
			cout << "Database Successfully Loaded \n";
			return true;
		}
		else {
			cout << "FILE NOT FOUNDED\n";
			return false;
		}
	}

};

class VideoGameRanked {
	//HashTable<Game*> ranking;
	ArbolB<Game> ranking;
	short year, rank;
	string name, platform, genre, publisher, dummy;
	string t_year, t_rank, t_NA_Sales, t_EU_Sales, t_JP_Sales, t_Global_Sales;
	float NA_Sales, EU_Sales, JP_Sales, Global_Sales;
	long cont;
public:
	VideoGameRanked() {
		cont = 1;
		ifstream DataBase("VideoGamesDataBase.csv");
		getline(DataBase, dummy);
		while (DataBase >> t_rank >> name >> platform >> t_year >> genre >> publisher >> t_NA_Sales >> t_EU_Sales >> t_JP_Sales >> t_Global_Sales) {
			//cout << t_rank << name << platform << t_year << genre << publisher << t_NA_Sales << t_EU_Sales << t_JP_Sales << t_Global_Sales;
			cont++;
			//cout << cont << endl;
			year = stoi(t_year);
			rank = stoi(t_rank);
			NA_Sales = stof(t_NA_Sales);
			EU_Sales = stof(t_EU_Sales);
			JP_Sales = stof(t_JP_Sales);
			Global_Sales = stof(t_Global_Sales);
			ranking.insertar(Game(rank, name, platform, year, genre, publisher, NA_Sales, EU_Sales, JP_Sales, Global_Sales));
			//ranking.addEntity(ranking.capitalizeString(name), new Game(rank, name, platform, year, genre, publisher, NA_Sales, EU_Sales, JP_Sales, Global_Sales));
		}
		DataBase.close();
		cout << "Database Successfully Uptaded \n";
		ranking.enOrden();
		//cout << "\n" << ranking.cantidad();
	}

	void tests() {

		srand(time(NULL));
		/*ranking.for_each<HashEntidad<Game*>*>(ranking.getVector(), [](HashEntidad<Game*>* h) {cout << h->getValue()->toString(); });

		ranking.find_if<HashEntidad<Game*>*>(ranking.getVector(), [](HashEntidad<Game*>* h) {return h->getValue()->getYear() == 2009; },
			[](HashEntidad<Game*>* h) {cout << h->getValue()->toString(); });

		ranking.find_if<HashEntidad<Game*>*>(ranking.getVector(), [=](HashEntidad<Game*>* h) {return h->getKey().find(ranking.capitalizeString("SuperMario64")) != string::npos; },
			[](HashEntidad<Game*>* h) {cout << h->getValue()->toString(); });

		ranking.returnEntity(ranking.capitalizeString("SuperMario64"), [](HashEntidad<Game*>* h) {cout << h->getValue()->toString(); });*/
	

		//ranking.MergeSort<Game*>(ranking.getModifiableAuxVector(), 0,  ranking.getAuxVector().size() - 1, [](Game* a, Game* b) {return a->getRank() <= b->getRank(); });

		//ranking.randomShuffle<Game*>(ranking.getModifiableAuxVector());

		//ranking.copy_if<HashEntidad<Game*>*, Game*>(ranking.getVector(), ranking.getModifiableAuxVector(), 
			//[](HashEntidad<Game*>* condicion) {return condicion->getValue()->getYear() % 2 == 0; });

		//ranking.stable_sort<Game*>(ranking.getModifiableAuxVector(),
			//[](Game* a, Game* b) {return a->getGlobalSales() < b->getGlobalSales(); });
		
		//ranking.for_each<Game*>(ranking.getAuxVector(), [](Game* h) {cout << h->toString(); });

		/*ranking.mismatch<Game*>(ranking.getAuxVector(),
			[](Game* a, Game* b) {return a->getYear() < b->getYear(); },
			[](Game* a, Game* b) {cout << "First Mismatch Objects:\n" << a->toString() << endl <<
			b->toString(); });*/

		//ranking.saveData("Jp_Sales");

		//ranking.loadHashData("JP_SALES");
	}

	
};


void prePrint() {
	cout << endl << "Ranking\t" << "Name\t" << "Platform\t" << "Year\t"
		<< "Genre\t" << "Publisher\t" << "NA Sales\t" << "EU Sales\t" << 
		"JP Sales\t" << "Global Sales\t" << endl;
}

int main(){

	VideoGameRanked PC_2;
	//PC_2.tests();
	//int op;
	//do {
	//	Console::Clear();
	//	cout << "************* MENU HASHTABLE **************" << endl;
	//	cout << "[1] - For_Each" << endl;
	//	cout << "[2] - Find_If" << endl;
	//	cout << "[3] - Find_First_Of" << endl;
	//	cout << "[4] - Random_Shuffle" << endl;
	//	cout << "[5] - Merge_Sort" << endl;
	//	cout << "[6] - Mismatch" << endl;
	//	cout << "[7] - Copy_If" << endl;
	//	cout << "[8] - Stable_Sort" << endl;
	//	cout << "[9] - Adjacent_find" << endl;
	//	cout << "[10] - Unique" << endl;
	//	cout << "[11] - Save Data" << endl;
	//	cout << "[12] - Load And Show Data" << endl;
	//	cout << "[0] - Salir" << endl;
	//	cout << "Ingrese Opcion:";
	//	cin >> op;
	//	PC_2.Menu(op);
	//	//system("pause");
	//} while (op != 0);

    return 0;
}
