#include "student.hpp"

int main() {
    Student s1("张三", 90);
    s1.printInfo();
    s1.setScore(95);
    s1.printInfo();
    return 0;
}
