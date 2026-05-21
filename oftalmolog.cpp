#include "oftalmolog.h"
#include <iostream>

Oftalmolog::Oftalmolog(const std::string& numeMedic, const std::string& prenumeMedic, double salariu, int c)
    : Medic(numeMedic, prenumeMedic, salariu) {
    this->nrConsultatii = c;
}

double Oftalmolog::calculeazaSalariu() const {
    return salariuBaza + (nrConsultatii * 200.0);
}

Medic* Oftalmolog::clone() const {
    return new Oftalmolog(*this);
}

void Oftalmolog::afisareDetaliiSpecifice() const {
    std::cout << "Specializare: Oftalmolog ; Consultatii luna aceasta: " << nrConsultatii 
              << " ; Salariul final: " << calculeazaSalariu() << " RON";
}
