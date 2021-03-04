#pragma once // Include  guard

#include <vector>

struct StudentStructure { // Student structure
    std::string FirstName, LastName; // Name
    int ExamGrade;
    double TotalResult;
    std::vector<int> HomeworkVector; // Vector of grades
};

