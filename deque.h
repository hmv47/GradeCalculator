#pragma once

#include <deque>
#include "structure.h"

// Data generation
void GenerateGradesDeque (Students*);

// Final grade calculation
double AverageDeque (std::deque<int>&, int);
double MedianDeque (std::deque<int>*, int);
double FinalDeque (std::deque<int>&, int, char);

// Data reading
void GetDataDeque (std::deque<Students>&, char, char);
void FileReadDeque (std::deque<Students>&, std::string, char);

// Other functions
void GroupStudentsDeque (std::deque<Students>&, std::deque<Students>&);
void SortDeque (std::deque<Students>&, std::deque<Students>&, char);
void WriteFileDeque (std::deque<Students>&, char, std::string);
