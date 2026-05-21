#ifndef STOMATOLOG_H
#define STOMATOLOG_H
#include "medic.h"

class Stomatolog : public Medic {
public:
    Stomatolog(const std::string& numeMedic, const std::string& prenumeMedic, double salariu, int c);
    
    double calculeazaSalariu() const override;
    Medic* clone() const override;

protected:
    void afisareDetaliiSpecifice() const override;
};

#endif