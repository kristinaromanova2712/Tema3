#ifndef MEDIC_FACTORY_H
#define MEDIC_FACTORY_H

#include <string>
#include "medic.h"
#include "dermatolog.h"
#include "stomatolog.h"
#include "cardiolog.h"
#include "oftalmolog.h"

class MedicFactory {
public:
    static Medic* creeazaMedic(const std::string& specializare, const std::string& nume, const std::string& prenume, double salariu, int consultatii=0) {
        
        if (specializare=="Dermatolog") {
            return new Dermatolog(nume, prenume, salariu, consultatii);
        } 
        else if (specializare=="Stomatolog") {
            return new Stomatolog(nume, prenume, salariu, consultatii);
        } 
        else if (specializare=="Cardiolog") {
            return new Cardiolog(nume, prenume, salariu, consultatii);
        } 
        else if (specializare=="Oftalmolog") {
            return new Oftalmolog(nume, prenume, salariu, consultatii);
        }
        return nullptr; 
    }
};
#endif