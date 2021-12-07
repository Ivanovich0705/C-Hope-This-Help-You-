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
#include <windows.h>
#include "SHA265.h"
#include "Entidades.h"
#include "DoubleLinkedList.h"
#include "BinaryTree.h"
using namespace std;
using namespace System;

string capitalizeString(string s) {
	transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c) { return toupper(c); });
	return s;
}

string toHours(int minutes) {

	std::stringstream stream;
	stream << fixed << setprecision(2) << std::setfill('0') << std::setw(2) << minutes / 60 << ":" << std::setfill('0')
		<< std::setw(2) << minutes % 60 << ":00";
	return stream.str();
}

class Control {//pasarle otro lambda q haga un getvalue
	BinaryT<HashEntidad<Movie>*, Movie> ranked;
	BlockChain<HashEntidad<Movie>*> lista;
	BinaryT<alphabeticEntity<HashEntidad<Movie>*>, alphabeticEntity<HashEntidad<Movie>*>> alphabeticTree;
	short rank, year, metascore;
	string title, genre, director, runtime, dummy;
	string indexer;
	string t_rank, t_year, t_votes, t_metascore, t_rating, t_revenue, t_blockchain = "";
	int votes;
	float rating, revenue;
	long cont;
	bool first = true;
	string blockChain = " ";
	void mostrar() {
		ranked.enOrden();
		lista.mostrar([](HashEntidad<Movie>* a1) {cout << a1->getValue() << a1->getKey() << endl; });
	}

public:
	Control() {
		cout << "************* MENU IMDB RANK ************" << endl;
		cout << "INGRESE FORMA DE INDEXAMIENTO...(votos, titulo, runtime)\n";
		cin >> indexer;
		if (indexer == "votos") {
			ranked = BinaryT<HashEntidad<Movie>*, Movie>([](HashEntidad<Movie>* o1, HashEntidad<Movie>* o2) {
				if (o1->getValue().getVotes() == o2->getValue().getVotes())
					return 0;
				else if (o1->getValue().getVotes() > o2->getValue().getVotes())
					return 1;
				else if (o1->getValue().getVotes() < o2->getValue().getVotes())
					return -1;
				},
				[](HashEntidad<Movie>* o1) {return o1->getValue(); }, [](HashEntidad<Movie>* o1, HashEntidad<Movie>* o2) {
					return o1->getValue().getVotes() < o2->getValue().getVotes(); });
		}
		else if (indexer == "titulo") {
			ranked = BinaryT<HashEntidad<Movie>*, Movie>([](HashEntidad<Movie>* o1, HashEntidad<Movie>* o2) {
				if (o1->getValue().getTitle() == o2->getValue().getTitle())
					return 0;
				else if (o1->getValue().getTitle() > o2->getValue().getTitle())
					return 1;
				else if (o1->getValue().getTitle() < o2->getValue().getTitle())
					return -1;
				},
				[](HashEntidad<Movie>* o1) {return o1->getValue(); }, [](HashEntidad<Movie>* o1, HashEntidad<Movie>* o2) {
					return o1->getValue().getTitle() < o2->getValue().getTitle(); });
		}
		else if (indexer == "runtime") {
			ranked = BinaryT<HashEntidad<Movie>*, Movie>([](HashEntidad<Movie>* o1, HashEntidad<Movie>* o2) {
				if (o1->getValue().getRuntime() == o2->getValue().getRuntime())
					return 0;
				else if (o1->getValue().getRuntime() > o2->getValue().getRuntime())
					return 1;
				else if (o1->getValue().getRuntime() < o2->getValue().getRuntime())
					return -1;
				},
				[](HashEntidad<Movie>* o1) {return o1->getValue(); }, [](HashEntidad<Movie>* o1, HashEntidad<Movie>* o2) {
					return o1->getValue().getRuntime() < o2->getValue().getRuntime(); });
		}

		alphabeticTree = BinaryT<alphabeticEntity<HashEntidad<Movie>*>, alphabeticEntity<HashEntidad<Movie>*>>(
			[](alphabeticEntity<HashEntidad<Movie>*> o1, alphabeticEntity<HashEntidad<Movie>*> o2) {
				if (o1 == o2)
					return 0;
				else if (o1 > o2)
					return 1;
				else if (o1 < o2)
					return -1; },
			[](alphabeticEntity<HashEntidad<Movie>*> a1) { a1.makeString(); return a1; },
			[](alphabeticEntity<HashEntidad<Movie>*> a1, alphabeticEntity<HashEntidad<Movie>*> a2) {
			return a1 < a2; });

		cont = 1;
		ifstream DataBase("IMDB-Movie-Data.csv");
		getline(DataBase, dummy);
		while (DataBase >> t_rank >> title >> genre >> director >> t_year >> runtime >>
			t_rating >> t_votes >> t_revenue >> t_metascore) {
			blockChain = "";
			cont++;
			rank = stoi(t_rank);
			year = stoi(t_year);
			votes = stoi(t_votes);
			metascore = stoi(t_metascore);
			runtime = toHours(stoi(runtime));
			rating = stof(t_rating);
			revenue = stof(t_revenue);
			auto tempMovie = Movie(rank, title, genre, director, year, runtime, rating, votes, revenue, metascore);
			if (first) {
				blockChain = "";
				first = false;
			}
			else
				blockChain = lista.fin->elemento->getKey();

			auto tempHash = new HashEntidad<Movie>(blockChain, tempMovie);
			//cout << rank << " "<<title << " " << genre << " " << director << " " << year << " " << runtime << " " << rating << " " << votes << " " << revenue << " " << metascore << endl;
			//1300 Chernobyl Science,Suspense,Drama JohanReck 2021 05:15:00 8.1 874728 80.34 95
			ranked.insertar(tempHash);
			lista.insertarFinal(tempHash);
			t_blockchain = SHA256::cifrar(tempMovie.toString());
		}
		DataBase.close();
		cout << "Database Successfully Uptaded \n";
		//ranked.enOrden();
		//lista.mostrar([](HashEntidad<Movie>* a1) {cout << a1->getValue() << a1->getKey() << endl; });

		for (short i = 0; i <= 25; i++)
			alphabeticTree.insertar(alphabeticEntity<HashEntidad<Movie>*>(char(i + 65)));

		//createEndTree();
		//eraseAlphabeticTree();
		//createStartTree();
		//alphabeticTree.enOrden();
		//system("pause");
	}

