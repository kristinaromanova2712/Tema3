// clasa derivata dermatolog
#ifndef DERMATOLOG_H
#define DERMATOLOG_H
#include "medic.h"

// dermatologUL mosteneste clasa medic
class Dermatolog : public Medic {
private:

public:
    Dermatolog(const std::string& numeMedic, const std::string& prenumeMedic, double salariu, int c);
    double calculeazaSalariu() const override; // implementam in clasa derivata functia virtuala din clasa de baza
    Medic* clone() const override; // clona 

protected:
    // afișare virtuală, interfață non-virtuală
    void afisareDetaliiSpecifice() const override;
};

#endif