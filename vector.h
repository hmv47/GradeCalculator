// Vector header

#pragma once

#include <vector>
#include "libraries.h"

// Data generation
void GenerateGradesVector (StudentContainer*);

// Final grade calculation
double AverageVector (std::vector<int>&, int);
double MedianVector (std::vector<int>*, int);
double FinalVector (std::vector<int>&, int, char);

// Data reading
void GetDataVector (std::vector<StudentContainer>&, char, char);
void FileReadVector (std::vector<StudentContainer>&, std::string, char);

// Other functions
void GroupStudentsVector (std::vector<StudentContainer>&, std::vector<StudentContainer>&, std::vector<StudentContainer>&, int, char);
void SortVector (std::vector<StudentContainer>&, std::vector<StudentContainer>&, char);
void WriteFileVector (std::vector<StudentContainer>&, char, std::string);