	void test1() {
		ranked.buscar(new HashEntidad<Movie>(Movie(164, "hola", "hola", "hola", 164, "4:0:0", 164, 61, 164, 31)));

		cout << endl;
		lista.mostrar([](HashEntidad<Movie>* a1) {cout << a1->getValue() << a1->getKey() << " " << a1->getBackKey() << endl; });
		//ranked.enOrden();
	}


	void createStartTree() {
		//alphabeticTree.obtener(alphabeticEntity<HashEntidad<Movie>*>('A')).addToList(new HashEntidad<Movie>(Movie(164, "hola", "hola", "hola", 164, "4:0:0", 164, 61, 164, 31)));
		//cout<<alphabeticTree.buscar(alphabeticEntity<HashEntidad<Movie>*>('A')).getList().cantidad;
		for (short i = 0; i <= 25; i++) {
			char aux = char(i + 65);
			auto& temp = alphabeticTree.obtener(alphabeticEntity<HashEntidad<Movie>*>(aux));
			lista.showObj([aux](HashEntidad<Movie>* a1) {return toupper(a1->getValue().getTitle().at(0)) == aux; },
				[&](HashEntidad<Movie>* a1) {temp.addToList(a1); });
		}
		//cout << alphabeticTree.buscar(alphabeticEntity<HashEntidad<Movie>*>('A'));
		//alphabeticTree.obtener(alphabeticEntity<HashEntidad<Movie>*>('A')).addToList(a1)
	}

	void eraseAlphabeticTree() {
		for (short i = 0; i <= 25; i++) {
			char aux = char(i + 65);
			auto& temp = alphabeticTree.obtener(alphabeticEntity<HashEntidad<Movie>*>(aux));
			temp.eraseList();
		}
	}

	void createEndTree() {
		for (short i = 0; i <= 25; i++) {
			char aux = char(i + 65);
			auto& temp = alphabeticTree.obtener(alphabeticEntity<HashEntidad<Movie>*>(aux));
			lista.showObj([aux](HashEntidad<Movie>* a1) {return 
				toupper(a1->getValue().getTitle().at(a1->getValue().getTitle().length()-1)) == aux; },
				[&](HashEntidad<Movie>* a1) {temp.addToList(a1); });
		}
			Console::Clear();
	}

