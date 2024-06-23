#include "repo.h"

void Repo::loadFile() {
	ifstream f(path);
	Produs produs{};

	while (f >> produs) {
		produse.push_back(produs);
	}

	f.close();
}

void Repo::saveFile() {
	ofstream g(path);

	for (const auto& p : produse) {
		g << p;
	}

	g.close();
}

void Repo::adaugaRepo(const Produs& produs) {
	for (const auto& p : getAll()) {
		if (p.getId() == produs.getId()) {
			throw RepoException("Produsul cu acest id deja exista!\n");
		}
	}
	produse.push_back(produs);
	saveFile();
}