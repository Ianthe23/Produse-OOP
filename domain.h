#pragma once

#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> splitLinie(const string& linie, char delimitator);

class Produs {
private:
	int id;
	string nume;
	string tip;
	double pret;

public:
	Produs() {
		id = -1;
		nume = "";
		tip = "";
		pret = 0;
	}

	Produs(int id, const string& nume, const string& tip, double pret) {
		this->id = id;
		this->nume = nume;
		this->tip = tip;
		this->pret = pret;
	}

	Produs& operator=(const Produs& other) = default;

	//getters
	int getId() const {
		return id;
	}
	const string& getNume() const {
		return nume;
	}
	const string& getTip() const {
		return tip;
	}
	double getPret() const {
		return pret;
	}

	//setters
	void setId(int id) {
		this->id = id;
	}
	void setNume(const string& nume) {
		this->nume = nume;
	}
	void setTip(const string& tip) {
		this->tip = tip;
	}
	void setPret(double pret) {
		this->pret = pret;
	}

	friend istream& operator>>(istream& input, Produs& produs);
	bool operator==(const Produs& produs) noexcept;
};
bool cmpPret(const Produs& produs1, const Produs& produs2);
ostream& operator<<(ostream& output, const Produs& produs);