#include "student.hpp"
#include <iostream>

Student::Student(std::string n, int s) : name(n), score(s) {}

void Student::printInfo() {
    std::cout << "姓名: " << name << ", 成绩: " << score << std::endl;
}

void Student::setScore(int s) {
    score = s;
}
