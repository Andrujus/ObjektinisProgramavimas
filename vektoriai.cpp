#include "functions.h"

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
    std::ifstream rf("kursiokai.txt");
    if (!rf) {
        std::cerr << "Failas nerastas\n";
        return;
    }
    std::string eilute;
    std::getline(rf, eilute);
    while(std::getline(rf, eilute)){
        Student studentas;
        rf>>studentas.vardas>>studentas.pavarde;
        int pazymys;
        for (int i = 0; i < 5; i++){
            rf>>pazymys;
            studentas.namuDarbai.push_back(pazymys);
        }
        rf>>studentas.egz;
        studentai.push_back(studentas);
    }
}

void Rez(const std::vector<Student>& studentai, bool n_vid) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-----------------------------------------------------------\n";
    if (n_vid)
        std::cout << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(25) << "Galutinis (vid.)\n";
    else
        std::cout << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(25) << "Galutinis (med.)\n";
    std::cout << "-----------------------------------------------------------\n";

    for (const auto& studentas : studentai) {
        double galutinis;
        if (n_vid) {
            galutinis = Vidurkis(studentas.namuDarbai) * 0.4 + studentas.egz * 0.6;
        } else {
            galutinis = apskaiciuotiMediana(studentas.namuDarbai) * 0.4 + studentas.egz * 0.6;
        }

        std::cout << std::setw(15) << studentas.vardas 
                  << std::setw(15) << studentas.pavarde 
                  << std::setw(15) << galutinis << "\n";
    }
}

int main() {
    std::vector<Student> studentai;
    Duom(studentai);

    std::string vid;
    std::cout << "V - vidurkis, M - mediana: ";
    std::cin >> vid;

    if (vid == "V" || vid == "v") {
        Rez(studentai, true);
    } else {
        Rez(studentai, false);
    }

    return 0;
}
