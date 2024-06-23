#include "validator.h"

void Validator::valideazaId(int id) {
	if (id < 0) {
		throw ValidatorException("Id invalid!\n");
	}
}

void Validator::valideazaNume(const string& nume) {
	if (nume.empty()) {
		throw ValidatorException("Nume invalid!\n");
	}
}

void Validator::valideazaTip(const string& tip) {
	if (tip.empty()) {
		throw ValidatorException("Tip invalid!\n");
	}
}

void Validator::valideazaPret(double pret) {
	if (pret < 1 || pret > 100) {
		throw ValidatorException("Pret invalid!\n");
	}
}

void Validator::valideazaProdus(const Produs& produs) {
	string exceptii;
	const int id = produs.getId();
	const string& nume = produs.getNume();
	const string& tip = produs.getTip();
	const double pret = produs.getPret();

	try {
		valideazaId(id);
	}
	catch (ValidatorException& mesaj) {
		exceptii += mesaj.get_mesaj();
	}

	try {
		valideazaNume(nume);
	}
	catch (ValidatorException& mesaj) {
		exceptii += mesaj.get_mesaj();
	}

	try {
		valideazaTip(tip);
	}
	catch (ValidatorException& mesaj) {
		exceptii += mesaj.get_mesaj();
	}

	try {
		valideazaPret(pret);
	}
	catch (ValidatorException& mesaj) {
		exceptii += mesaj.get_mesaj();
	}

	if (!exceptii.empty()) {
		throw ValidatorException(exceptii);
	}
}