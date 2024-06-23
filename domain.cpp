#include "domain.h"

vector<string> splitLinie(const string& linie, char delimitator) {
	vector<string> atribute;
	stringstream stream(linie);
	string obiect;

	while (getline(stream, obiect, delimitator)) {
		atribute.push_back(obiect);
	}
	return atribute;
}

istream& operator>>(istream& input, Produs& produs) {
	string linie;
	getline(input, linie);
	if (linie.empty()) {
		return input;
	}

	vector<string> atribute = splitLinie(linie, ',');
	produs.setId(stoi(atribute[0]));
	produs.setNume(atribute[1]);
	produs.setTip(atribute[2]);
	produs.setPret(stod(atribute[3]));

	return input;
}

ostream& operator<<(ostream& output, const Produs& produs) {
	output << produs.getId() << "," << produs.getNume() << "," << produs.getTip() << "," << produs.getPret() << "\n";
	return output;
}

bool Produs::operator==(const Produs& produs) noexcept {
	return this->id == produs.id && this->nume == produs.nume && this->tip == produs.tip && this->pret == produs.pret;
}

bool cmpPret(const Produs& produs1, const Produs& produs2) {
	if (produs1.getPret() < produs2.getPret()) {
		return true;
	}
	return false;
}