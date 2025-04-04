#include "functions.h"
#include "student.h"

int main() {
    std::vector<Student> studentai;
    std::string pasirinkimas;
    Duom(studentai);
    std::cout<<"Ar rezultatus norite issaugoti faile? (T - taip, N - ne): ";
    std::cin >> pasirinkimas;
    if (pasirinkimas == "T" || pasirinkimas == "t") {
        Rez_file(studentai);
    } else if (pasirinkimas == "N" || pasirinkimas == "n") {
        Rez(studentai);
    } else {
        std::cout << "Neteisingas pasirinkimas\n";
    }
    return 0;
}