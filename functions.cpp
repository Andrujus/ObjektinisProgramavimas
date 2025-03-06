#include "functions.h"
#include <iostream>
#include <fstream>
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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 10);

    std::string kitas_stud = "T";
    while (kitas_stud == "T" || kitas_stud == "t") {
        Student studentas;
        std::cout << "1 - įvesti pažymius rankiniu būdu\n2 - generuoti atsitiktinius pažymius\n3 - generuoti vardus, pavardes ir pazymius\n4 - nuskaityti is failo\n5 - generuoti failus\n6 - baigti\n";
        int ch;
        std::cin >> ch;
        if (ch == 5) break;
        if (ch == 4) {
            try {
                std::ifstream rf("studentai10000.txt");
                if (!rf) throw std::runtime_error("Failas nerastas");

                std::string var, pav, nd;
                rf >> var >> pav;
                int kiek = 0;

                while (rf >> nd && nd != "Egz.") {
                    kiek++;
                }

                while (rf >> studentas.vardas >> studentas.pavarde) {
                    studentas.namuDarbai.clear();
                    int pazymys;

                    for (int i = 0; i < kiek; i++) {
                        if (!(rf >> pazymys)) 
                            throw std::runtime_error("Klaida skaitant pažymius iš failo.");
                        studentas.namuDarbai.push_back(pazymys);
                    }

                    if (!(rf >> studentas.egz))
                        throw std::runtime_error("Klaida skaitant egzamino pažymį iš failo.");
                    
                    studentai.push_back(studentas);
                }

            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
        if (ch == 1) {
            try{
            std::cout << "Įveskite studento vardą: ";
            std::cin >> studentas.vardas;
            if (std::isdigit(studentas.vardas[0])) throw std::runtime_error("Vardas negali prasidėti skaičiumi");
            std::cout << "Įveskite studento pavardę: ";
            std::cin >> studentas.pavarde;
            if (std::isdigit(studentas.pavarde[0])) throw std::runtime_error("Pavarde negali prasidėti skaičiumi");
            std::cout << "Įveskite namų darbų pažymius (įveskite -1, kad baigtumėte): ";
            int pazymys;
            studentas.namuDarbai.clear();
            while (true) {
                std::cin >> pazymys;
                if (pazymys < -1 || pazymys > 10) throw std::runtime_error("Pažymys turi būti intervale nuo 1 iki 10");
                if (pazymys == -1) break;
                studentas.namuDarbai.push_back(pazymys);
            }
            if (std::cin.fail()) throw std::runtime_error("Neteisingas pažymys");
            std::cout << "Įveskite egzamino rezultatą: ";
            std::cin >> studentas.egz;
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
            
        }
        if (ch == 2) {
            try{
            std::cout << "Įveskite studento vardą: ";
            std::cin >> studentas.vardas;
            if (std::isdigit(studentas.vardas[0])) throw std::runtime_error("Vardas negali prasidėti skaičiumi");
            std::cout << "Įveskite studento pavardę: ";
            std::cin >> studentas.pavarde;
            if (std::isdigit(studentas.pavarde[0])) throw std::runtime_error("Pavarde negali prasidėti skaičiumi");
            studentas.namuDarbai.clear();
            for (int i = 0; i < 5; i++) {
                studentas.namuDarbai.push_back(distr(gen));
            }
            studentas.egz = distr(gen);
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
            
        }
        if (ch == 3) {
            gen_name(studentas.vardas, studentas.pavarde);
            studentas.namuDarbai.clear();
            for (int i = 0; i < 5; i++) {
                studentas.namuDarbai.push_back(distr(gen));
            }
            studentas.egz = distr(gen);
        }
        studentai.push_back(studentas);
        std::cout << "Ar norite tęsti? (T - taip, N - ne): ";
        std::cin >> kitas_stud;
    }
}

void Rez(std::vector<Student>& studentai) {
    std::cout << "Pasirinkite rikiavimo būdą:\n1 - pagal vardą\n2 - pagal pavardę\n3 - pagal vidurkį\n4 - pagal medianą\n";
    int ch;
    std::cin >> ch;
    switch (ch) {
        case 1:
            std::sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
                return a.vardas < b.vardas;
            });
            break;
        case 2:
            std::sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
                return a.pavarde < b.pavarde;
            });
            break;
        case 3:
            std::sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
                return (Vidurkis(a.namuDarbai) * 0.4 + a.egz * 0.6) < (Vidurkis(b.namuDarbai) * 0.4 + b.egz * 0.6);
            });
            break;
        case 4:
            std::sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
                return (apskaiciuotiMediana(a.namuDarbai) * 0.4 + a.egz * 0.6) < (apskaiciuotiMediana(b.namuDarbai) * 0.4 + b.egz * 0.6);
            });
            break;
        default:
            std::cout << "Neteisingas pasirinkimas\n";
            return;
    }
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
    std::cout << "Ar norite išsaugoti į failą? (T - taip, N - ne): ";
    std::string ats;
    std::cin >> ats;
    if (ats == "T" || ats == "t") {
        std::ofstream rf("rezultatai.txt");
        
        rf << std::fixed << std::setprecision(2);
        rf << "-----------------------------------------------------------\n";
        rf << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(25) << "Galutinis (vid.)  Galutinis (med.)\n";
        rf << "-----------------------------------------------------------\n";
        for (const auto& studentas : studentai) {
            double galutinis_v = Vidurkis(studentas.namuDarbai) * 0.4 + studentas.egz * 0.6;
            double galutinis_m = apskaiciuotiMediana(studentas.namuDarbai) * 0.4 + studentas.egz * 0.6;

            rf << std::setw(15) << studentas.vardas 
               << std::setw(15) << studentas.pavarde
               << std::setw(15) << galutinis_v
               << std::setw(15) << galutinis_m << "\n";
        }
    }
}
void gen_file(const std::string& pav, int kiek)
{
    std::ofstream gf(pav);
    if (!gf) std::cout<<"failas nebuvo sukurtas"<<std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, 10);
    for (int i=0; i<kiek; i++)
    {
        gf<<"VardasNR"<<i<<" "<<"PavardeNR"<<i;
        for (int j=0; j<5; j++)
        {
            gf<<" "<<distr(gen);
        }
        gf<<distr(gen)<<std::endl;
    }
    gf.close();
}
void failo_nuskaitymas(const std::string& pav, int kiek, std::vector<Student>& studentai)
{
    std::ifstream rf(pav);
    if (!rf) std::cout<<"failas neatsidaro"<<std::endl;
    Student studentas;
    while (rf >> studentas.vardas >> studentas.pavarde) {
        studentas.namuDarbai.clear();
        int pazymys;
        for (int i = 0; i < 5; i++) {
            if (!(rf >> pazymys)) 
                throw std::runtime_error("Klaida skaitant pažymius iš failo.");
            studentas.namuDarbai.push_back(pazymys);
        }
        if (!(rf >> studentas.egz))
            throw std::runtime_error("Klaida skaitant egzamino pažymį iš failo.");
        studentai.push_back(studentas);
    }
}
void padalinti_studentus (std::vector<Student>& studentai, std::vector<Student>& vargsiukai, std::vector<Student>& kietekai)
{
    for (const auto& studentas : studentai)
    {
        double galutinis_v = Vidurkis(studentas.namuDarbai) * 0.4 + studentas.egz * 0.6;
        if (galutinis_v < 5.0)
        {
            vargsiukai.push_back(studentas);
        }
        else kietekai.push_back(studentas);
    }
}