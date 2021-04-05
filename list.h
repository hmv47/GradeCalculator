#pragma once

#include <list>
#include "structure.h"

// Data generation
void GenerateGradesList (Students*, char);

// Final grade calculation
double AverageList (std::list<int>&, int);
double MedianList (std::list<int>&, int);
double FinalList (std::list<int> &, int, char);

// Data reading
void GetDataList (std::list<Students> &, char, char);
void FileReadList (std::list<Students>&, std::string, char);

// Other functions
void GroupStudentsList (std::list<Students>&, std::list<Students>&);
void SortList (std::list<Students>&, std::list<Students>&, char);
void WriteFileList (std::list<Students>&, char, std::string);

