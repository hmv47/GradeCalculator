#pragma once

#include <vector>
#include "structure.h"

// Data generation
void GenerateGradesVector (Students*);

// Final grade calculation
double AverageVector (std::vector<int>&, int);
double MedianVector (std::vector<int>*, int);
double FinalVector (std::vector<int>&, int, char);

// Data reading
void GetDataVector (std::vector<Students>&, char, char);
void FileReadVector (std::vector<Students>&, std::string, char);

// Other functions
void GroupStudentsVector (std::vector<Students>&, std::vector<Students>&);
void SortVector (std::vector<Students>&, std::vector<Students>&, char);
void WriteFileVector (std::vector<Students>&, char, std::string);

