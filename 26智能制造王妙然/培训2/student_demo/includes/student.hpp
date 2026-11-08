#ifndef STUDENT_HPP
#define STUDENT_HPP
#include <string>

class Student {
private:
    std::string name;
    int score;
public:
    Student(std::string n, int s);
    void printInfo();
    void setScore(int s);
};
#endif
