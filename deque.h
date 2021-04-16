// List header

#pragma once

#include <deque>
#include "libraries.h"

// Data generation
void GenerateGradesDeque (StudentContainer*);

// Final grade calculation
double AverageDeque (std::deque<int>&, int);
double MedianDeque (std::deque<int>*, int);
double FinalDeque (std::deque<int>&, int, char);

// Data reading
void GetDataDeque (std::deque<StudentContainer>&, char, char);
void FileReadDeque (std::deque<StudentContainer>&, std::string, char);

// Other functions
void GroupStudentsDeque (std::deque<StudentContainer>&, std::deque<StudentContainer>&, std::deque<StudentContainer>&, int);
void SortDeque (std::deque<StudentContainer>&, std::deque<StudentContainer>&, char);
void WriteFileDeque (std::deque<StudentContainer>&, char, std::string);
