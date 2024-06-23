#pragma once

#include "domain.h"
#include "exceptions.h"
#include <fstream>

class Repo {
	vector<Produs> produse;
	string path;
	void loadFile();
	void saveFile();

public:
	Repo(const string p) : path(p) {
		loadFile();
	}

	Repo(Repo& other) = delete;

	void adaugaRepo(const Produs& produs);

	vector<Produs>& getAll() {
		return produse;
	}
};