#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "student.h"
#include "functions.cpp"
#include <vector>
#include <string>

double Vidurkis(const std::vector<int>& pazymiai);
double apskaiciuotiMediana(std::vector<int> pazymiai);
void gen_name(std::string& vardas, std::string& pavarde);
void Duom(std::vector<Student>& studentai);
void Rez(std::vector<Student>& studentai);

#endif