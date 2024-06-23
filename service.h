#pragma once

#include "repo.h"
#include "validator.h"
#include "observer.h"

#include <functional>
#include <algorithm>
#include <map>

using std::function;
using std::map;

class Service :public Observable {
private:
	Repo& repo;
	Validator validator;

public:
	Service(Repo& r, Validator& v) : repo(r), validator(v) {

	};

	Service(Service& other) = delete;

	void adauga(int id, const string& nume, const string& tip, double pret);
	vector<Produs> sorteaza();
	vector<Produs> filtreaza(double pret);
	vector<int> vocale();
	map<string, int> tipuri();
	int nr_tipuri(const string& tip);

	vector<Produs>& getProduse() {
		return repo.getAll();
	}
};
