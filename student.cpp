#include "student.h"
#include <algorithm>

double Student::Vidurkis() const {
    if (namuDarbai.empty()) return 0.0;
    
    double suma = 0.0;
    for (int pazymys : namuDarbai) {
        suma += pazymys;
    }

    return suma / namuDarbai.size();
}
