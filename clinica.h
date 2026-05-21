#ifndef CLINICA_H
#define CLINICA_H
#include <vector>
#include <string>
#include "medic.h"
#include "dermatolog.h"

class Clinica {
private:
    std::string numeClinica;
    std::vector<Medic*> listaMedici; // vector de pointeri la clasa de baza

public:

    Clinica(const std::string& nume);
    ~Clinica();
    Clinica(const Clinica& alta);
    Clinica& operator=(Clinica alta);

    void angajeazaMedic(Medic* m);

    void consultatie(const std::string& numeMedic, const std::string& afectiune);
    
    void Bilant(int luna) const;
    
    void angajeazaMedic();
    
    void actualizeazaFisierMedici(); 
    
    void afiseazaMedici() const;
  
    friend void swap(Clinica& unu, Clinica& doi) noexcept;
};

#endif