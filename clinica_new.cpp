#include "clinica.h"
#include "dermatolog.h"
#include "stomatolog.h"  
#include "cardiolog.h"  
#include "oftalmolog.h"
#include "exceptii.h"
#include <fstream>
#include <iostream>

Clinica::Clinica(const std::string& nume) : numeClinica(nume) {}
//copy and swap
void swap(Clinica& unu, Clinica& doi) noexcept {
    using std::swap;
    swap(unu.numeClinica, doi.numeClinica);
    swap(unu.listaMedici, doi.listaMedici);
}

//constructor de copiere
Clinica::Clinica(const Clinica& alta) : numeClinica(alta.numeClinica) {
    for (auto m : alta.listaMedici) {
        this->listaMedici.push_back(m->clone());
    }
}
//operator=
Clinica& Clinica::operator=(Clinica alta) {
    swap(*this, alta);
    return *this;
}
Clinica::~Clinica() {
    for (auto m : listaMedici) {
        delete m;
    }
    listaMedici.clear();
}
// adaugam medicul nou in vectorul de medici
void Clinica::angajeazaMedic(Medic* m) {
    listaMedici.push_back(m);
} 
// functie care adauga o consultatie in programul medicului
void Clinica::consultatie(const std::string& numeMedic, const std::string& afectiune) {
    //cautam afectiunea introdusa in fisierul afectiuni.txt
    std::ifstream Afectiuni("afectiuni.txt");
    if (!Afectiuni.is_open()) {
        // daca nu exista fisierul afectiuni.txt
        throw EroareClinica("Nu se poate accesa lista afectiunilor.");
    }

    std::string boala, specializareNecesara;
    bool gasitBoala = false;

    while (Afectiuni >> boala >> specializareNecesara) {
        if (boala == afectiune) {
            gasitBoala = true;
            break; 
        }
    }
    Afectiuni.close();

    // eroare ca nu s-a gasit boala
    if (!gasitBoala) {
        throw EroareClinica("Nu a fost gasita aceasta afectiune");
    }
    //cautam medicul introdus in fisierul medici.txt
    for (auto m : listaMedici) {
        if (m->getNume() == numeMedic) {
            bool specializareCorecta = false;

            if (specializareNecesara == "Dermatolog") {
                if (dynamic_cast<Dermatolog*>(m) != nullptr) specializareCorecta = true;
            } 
            else if (specializareNecesara == "Stomatolog") {
                if (dynamic_cast<Stomatolog*>(m) != nullptr) specializareCorecta = true;
            } 
            else if (specializareNecesara == "Cardiolog") {
                if (dynamic_cast<Cardiolog*>(m) != nullptr) specializareCorecta = true;
            }
            else if (specializareNecesara == "Oftalmolog") {
                if (dynamic_cast<Oftalmolog*>(m) != nullptr) specializareCorecta = true;
            }
            if (specializareCorecta) {
                m->consultatieNoua(); 
                actualizeazaFisierMedici();
                std::cout << "A fost introdusa in program consultatia la Dr. " << numeMedic << "\n";
                return; 
            } else {
                throw EroareSpecializare(numeMedic, specializareNecesara);
            }
        }
    }
    
    throw EroareMedicInexistent(numeMedic);
}

// functie care calculeaza nr de salarii care trebuie platite medicilor, atat din lunile trecute(bilantul este complet), cat si din luna curenta(partial)
void Clinica::Bilant(int luna) const {
    int lunaCurenta= 5; // luna curenta este aprilie
    if (luna < 1 || luna > 12) { // eroare daca luna nu e reala
        throw EroareFormatLuna(luna);
    } 
    if (luna > lunaCurenta ) {
        throw EroareLunaViitor(luna); // avem eroare daca luna e in viitor
    }
    
    if (luna < lunaCurenta) {
        std::cout << "Bilant complet\n";
        // citim din arhiva clinicii
        std::ifstream file("arhiva.txt");
        int l, cons;
        double bani;
        bool gasit = false;
    // bilant complet
        if (file.is_open()) {
            while (file >> l >> cons >> bani) {
                if (l == luna) {
                    std::cout << "Total consultatii: " << cons << "\n";
                    std::cout << "Total salarii: " << bani << " RON\n";
                    gasit = true;
                    break;
                }
            }
            file.close();
        }
        if (!gasit) std::cout << "Nu exista date salvate pentru luna " << luna << ".\n";

    } //bilant partial
    else if (luna == lunaCurenta) {
        std::cout << "Bilant partial\n";
        double totalBani = 0;
    
        for (auto m : listaMedici) {
            m->afisare();
            double salariu = m->calculeazaSalariu();
            std::cout << "De plata: " << salariu << " RON\n";
            totalBani += salariu;
        }
        
        std::cout << "Total salarii pana acum: " << totalBani << " RON\n";
    } 
}

// suprascrie fisierul medici.txt, adaugand modificarea facuta, ca datele sa nu se piarda la inchiderea programului
void Clinica::actualizeazaFisierMedici() {
    std::ofstream file("medici.txt"); 
    
    for (auto m : listaMedici) {
        std::string spec = "Medic";
        
        if (dynamic_cast<Dermatolog*>(m)) spec = "Dermatolog";
        else if (dynamic_cast<Stomatolog*>(m)) spec = "Stomatolog";
        else if (dynamic_cast<Cardiolog*>(m)) spec = "Cardiolog";
        else if (dynamic_cast<Oftalmolog*>(m)) spec = "Oftalmolog";

        file << spec << " " 
             << m->getNume() << " " 
             << m->getPrenume() << " " 
             << m->getSalariuBaza() << " " 
             << m->getNrConsultatiiActuale() << "\n";
    }
    file.flush();
    file.close();
}
void Clinica::afiseazaMedici() const {
    if (listaMedici.empty()) {
        std::cout << "Clinica nu are niciun medic angajat \n";
        return;
    }
    for (auto m : listaMedici) {
        m->afisare(); 
    }
}