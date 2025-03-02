#include "functions.h"
#include "student.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>

int main() {
    std::vector<Student> studentai;
    Duom(studentai);
    Rez(studentai);
    return 0;
}