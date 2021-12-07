#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "SHA265.h"
#include "Pila.h"
#include "DoubleLinkedList.h"
using namespace std;
using namespace System;

template<typename T>
class alphabeticEntity {
	char character;
	BlockChain<T> list;
	string print;
	
public:
	alphabeticEntity(char character) {
		this->character = character;
	}

	alphabeticEntity() {}
	BlockChain<T>& getList() { return this->list; }
	char getChar() { return this->character; }

	void addToList(T value) {list.insertarFinal(value); }

	void makeString() {
		//this->print = list.returnString([](T a1) {return a1->getValue().toString() + "\n"; });
		this->print = list.returnString([](T a1) {return a1->buffer.str() + "\n"; });
	}

	void eraseList() {this->list.deleteAllNodes(); }

	friend ostream& operator<<(ostream& os, const alphabeticEntity& r) {
		os << r.character << endl << r.print;
		return os;
	}

	bool operator<(const alphabeticEntity& r) {	return this->character < r.character; }

	bool operator>=(const alphabeticEntity& r) {return this->character >= r.character; }

	bool operator>(const alphabeticEntity& r) {	return this->character > r.character;}

	bool operator==(const alphabeticEntity& r) {return this->character == r.character; }

};

template<typename T>
class HashEntidad {
private:
	string key;
	string backKey;
	T value;
	Pila<T> backUps;

public:
	std::stringstream buffer;
	HashEntidad(string backKey, T value) {
		
		this->backKey = backKey;
		this->value = value;
		buffer << value;
		this->key = SHA256::cifrar(backKey + SHA256::cifrar(buffer.str()));
	}

	HashEntidad(T value) {
		this->value = value;
	}

	string getKey() { return key; }
	string getBackKey() { return backKey; }
	void setKey(string key) { this->key = key; }
	T& getValue() { return value; }
	void setValue(T value) { delete this->value; this->value = value; }
	
	Pila<T>& getPila() { return backUps; }

	void reloadHash() {
		buffer << value;
		this->key = SHA256::cifrar(backKey + SHA256::cifrar(buffer.str()));

	}

	void uptadeHash(string BackBlockchain) {
		this->backKey = BackBlockchain;
		this->key = SHA256::cifrar(backKey + SHA256::cifrar(buffer.str()));
	}

	void doBackUp() { this->backUps.push(value); }
};

class Movie {
	short rank, year, metascore;
	string title, genre, director, runtime;
	float rating, revenue;
	int votes;
public:
	
	Movie(short rank = 0, string title = "", string genre = "", string director = "", short year = 0, string runtime = "",
		float rating = 0, int votes = 0, float revenue = 0, short metascore = 0) {

		this->rank = rank;
		this->title = title;
		this->genre = genre;
		this->director = director;
		this->year = year;
		this->runtime = runtime;
		this->rating = rating;
		this->votes = votes;
		this->revenue = revenue;
		this->metascore = metascore;
	}

	short getRank() { return this->rank; }
	short getYear() { return this->year; }
	short getMetaScore() { return this->metascore; }
	string getTitle() { return this->title; }
	string getGenre() { return this->genre; }
	string getDirector() { return this->director; }
	string getRuntime() { return this->runtime; }
	float getRating() { return this->rating; }
	float getRevenue() { return this->revenue; }
	int getVotes() { return this->votes; }


	void setRank(short rank) { this->rank = rank; }
	void setYear(short year) { this->year = year; }
	void setMetaScore(short metascore) { this->metascore = metascore; }
	void setTitle(string title) { this->title = title; }
	void setGenre(string genre) { this->genre = genre; }
	void setDirector(string director) { this->director = director; }
	void setRuntime(string runtime) { this->runtime= runtime; }
	void setRating(float rating) { this->rating = rating; }
	void setRevenue(float revenue) { this->revenue = revenue; }
	void setVotes(int votes) { this->votes = votes; }

	bool Check(function<bool(string)> cmp) {

		if (cmp(to_string(rank)) || cmp(to_string(year)) || cmp(to_string(metascore)) || cmp(title) || cmp(genre) || cmp(director) ||
			cmp(runtime) || cmp(to_string(rating)) || cmp(to_string(revenue)) || cmp(to_string(votes)))
			return true;
		else
			return false;

	}
	
	friend ostream& operator<<(ostream& os, const Movie& r) {
		os << std::setw(7) << r.votes << std::setw(5) << r.rank << std::setw(40) << r.title << std::setw(28) <<
			r.genre << std::setw(20) <<
			r.director << "  " << r.year << std::setw(10) << r.runtime << std::setw(5) <<
			r.rating << std::setw(7) << r.revenue << std::setw(4) << r.metascore;
		return os;
	}

	bool operator<(const Movie& r) {
		return this->votes < r.votes;
	}

	bool operator>=(const Movie& r) {
		return this->votes >= r.votes;
	}


	string toString() {
		std::stringstream stream;
		stream << fixed << setprecision(2) << " " << rating << " " << votes << " " << revenue << " " << metascore;
		string Sales = stream.str();
		return to_string(rank) + " " + title + " " + genre + " " + director + " " + to_string(year) + " " +
			runtime + " " + Sales + " ";
	}

};