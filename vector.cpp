// Libraries

#include <iostream> // IO library
#include <iomanip> // IO manipulation library
#include <vector> // Vector
#include <fstream> // File read / write
#include <algorithm> // Used to sort vector

#include "structure.h"
#include "functions.h"

int main () {
    std::vector<StudentStructure> IndividualVector;  // Vector for student data
    char AvgManChoice;                            // a or m
    char FilGenChoice;                            // f or g or m

	std::cout << "Please choose the input method:\n\n";
    std::cout<< "Read from file:\t  f\nGenerate: \t  g\nInput manually:\t  m\n";
    std::cin >> FilGenChoice;                      // Read and validate the entered input type
    ValidateChoice(FilGenChoice, 'f', 'g', 'm');

    if (FilGenChoice == 'f') {
        try {
            std::ifstream in ("kursiokai.txt");
            if (!in.good())                     // Check data file exists
                throw 1;
            else in.close();
        } catch (int exception) {               // Case if file doesn't exist
            std::cout << "\nThe file does not exist. Please use a different method (g/m)\n";
            RepeatInput(FilGenChoice);
            ValidateChoice(FilGenChoice, 'g', 'm');
        }
    }

    std::cout << "\nPlease choose the calculation method:\n";
    std::cout << "\nMedian:\t\tm\nAverage:\ta\n";
    std::cin >> AvgManChoice;                      // Read result type
    ValidateChoice(AvgManChoice, 'm', 'a');

    if (FilGenChoice == 'm' || FilGenChoice == 'g') {
        char MoreStudents = 'n'; 
        bool HWMore;
        int HWStore;
        StudentStructure VectorStore;                           // Temporary structure to hold before pushing
        do {
            HWMore = true;
            VectorStore.HomeworkVector.clear();                        // Clear the data vector

            std::cout << "\nStudent's full name:\n";
            std::cin >> VectorStore.FirstName >> VectorStore.LastName;  // Read name

            if (FilGenChoice == 'g')
                generateGrades(&VectorStore);              // Generate grades
            else {
                std::cout << "\nPlease enter the marks separated by return (ENTER). After the last one enter 0:\n";
                do {
                    std::cin >> HWStore;             // Read grade
                    ValidateNumber(HWStore, 0, 10);
                    if (HWStore == 0)
                        HWMore = false;             // Halt if 0
                    else VectorStore.HomeworkVector.push_back(HWStore); // Add to vector
                } while (HWMore);                   // While not 0
                VectorStore.HomeworkVector.shrink_to_fit();            // Shrink
                std::cout << "\nPlease enter the exam grade:\n";
                std::cin >> VectorStore.ExamGrade;              // Read exam grade
                ValidateNumber(VectorStore.ExamGrade, 1, 10);
            }
            IndividualVector.push_back(VectorStore);                      // Push

            std::cout << "\nWould you like to add another student? (y/n) ";
            std::cin >> MoreStudents;               // More students
            ValidateChoice(MoreStudents, 'y', 'n');
        } while (MoreStudents == 'y');              // While y
    } else FileInput(IndividualVector);                             // Read data file
    IndividualVector.shrink_to_fit();

    // Calculate TotalResult grades
    for (int i = 0; i < IndividualVector.size(); i ++)
        IndividualVector[i].TotalResult = Result(&IndividualVector[i], AvgManChoice);

    // Sort by name
    std::sort(IndividualVector.begin(), IndividualVector.end(), [](StudentStructure &s1, StudentStructure &s2) {return s1.FirstName < s2.FirstName;});

    FileOutput(IndividualVector, AvgManChoice);

    IndividualVector.clear(); // Clear
    IndividualVector.shrink_to_fit(); // Shrink
    return 0;
}
