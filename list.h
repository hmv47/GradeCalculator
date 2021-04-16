// List header

#pragma once

#include <list>
#include "libraries.h"

// Data generation
void GenerateGradesList (StudentContainer*, char);

// Final grade calculation
double ListAverage (std::list<int>&, int);
double MedianList (std::list<int>&, int);
double FinalList (std::list<int> &, int, char);

// Data reading
void GetDataList (std::list<StudentContainer> &, char, char);
void FileReadList (std::list<StudentContainer>&, std::string, char);

// Other functions
void GroupStudentsList (std::list<StudentContainer>&, std::list<StudentContainer>&, std::list<StudentContainer>&, int);
void ListSort (std::list<StudentContainer>&, std::list<StudentContainer>&, char);
void WriteFileList (std::list<StudentContainer>&, char, std::string);
