#include "dermatolog.h"

// construim dermatologul apeland la constructorul din clasa de baza medic
Dermatolog::Dermatolog(const std::string& numeMedic, const std::string& prenumeMedic, double salariu, int c): Medic(numeMedic, prenumeMedic, salariu) { 
    this->nrConsultatii = c; 
}
// calculam salariul
double Dermatolog::calculeazaSalariu() const {
    // dermatologul primeste 500 de lei pe consultatie
    return salariuBaza + (nrConsultatii * 500.0);
}
// clona
Medic* Dermatolog::clone() const {
    return new Dermatolog(*this);
}

// afișare virtuală, interfață non-virtuală
void Dermatolog::afisareDetaliiSpecifice() const {
    std::cout << "Specializare: dermatolog ; Consultatii luna aceasta: " << nrConsultatii
              << "Salariul final: " << calculeazaSalariu() << " RON";
}