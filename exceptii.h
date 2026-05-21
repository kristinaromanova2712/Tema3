#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <exception>
#include <string>

// clasa de baza a erorilor
class EroareClinica : public std::exception {
protected:
    std::string mesaj;
public:
    EroareClinica(const std::string& msg) : mesaj(msg) {}
    
    // functia care returneza textul erorii
    const char* what() const noexcept override {
        return mesaj.c_str();
    }
};
// 3 clase derivate

// functia bilant: luna ceruta este in viitor
class EroareLunaViitor : public EroareClinica {
public:
    EroareLunaViitor(int luna) : EroareClinica("EROARE : Bilantul nu se poate emite fiindca luna este în viitor.") {}
};

//  functia consultatie: medicul nu exista in baza de date
class EroareMedicInexistent : public EroareClinica {
public:
    EroareMedicInexistent(const std::string& nume) : EroareClinica("EROARE: Dr. " + nume + " nu lucreaza in aceasta clinica") {}
};

// functia consultatie: s-a introdus un medic necorespunzator afectiunii cerute
class EroareSpecializare : public EroareClinica {
public:
    EroareSpecializare(const std::string& nume, const std::string& specializareNecesara): EroareClinica( "EROARE: Dr. " + nume + " are alta specializare") {}
};

class EroareFormatLuna : public EroareClinica {
public:
    EroareFormatLuna(int luna) : EroareClinica("EROARE: Numarul lunii este invalid") {}
};
#endif