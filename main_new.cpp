#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clinica.h"
#include "medic.h"
#include "exceptii.h"
#include "medic_factory.h"
#include "sabloane.h"

int main() {
    std::cout << "      Program management clinica Medlife      \n";
    Clinica Medlife("Medlife");
    //instantierea clasei sablon(string si int) 
    RegistruGeneric<std::string> jurnalActiuni("jurnal de activitati");
    RegistruGeneric<int> luniVerificate("istoric luni verificate");
    jurnalActiuni.adaugaIntrare("Sistemul clinicii a fost pornit"); //am adaugat prima activitate
    std::ifstream fisierMedici("medici.txt");
    std::string specializare, nume, prenume;
    double salariu;
    int consultatii;
    // implementam factory pattern si folosim medic factory-cream automat un medic de tipul potrivit
    while (fisierMedici >> specializare >> nume >> prenume >> salariu >> consultatii) {
        Medic* medicNou = MedicFactory::creeazaMedic(specializare, nume, prenume, salariu, consultatii);
        if (medicNou != nullptr) {
            Medlife.angajeazaMedic(medicNou);
        }
    }
    fisierMedici.close();

    std::cout << "Bine ati venit!\n";
    std::cout << "Medici angajati: " << Medic::getnrMedici() << "\n";
    
    int optiune;
    do { 
        std::cout << "\n1. Adauga o consultatie\n";
        std::cout << "2. Afiseaza bilantul lunar\n";
        std::cout << "3. Angajare medic nou\n";
        std::cout << "4. Afiseaza lista medici\n";
        std::cout << "5. Afiseaza jurnalul si verifica istoricul\n";
        std::cout << "0. Iesire din program\n";
        std::cout << "Apasati tasta corespunzatoare: ";
        std::cin >> optiune;
        switch (optiune) {
            case 1: {
                std::string numeMedic, afectiune;
                std::cout << "Afectiune pacient: "; std::cin >> afectiune;
                std::cout << "Nume medic: "; std::cin >> numeMedic;
                
                try {
                    Medlife.consultatie(numeMedic, afectiune);
                    jurnalActiuni.adaugaIntrare("S-a adaugat o consultatie la Dr. " + numeMedic); 
                } 
                catch (const EroareClinica& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }
            case 2: {
                int luna;
                std::cout << "Introduceti luna (1-12): "; std::cin >> luna;
                
                try {
                    Medlife.Bilant(luna);
                    luniVerificate.adaugaIntrare(luna); //adaugam luna veriicata in vectorul din clasa template
                    jurnalActiuni.adaugaIntrare("S-a afisat bilantul pt luna " + std::to_string(luna));
                } 
                catch (const EroareFormatLuna& e) {
                    std::cout << e.what() << "\n";
                }
                catch (const EroareLunaViitor& e) {
                    std::cout  << e.what() << "\n";
                }
                catch (const EroareClinica& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }
            case 3: {
                std::string spec, nume, prenume;
                double salariu;
    
                std::cout << "Specializare (Dermatolog/Stomatolog/Cardiolog/Oftalmolog): "; 
                std::cin >> spec;
                std::vector<std::string> specValide = {"Dermatolog", "Stomatolog", "Cardiolog", "Oftalmolog"};
                 //folosind functia sablon verificam daca specializarea exista in baza de date a clinicii
                if (!existaInColectie(specValide, spec)) {
                    std::cout << "EROARE: Nu avem aceasta specialitate!\n";
                    break;
                }
                std::cout << "Nume: "; std::cin >> nume;
                std::cout << "Prenume: "; std::cin >> prenume;
                std::cout << "Salariu de baza: "; 
    
                if (!(std::cin >> salariu)) {
                    std::cout << "EROARE: Salariu invalid!\n";
                    std::cin.clear(); 
                    std::cin.ignore(1000, '\n');
                    break;
                }// folosim creeazaMedic pt angajarea unui nou medic
                Medic* medicNou = MedicFactory::creeazaMedic(spec, nume, prenume, salariu, 0);
                // verificam daca medic factory a reusit sa creeze un obiect de tipul potrivit si nu da eroare
                if (medicNou != nullptr) {
                    Medlife.angajeazaMedic(medicNou);
                    Medlife.actualizeazaFisierMedici();
                    std::cout << "Dr. " << nume << " a fost angajat!\n";
                    jurnalActiuni.adaugaIntrare("A fost angajat Dr. " + nume + " (" + spec + ")"); 
                } else {
                    std::cout << "EROARE: Crearea medicului a esuat.\n";
                }
                break;
            }
            case 4: {
                Medlife.afiseazaMedici();
                break;
            }
            case 5: {
                // afisam jurnalul activitatilor
                jurnalActiuni.afiseazaRegistru();

               int lunaCautata;
                std::cout << "vezi daca luna a fost deja verificata: ";
                std::cin >> lunaCautata;

            if (existaInColectie(luniVerificate.getIntrari(), lunaCautata)) {
                    std::cout << "Bilantul pt luna " << lunaCautata << " a fost deja verificat\n";
            } else {
                    std::cout << "Bilantul pt luna " << lunaCautata << " NU a fost verificat inca\n";
            }
            break; 
            }
            case 0:
                break;
            default:
                std::cout << "Optiune invalida\n";
        }
    } while (optiune != 0);

    return 0;
}