#ifndef OFTALMOLOG_H
#define OFTALMOLOG_H

#include "medic.h"

class Oftalmolog : public Medic {
public:
    Oftalmolog(const std::string& numeMedic, const std::string& prenumeMedic, double salariu, int c);
    
    double calculeazaSalariu() const override;
    Medic* clone() const override;

protected:
    void afisareDetaliiSpecifice() const override;
};

#endif