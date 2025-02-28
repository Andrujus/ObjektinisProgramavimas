#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <string>

struct Student {
    std::string vardas;
    std::string pavarde;
    std::vector<int> namuDarbai;
    int egz;

    double Vidurkis() const;
    double apskaiciuotiMediana() const;
};

#endif