#pragma once // Include  guard

#include <vector>

struct StudentStructure {
    std::string FirstName, LastName;
    int ExamGrade;
    double FinalGrade;
    std::vector<int> HW; // Vector of homework grades
};
