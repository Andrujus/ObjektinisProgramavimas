#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <chrono>
#include <random>

struct Student {
    std::string name;
    double grade;
};

template <typename Container>
void generate_students(Container& students, size_t count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(1.0, 10.0);

    for (size_t i = 0; i < count; ++i) {
        students.push_back({"Student" + std::to_string(i), dis(gen)});
    }
}

// Specialization for std::list to use list::sort()
void sort_students(std::list<Student>& students) {
    students.sort([](const Student& a, const Student& b) {
        return a.grade > b.grade;
    });
}

// General case for std::vector and std::deque
template <typename Container>
void sort_students(Container& students) {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.grade > b.grade;
    });
}

template <typename Container>
void benchmark(size_t count) {
    Container students;

    auto start = std::chrono::high_resolution_clock::now();
    generate_students(students, count);
    auto gen_end = std::chrono::high_resolution_clock::now();

    sort_students(students);
    auto sort_end = std::chrono::high_resolution_clock::now();

    std::cout << "Generated " << count << " students in "
              << std::chrono::duration<double>(gen_end - start).count() << " seconds.\n";
    std::cout << "Sorted in "
              << std::chrono::duration<double>(sort_end - gen_end).count() << " seconds.\n";
}

int main() {
    size_t data_sizes[] = {1000, 10000, 100000};

    for (size_t size : data_sizes) {
        std::cout << "\nBenchmarking std::vector with " << size << " elements:\n";
        benchmark<std::vector<Student>>(size);

        std::cout << "\nBenchmarking std::list with " << size << " elements:\n";
        benchmark<std::list<Student>>(size);

        std::cout << "\nBenchmarking std::deque with " << size << " elements:\n";
        benchmark<std::deque<Student>>(size);
    }

    return 0;
}