	void addEntity() {
		cout << "Ingrese Datos\nRango Titulo\n Genero Diretor Year Runtime Rating Votos Revenue MetaScore\n";
		cin >> t_rank >> title >> genre >> director >> t_year >> runtime >>
			t_rating >> t_votes >> t_revenue >> t_metascore;
		blockChain = "";
		cont++;
		rank = stoi(t_rank);
		year = stoi(t_year);
		votes = stoi(t_votes);
		metascore = stoi(t_metascore);
		runtime = toHours(stoi(runtime));
		rating = stof(t_rating);
		revenue = stof(t_revenue);
		auto tempMovie = Movie(rank, title, genre, director, year, runtime, rating, votes, revenue, metascore);
		auto tempHash = new HashEntidad<Movie>(lista.fin->elemento->getKey(), tempMovie);
		//1300 Chernobyl Science,Suspense,Drama JohanReck 2021 05:15:00 8.1 874728 80.34 95
		ranked.insertar(tempHash);
		lista.insertarFinal(tempHash);
		t_blockchain = SHA256::cifrar(tempMovie.toString());

	}

	void modifyEntity(HashEntidad<Movie>* temp) {
		string stringAux;
		int intAux;
		cout << "************* MENU IMDB RANK ************" << endl;
		cout << temp->getValue();
		temp->doBackUp();
		cout << "Ingrese que dato quiere modificar\n";
		cout << "Rango, Titulo, Genero, Diretor, Year, Runtime, Rating, Votos, Revenue o MetaScore\n";
		cin >> dummy;
		cout << "INGRESE NUEVA INFORMACION\n";
		if (dummy == "genero") {
			cin >> stringAux;
			temp->getValue().setGenre(stringAux);
		}
		else if (dummy == "director") {
			cin >> stringAux;
			temp->getValue().setDirector(stringAux);
		}
		else if (dummy == "year") {
			cin >> intAux;
			temp->getValue().setYear(intAux);
		}
		else if (indexer != "runtime" && dummy == "runtime") {//
			cin >> stringAux;
			temp->getValue().setRuntime(stringAux);
		}
		else if (indexer == "runtime" && dummy == "runtime") {//
			cout << "YOU DONT HAVE PERMISION\n";
			return;
		}
		else if (dummy == "rating") {
			cin >> intAux;
			temp->getValue().setRating(intAux);
		}
		else if (indexer != "votos" && dummy == "votos") {//
			cin >> intAux;
			temp->getValue().setVotes(intAux);
		}
		else if (indexer == "votos" && dummy == "votos") {//
			cout << "YOU DONT HAVE PERMISION\n";
			return;

		}
		else if (indexer != "titulo" && dummy == "titulo") {//
			cin >> stringAux;
			temp->getValue().setTitle(stringAux);
		}
		else if (indexer == "titulo" && dummy == "titulo") {//
			cout << "YOU DONT HAVE PERMISION\n";
			return;
		}
		else if (dummy == "rango") {
			cin >> intAux;
			temp->getValue().setRank(intAux);
		}
		else if (dummy == "revenue") {
			cin >> intAux;
			temp->getValue().setRevenue(intAux);
		}
		else if (dummy == "metascore") {
			cin >> intAux;
			temp->getValue().setMetaScore(intAux);
		}
		else if (dummy == "rating") {
			cin >> intAux;
			temp->getValue().setRating(intAux);
		}
		lista.updateBlockChain(temp);
		//temp->uptadeHash(temp->getValue().toString());
	}

	void dsa() {
		auto temp = ranked.obtener(new HashEntidad<Movie>(Movie
		(733, "ThisBeautifulFantastic", "Comedy,Drama,Fantasy", "SimonAboud", 2016, "1:30:20", 6.9, 688, 0, 51)));

		temp->doBackUp();
		temp->getValue().setTitle("Vegeta777");
		//temp->uptadeHash(temp->getValue().toString());
		temp->doBackUp();
		cout << temp->getPila().top() << endl;
		temp->getPila().pop();
		cout << temp->getPila().top();
		//ranked.enOrden();
	}

	void searchAlphabeticTree() {
		char aux;
		cout << "Ingrese palabra clave...\n";
		cin.ignore();
		cin >> aux;
		cout << endl;
		auto& temp = alphabeticTree.obtener(alphabeticEntity<HashEntidad<Movie>*>(aux));
		temp.makeString();
		cout << temp;
		
	}

