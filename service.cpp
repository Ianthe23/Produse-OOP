#include "service.h"

void Service::adauga(int id, const string& nume, const string& tip, double pret) {
	Produs produs{ id, nume, tip, pret };
	validator.valideazaProdus(produs);
	repo.adaugaRepo(produs);
	notify();
}

vector<Produs> Service::sorteaza() {
	auto sorted = repo.getAll();
	std::sort(sorted.begin(), sorted.end(), cmpPret);
	return sorted;
}

vector<int> Service::vocale() {
	vector<int> vocale;
	for (const auto& p : sorteaza()) {
		int nr = 0;
		for (int j = 0; j < p.getNume().size(); ++j) {
			if (p.getNume()[j] == 'a' || p.getNume()[j] == 'e' || p.getNume()[j] == 'i' || p.getNume()[j] == 'o' || p.getNume()[j] == 'u') {
				nr++;
			}
		}
		vocale.push_back(nr);
	}
	return vocale;
}

vector<Produs> Service::filtreaza(double pret) {
	vector<Produs> filtered;

	const auto allProduse = repo.getAll();
	copy_if(allProduse.begin(), allProduse.end(), std::back_inserter(filtered),
		[pret](const Produs& produs) noexcept {
			return produs.getPret() <= pret;
		});

	return filtered;
}

map<string, int> Service::tipuri() {
	map<string, int> tipuri;
	for (const auto& p : getProduse()) {
		if (tipuri.find(p.getTip()) == tipuri.end()) {
			tipuri[p.getTip()] = 1;
		}
		else {
			tipuri[p.getTip()]++;
		}
	}
	return tipuri;
}

int Service::nr_tipuri(const string& tip) {
	return tipuri()[tip];
}