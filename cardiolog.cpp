#include "cardiolog.h"
#include <iostream>

Cardiolog::Cardiolog(const std::string& numeMedic, const std::string& prenumeMedic, double salariu, int c)
    : Medic(numeMedic, prenumeMedic, salariu) {
    this->nrConsultatii = c;
}

double Cardiolog::calculeazaSalariu() const {
    return salariuBaza + (nrConsultatii * 300.0);
}

Medic* Cardiolog::clone() const {
    return new Cardiolog(*this);
}

void Cardiolog::afisareDetaliiSpecifice() const {
    std::cout << "Specializare: Cardiolog ; Consultatii luna aceasta: " << nrConsultatii 
              << " ; Salariul final: " << calculeazaSalariu() << " RON";
}