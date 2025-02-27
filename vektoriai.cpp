#include "functions.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>


double Vidurkis(const std::vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0.0;
    double suma = 0.0;
    for (int pazymys : pazymiai) suma += pazymys;
    return suma / pazymiai.size();
}

double apskaiciuotiMediana(std::vector<int> pazymiai) {
    if (pazymiai.empty()) return 0.0;
    std::sort(pazymiai.begin(), pazymiai.end());
    size_t dydis = pazymiai.size();
    if (dydis % 2 == 0) {
        return (pazymiai[dydis / 2 - 1] + pazymiai[dydis / 2]) / 2.0;
    } else {
        return pazymiai[dydis / 2];
    }
}

void gen_name(std::string& vardas, std::string& pavarde) {
    std::vector<std::string> vardai = {"Pijus", "Justas", "Kostas", "Petras"};
    std::vector<std::string> pavardes = {"Savanevicius", "Andru", "Baranauskas", "Dovydaitis"};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, vardai.size() - 1);

    vardas = vardai[distr(gen)];
    pavarde = pavardes[distr(gen)];
}

void Duom(std::vector<Student>& studentai) {
    std::ifstream rf("studentai10000.txt");
    if (!rf) {
        std::cerr << "Failas nerastas\n";
        return;
    }
    std::string var, pav, nd;
    rf >> var >> pav;
    int kiek = 0;
    
    while (rf >> nd && nd != "Egz.") {
        kiek = kiek + 1;
    }
    Student studentas;
    while (rf >> studentas.vardas >> studentas.pavarde) {
        studentas.namuDarbai.clear();
        int pazymys;
        for (int i = 0; i < kiek; i++) {
            rf >> pazymys;
            studentas.namuDarbai.push_back(pazymys);
        }
        rf >> studentas.egz;

        studentai.push_back(studentas);
    }
}

void Rez(const std::vector<Student>& studentai) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-----------------------------------------------------------\n";
    std::cout << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(25) << "Galutinis (vid.)  Galutinis (med.)\n";
    std::cout << "-----------------------------------------------------------\n";

    for (const auto& studentas : studentai) {
        double galutinis_v = Vidurkis(studentas.namuDarbai) * 0.4 + studentas.egz * 0.6;
        double galutinis_m = apskaiciuotiMediana(studentas.namuDarbai) * 0.4 + studentas.egz * 0.6;

        std::cout << std::setw(15) << studentas.vardas 
                  << std::setw(15) << studentas.pavarde 
                  << std::setw(15) << galutinis_v
                  << std::setw(15) << galutinis_m << "\n";
    }
}

int main() {
    std::vector<Student> studentai;
    Duom(studentai);
    Rez(studentai);
    return 0;
}
