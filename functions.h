#pragma once // Include  guard

#include <vector> // Vector lib
#include "structure.h" // Include the structure type

template <typename T>
void RepeatInput(T&); // Repeat input in case of fail
void FileInput (std::vector<StudentStructure>&); // File reading
double GradeAverage (int*, int); // Calculating avg
double GradeMedian (int*, int); // Calculating median
double Result (StudentStructure*, char); // Calculating final result
void ValidateChoice (char&, char, char); // Validating choice (2)
void ValidateChoice (char&, char, char, char); // Validating choice (3)
void ValidateNumber (int&, int, int); // Validating number
void generateGrades (StudentStructure*); // Generating grades
void FileOutput(std::vector<StudentStructure>&, char); // Writing file
