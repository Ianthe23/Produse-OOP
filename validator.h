#pragma once

#include "domain.h"
#include "exceptions.h"

class Validator {
private:
	static void valideazaId(int id);
	
	static void valideazaNume(const string& nume);
	
	static void valideazaTip(const string& tip);

	static void valideazaPret(double pret);
public:
	static void valideazaProdus(const Produs& produs);
};