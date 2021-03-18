#pragma once // Include  guard

#include <vector>
#include "structure.h"

template <typename T>
void RepeatInput(T&);
void FileRead (std::vector<StudentStructure>&, std::string);
double GradeAverage (int*, int);
double GradeMedian (int*, int);
double Result (StudentStructure*, char);
void GroupStudents (std::vector<StudentStructure>&, std::vector<StudentStructure>&);
void ValidateOption (char&, char, char);
void ValidateOption (char&, char, char, char);
void ValidateNumber (int&, int, int);
void GradesGenerate (StudentStructure*);
void GenerateFile (int);
void SortStudents (std::vector<StudentStructure>&, std::vector<StudentStructure>&, char);
void WriteFile(std::vector<StudentStructure>&, char, std::string);