	void Menu(short op) {

		int intAux2;
		string stringAux2;
		int auxData;
		string auxInfo;
		switch (op) {
		case 1:
			this->addEntity();
			system("pause");
			break;

		case 2:
			//lista.mostrar([](HashEntidad<Movie>* a1) {cout << a1->getKey() << " " << a1->getBackKey() << endl; });
			ranked.enOrden();
			system("pause");
			break;

		case 3:
			if (indexer == "votos") {
				cout << "Ingrese N# de Votos de la Pelicula a Modificar\n";
				cin >> intAux2;
				auto temp = ranked.buscar(new HashEntidad<Movie>(Movie(0, "", "", "", 0, "", 0, intAux2, 0, 0)));
				if (temp != nullptr)
					this->modifyEntity(temp);
				else
					cout << "NOT FOUND\n";

			}
			else if (indexer == "titulo") {
				cout << "Ingrese Titulo de la Pelicula a Modificar\n";
				cin >> stringAux2;
				auto temp = ranked.buscar(new HashEntidad<Movie>(Movie(0, stringAux2, "", "", 0, "", 0, 0, 0, 0)));
				if (temp != nullptr)
					this->modifyEntity(temp);
				else
					cout << "NOT FOUND\n";

			}
			else if (indexer == "runtime") {
				cout << "Ingrese Tiempo de la Pelicula a Modificar\n";
				cin >> stringAux2;
				auto temp = ranked.buscar(new HashEntidad<Movie>(Movie(0, "", "", "", 0, stringAux2, 0, 0, 0, 0)));
				if (temp != nullptr)
					this->modifyEntity(temp);
				else
					cout << "NOT FOUND\n";

			}
			system("pause");
			break;

		case 4:
			if (indexer == "votos") {
				cout << "Ingrese N# de Votos de la Pelicula Modificada\n";
				cin >> intAux2;
				auto temp = ranked.buscar(new HashEntidad<Movie>(Movie(0, "", "", "", 0, "", 0, intAux2, 0, 0)));
				if (temp != nullptr) {
					while (temp->getPila().inicio != nullptr && temp->getPila().cantidad != 0) {
						cout << temp->getPila().top() << endl;
						if (temp->getPila().cantidad != 0)
							temp->getPila().pop();
					}
					cout << temp->getValue();
				}
				else
					cout << "NOT FOUND\n";


			}
			else if (indexer == "titulo") {
				cout << "Ingrese Titulo de la Pelicula Modificada\n";
				cin >> stringAux2;
				auto temp = ranked.buscar(new HashEntidad<Movie>(Movie(0, stringAux2, "", "", 0, "", 0, 0, 0, 0)));
				if (temp != nullptr) {
					while (temp->getPila().inicio != nullptr && temp->getPila().cantidad != 0) {
						cout << temp->getPila().top() << endl;
						temp->getPila().pop();
					}
					cout << temp->getValue();
				}
				else
					cout << "NOT FOUND\n";

			}
			else if (indexer == "runtime") {
				cout << "Ingrese Tiempo de la Pelicula Modificada\n";
				cin >> stringAux2;
				auto temp = ranked.buscar(new HashEntidad<Movie>(Movie(0, "", "", "", 0, stringAux2, 0, 0, 0, 0)));
				if (temp != nullptr) {
					while (temp->getPila().inicio != nullptr && temp->getPila().cantidad != 0) {
						cout << temp->getPila().top() << endl;
						temp->getPila().pop();
					}
					cout << temp->getValue();
				}
				else
					cout << "NOT FOUND\n";

			}
			system("pause");
			break;

		case 5:
			Console::Clear();
			cin.ignore();
			cout << "Filtrar Datos ..." << endl;
			cout << "[1] - Mostrar Datos que sean igual a" << endl;
			cout << "[2] - Mostrar Datos que inicien con " << endl;
			cout << "[3] - Mostrar Datos que finalizen con" << endl;
			cout << "[4] - Mostrar Datos que contengan" << endl;
			cout << "[5] - Mostrar Datos que no contengan" << endl;
			cin >> intAux2;
			Console::Clear();

			if (indexer == "votos") {
				if (intAux2 != 2 && intAux2 != 3) {
					cin.ignore();
					cout << "Ingrese palabra clave ..." << endl;
					cin >> auxData;
					cout << endl;
				}
				switch (intAux2) {
				case 1:
					cout << ranked.buscar(new HashEntidad<Movie>(Movie(0, "", "", "", 0, "", 0, auxData, 0, 0)))->getValue();
					system("pause");
					break;

				case 2:
					createStartTree();
					searchAlphabeticTree();
					eraseAlphabeticTree();
					system("pause");
					break;

				case 3:
					createEndTree();
					searchAlphabeticTree();
					eraseAlphabeticTree();
					system("pause");
					break;

				case 4:
					lista.showObj([auxData](HashEntidad<Movie>* s1)->bool {
						return to_string(s1->getValue().getVotes()).find(to_string(auxData)) != string::npos; },
						[](HashEntidad<Movie>* s1) {cout << s1->getValue() << endl; });
					system("pause");
					break;

				case 5:
					lista.showObj([auxData](HashEntidad<Movie>* s1)->bool { if (
						to_string(s1->getValue().getVotes()).find(to_string(auxData)) != string::npos) return false; else return true; },
						[](HashEntidad<Movie>* s1) {cout << s1->getValue() << endl; });
					system("pause");
					break;
				}

			}
			else if (indexer == "titulo") {
				if (intAux2 != 2 && intAux2 != 3) {
					cin.ignore();
					cout << "Ingrese palabra clave ..." << endl;
					cin >> auxInfo;
					cout << endl;
				}
				switch (intAux2) {
				case 1:
					cout << ranked.buscar(new HashEntidad<Movie>(Movie(0, auxInfo, "", "", 0, "", 0, 0, 0, 0)))->getValue();
					system("pause");
					break;

				case 2:
					createStartTree();
					searchAlphabeticTree();
					eraseAlphabeticTree();
					system("pause");
					break;

				case 3:
					createEndTree();
					searchAlphabeticTree();
					eraseAlphabeticTree();
					system("pause");
					break;

				case 4:
					auxInfo = capitalizeString(auxInfo);
					lista.showObj([auxInfo](HashEntidad<Movie>* s1)->bool {
						return capitalizeString(s1->getValue().getTitle()).find(auxInfo) != string::npos; },
						[](HashEntidad<Movie>* s1) {cout << s1->getValue() << endl; });
					system("pause");
					break;

				case 5:
					auxInfo = capitalizeString(auxInfo);
					lista.showObj([auxInfo](HashEntidad<Movie>* s1)->bool { if (
						capitalizeString(s1->getValue().getTitle()).find(auxInfo) != string::npos) return false; else return true; },
						[](HashEntidad<Movie>* s1) {cout << s1->getValue() << endl; });
					system("pause");
					break;

				}

			}
			else if (indexer == "runtime") {
				if (intAux2 != 2 && intAux2 != 3) {
					cin.ignore();
					cout << "Ingrese palabra clave ..." << endl;
					cin >> auxInfo;
					cout << endl;
				}
				switch (intAux2) {
				case 1:
					cout << ranked.buscar(new HashEntidad<Movie>(Movie(0, "", "", "", 0, auxInfo, 0, 0, 0, 0)))->getValue();
					system("pause");
					break;

				case 2:
					createStartTree();
					searchAlphabeticTree();
					eraseAlphabeticTree();
					system("pause");
					break;

				case 3:
					createEndTree();
					searchAlphabeticTree();
					eraseAlphabeticTree();
					system("pause");
					break;

				case 4:
					lista.showObj([auxInfo](HashEntidad<Movie>* s1)->bool {
						return s1->getValue().getRuntime().find(auxInfo) != string::npos; },
						[](HashEntidad<Movie>* s1) {cout << s1->getValue() << endl; });
					system("pause");
					break;

				case 5:
					lista.showObj([auxInfo](HashEntidad<Movie>* s1)->bool { if (
						s1->getValue().getRuntime().find(auxInfo) != string::npos) return false; else return true; },
						[](HashEntidad<Movie>* s1) {cout << s1->getValue() << endl; });
					system("pause");
					break;

				}

			}

			break;

		case 6:
			lista.compare([](HashEntidad<Movie>* a1, HashEntidad<Movie>* a2) {return a1->getBackKey() == a2->getKey(); },
				[](HashEntidad<Movie>* obj) {cout << obj->getValue() << " " << obj->getBackKey() << " " << obj->getKey() << endl; });
			system("pause");
			break;

		}
	}
};


int main() {

	Console::WindowWidth = Console::LargestWindowWidth - 100;
	Console::WindowHeight = Console::LargestWindowHeight - 20;
	Control TF;
	short op;
	do {
		Console::Clear();
		cout << "************* MENU IMDB RANK ************" << endl;
		cout << "[1] - Registrar Pelicula" << endl;
		cout << "[2] - Mostrar Binary Tree de Peliculas" << endl;
		cout << "[3] - Modificar Pelicula" << endl;
		cout << "[4] - Mostrar Modificaciones de Pelicula" << endl;
		cout << "[5] - Filtrar Datos" << endl;
		cout << "[6] - Elementos Modificados a Partir de SHA265-Key" << endl;
		cout << "[0] - Salir" << endl;
		cout << "Ingrese Opcion:";
		cin >> op;
		TF.Menu(op);
	} while (op != '0');
	//test.backups();
	return 0;
}
