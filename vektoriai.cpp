#include "functions.h"
#include "student.h"
#include <chrono>

int main() {
    std::string pasirinkimas;
    int ch1;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::vector<Student> studentai;
    std::vector<int> skaicius = {1000, 10000, 100000};
    Duom(studentai, ch1);
    if(ch1 != 5)
    {
    std::cout << "Ar norite spausdinti rezultatus i faila? (T - taip, N - ne): ";
    std::cin >> pasirinkimas;
    if (pasirinkimas == "T" || pasirinkimas == "t") 
    {
        Rez_file(studentai);
    }
    else if (pasirinkimas == "N" || pasirinkimas == "n")
    {
        Rez(studentai, ch1);
    }
    }
    
    

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Programos veikimo laikas: " << elapsed.count() << " sekundžių\n";
    return 0;
}