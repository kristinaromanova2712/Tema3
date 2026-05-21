#ifndef CARDIOLOG_H
#define CARDIOLOG_H

#include "medic.h"

class Cardiolog : public Medic {
public:
    Cardiolog(const std::string& numeMedic, const std::string& prenumeMedic, double salariu, int c);
    
    double calculeazaSalariu() const override;
    Medic* clone() const override;

protected:
    void afisareDetaliiSpecifice() const override;
};

#endif