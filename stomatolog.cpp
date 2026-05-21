#include "stomatolog.h"
#include <iostream>
Stomatolog::Stomatolog(const std::string& numeMedic, const std::string& prenumeMedic, double salariu, int c)
    : Medic(numeMedic, prenumeMedic, salariu) {
    this->nrConsultatii = c;
}
double Stomatolog::calculeazaSalariu() const {
    // stomatologul primeste 250 de lei pe consultatie
    return salariuBaza + (nrConsultatii * 250.0);
}

Medic* Stomatolog::clone() const {
    return new Stomatolog(*this);
}

void Stomatolog::afisareDetaliiSpecifice() const {
    std::cout << "Specializare: Stomatolog ; Consultatii luna aceasta: " << nrConsultatii 
              << " ; Salariul final: " << calculeazaSalariu() << " RON";
}