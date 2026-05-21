#ifndef SABLOANE_H
#define SABLOANE_H
#include <iostream>
#include <vector>
#include <string>
// functie sablon
template <typename T>
bool existaInColectie(const std::vector<T>& colectie, const T& elementCautat) {
    for (const auto& item : colectie) {
        if (item == elementCautat) {
            return true;
        }
    }
    return false;
}
// clasa sablon
template <typename T>
class RegistruGeneric {
private:
    std::string numeRegistru;
    std::vector<T> intrari;

public:
    RegistruGeneric(const std::string& nume) : numeRegistru(nume) {}
    void adaugaIntrare(const T& element) {
        intrari.push_back(element);
    }
    void afiseazaRegistru() const {
        std::cout << " "<<"\n";
        std::cout << numeRegistru <<"\n";
        std::cout << " "<<"\n";
        if (intrari.empty()) {
            std::cout << "registrul este gol\n";
        } else {
            for (size_t i = 0; i < intrari.size(); ++i) {
                std::cout << i + 1 << ". " << intrari[i] << "\n";
            }
        }
    }
    const std::vector<T>& getIntrari() const {
        return intrari;
    }
};

#endif