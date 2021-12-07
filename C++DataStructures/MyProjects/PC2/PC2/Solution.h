#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
using namespace System;

template<typename T>
class HashEntidad {
private:
	string key;
	T value;

public:
	HashEntidad(string key, T value) {
		this->key = key;
		this->value = value;
	}
	string getKey() { return key; }
	void setKey(string key) { this->key = key; }
	T getValue() { return value; }
	void setValue(T value) { delete this->value; this->value = value; }
};

class Game {
	short year, rank;
	string name, platform, genre, publisher;
	float NA_Sales, EU_Sales, JP_Sales, Global_Sales;
public:

	Game(short rank=0, string name="", string platform="", short year=0, string genre="", string publisher="",
		float NA_Sales=0, float EU_Sales=0, float JP_Sales=0, float Global_Sales=0) {

		this->rank = rank;
		this->name = name;
		this->platform = platform;
		this->year = year;
		this->genre = genre;
		this->publisher = publisher;
		this->NA_Sales = NA_Sales;
		this->EU_Sales = EU_Sales;
		this->JP_Sales = JP_Sales;
		this->Global_Sales = Global_Sales;
	}

	short getYear() { return this->year; }
	short getRank() { return this->rank; }
	string getName() { return this->name; }
	string getPlatform() { return this->platform; }
	string getGenre() { return this->genre; }
	string getPublisher() { return this->publisher; }
	float getNaSales() { return this->NA_Sales; }
	float getEuSales() { return this->EU_Sales; }
	float getJpSales() { return this->JP_Sales; }
	float getGlobalSales() { return this->Global_Sales; }

	void setYear(short year) { this->year = year; }
	void setRank(short rank) { this->rank = rank; }
	void setName(string name) { this->name = name; }
	void setPlatform(string platform) { this->platform = platform; }
	void setGenre(string genre) { this->genre = genre; }
	void setPublisher(string publisher) { this->publisher = publisher; }
	void setNaSales(float NA_Sales) { this->NA_Sales = NA_Sales; }
	void setEuSales(float EU_Sales) { this->EU_Sales = EU_Sales; }
	void setJpSales(float JP_Sales) { this->JP_Sales = JP_Sales; }
	void setGlobalSales(float Global_Sales) { this->Global_Sales = Global_Sales; }

	friend ostream& operator<<(ostream& os, const Game& r) {
		os << r.rank << " " << r.name << " " << r.platform << " " <<
			r.year << " " << r.genre << " " << r.publisher << " " <<
			r.NA_Sales << " " << r.EU_Sales << " " << r.JP_Sales << " " << r.Global_Sales << endl;
		return os;
	}

	bool operator<(const Game& r) {
		return this->rank < r.rank;
	}
	bool operator>=(const Game& r) {
		return this->rank >= r.rank;
	}

	string toString() {
		std::stringstream stream;
		stream << fixed << setprecision(2) << NA_Sales << " " << EU_Sales << " " << JP_Sales << " " << Global_Sales;
		string Sales = stream.str();
		return to_string(rank) + " " + name + " " + platform + " " + to_string(year) + " " + genre + " " +
			publisher + " " + Sales + "\n";
	}

};