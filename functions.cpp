#include <iostream> // IO library
#include <iomanip> // IO manipulation library
#include <fstream> // File read / write
#include <sstream> // Used to read string
#include <algorithm> // Used to sort vector
#include <random> // Library, used to generate random numbers

#include "functions.h" // Functions header

void FileInput (std::vector<StudentStructure> &IndividualVector) {
    std::ifstream FRead ("kursiokai.txt");     // Open the file
    int HomeworkAmount = 0;

    std::string FLine;
    std::getline(FRead, FLine);            // Read the first line of the file
    std::stringstream ss1 (FLine);       // Copy into stringstream
    std::string str1;
    while (ss1 >> str1)                       // Count the number of separate strings
        HomeworkAmount ++;
    HomeworkAmount -= 3;                           // Ignore FirstName, LastName and ExamGrade strings

    StudentStructure VectorStore; // Initialize temporary vector
    int HWStore;
    do {                                    // Read one students data into structure
        FRead >> VectorStore.FirstName >> VectorStore.LastName;
        VectorStore.HomeworkVector.clear();                    // Empty the temporary homework vector and fill it with grades from the file
        for (int i = 0; i < HomeworkAmount; i ++) {
            FRead >> HWStore;
            VectorStore.HomeworkVector.push_back(HWStore);
        }
        FRead >> VectorStore.ExamGrade;
        IndividualVector.push_back(VectorStore);                  // Push the temporary structure to the vector of structures
    } while (!FRead.eof());                    // Continue reading until the end of file is reached
	FRead.close();                             // Close the file
}


// Calculate average grade
double GradeAverage (int* HomeworkVector, int n) {
    double sum = 0;
    for (int i = 0; i < n; i ++)
        sum += HomeworkVector[i];
    return (sum / n);
}

// Calculate median grade
double GradeMedian (int *HomeworkVector, int n) {
    double m;
    std::sort(HomeworkVector, HomeworkVector + n);
    n % 2 == 0 ? (m = 1.00 * (HomeworkVector[n / 2 - 1] + HomeworkVector[n / 2]) / 2) : m = HomeworkVector[n / 2];
    return m;
}

double Result (StudentStructure* IndividualVector, char type){
    double HomeworkGrade;
    if (!IndividualVector->HomeworkVector.empty())  // Test that the vector isn't empty
        type == 'm' ? HomeworkGrade = GradeMedian(&IndividualVector->HomeworkVector[0], IndividualVector->HomeworkVector.size()) : HomeworkGrade = GradeAverage(&IndividualVector->HomeworkVector[0], IndividualVector->HomeworkVector.size());
    else HomeworkGrade = 0;
    return (0.4 * HomeworkGrade + 0.6 * IndividualVector->ExamGrade);
}

template <typename T>
void RepeatInput(T& input) {
    std::cin.clear();
    std::cin.ignore(256,'\n');
    std::cin >> input;
}

// Test input (2)
void ValidateChoice (char& input, char option1, char option2) {
    while (!(input == option1 || input == option2)) {
        std::cout << "Error. You can choose (" << option1 << "/" << option2 << ") \n";
        RepeatInput(input);
    }
}

// Test input (3)
void ValidateChoice (char& input, char option1, char option2, char option3) {
    while (!(input == option1 || input == option2 || input == option3)) {
        std::cout << "Error. You can choose (" << option1 << "/" << option2  << "/" << option3 << ") \n";
        RepeatInput(input);
    }
}

// Test numbers
void ValidateNumber (int& input, int lowest, int highest) {
    while (input < lowest || input > highest || std::cin.fail()) {
        std::cout << "Error. You can choose [" << lowest << " ; " << highest << "] \n";
        RepeatInput(input);
    }
}

void generateGrades (StudentStructure* IndividualVector) {
    char MoreGrades;
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(1, 10); // Define the range

    do {
        IndividualVector->HomeworkVector.push_back(distr(gen)); // Generate random grade
        std::cout << "\nGenerated grade: " << IndividualVector->HomeworkVector.back() << "\nGenerate another? (y/n) ";
        std::cin >> MoreGrades;
        ValidateChoice(MoreGrades, 'y', 'n');
    } while (MoreGrades == 'y');

    IndividualVector->ExamGrade = distr(gen);  // Generate a random exam grade
    std::cout << "\n\nGenerated exam grade: " << IndividualVector->ExamGrade << "\n";
}

void FileOutput(std::vector<StudentStructure> &IndividualVector, char AvgManChoice) {
    std::ofstream FWrite ("rezultatai.txt"); // Open results file

    FWrite << std::setw(20) << std::left << "First name" << std::setw(20) << "Last name" << "Final grade ";        // Header
    AvgManChoice == 'm' ? FWrite << "(Med.)\n" : FWrite << "(Avg.)\n";
    FWrite << "--------------------------------------------------------\n";
    for (int i = 0; i < IndividualVector.size(); i ++)                 // Print out student's data
        FWrite << std::setw(20) << std::left << IndividualVector[i].FirstName << std::setw(20) << IndividualVector[i].LastName << std::fixed << std::setprecision(2) << IndividualVector[i].TotalResult << "\n";

    try {
        if (FWrite.good())                                  // Print message if OK
           std::cout << "\n\nThe results were written to file rezultatai.txt\n\n"; // message if OK
        else throw FWrite.rdstate();                        // Set error state flag as an exception code
    } catch (int code) { // catch the exception
        std::cout << "Error: " << code << "\n"; // Error code
    }
    FWrite.close();                                         // Close the results' file
}
