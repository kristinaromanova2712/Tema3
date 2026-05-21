#include "medic.h"
int Medic::nrMedici=0;

Medic::Medic(const std::string& numeMedic, const std::string& prenumeMedic, double salariu)
    : nume(numeMedic), prenume(prenumeMedic), salariuBaza(salariu) {
        nrMedici++;
}

Medic::~Medic() {
    nrMedici--;
}
void Medic::afisare() const {
    std::cout << "Dr. " << nume << " " << prenume 
              << "Salariu baza: " << salariuBaza << " RON";
    
    afisareDetaliiSpecifice(); 
    std::cout << "\n";
}
int Medic::getnrMedici() {
    return nrMedici;
}