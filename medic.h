// clasa de baza MEDIC
#ifndef MEDIC_H
#define MEDIC_H
#include <iostream>
#include <string>


class Medic {
protected:
    std::string nume;
    std::string prenume;
    double salariuBaza;
    int nrConsultatii;
    virtual void afisareDetaliiSpecifice() const = 0; // fucntie virtuala pura
    static int nrMedici; 

public:
    
    Medic(const std::string& n, const std::string& p, double sal);
    virtual void consultatieNoua() { // functia care adauga o consultatie noua la un medic
        nrConsultatii++;
    }
    virtual double calculeazaSalariu() const = 0; // functie virtuala pura specifica temei
    virtual Medic* clone() const = 0; // constructor virtual
    void afisare() const; // interfata non virtuala
    std::string getNume() const { return nume; }
    virtual ~Medic();
    static int getnrMedici();
    std::string getPrenume() const { return prenume; }
    double getSalariuBaza() const { return salariuBaza; }
    int getNrConsultatiiActuale() const { return nrConsultatii; }
    
};

#endif