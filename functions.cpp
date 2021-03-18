#include <iomanip> // IO manipulation
#include <iostream> // Screen lib
#include <fstream> // File lib
#include <sstream> // String stream
#include <algorithm> // Used for sort
#include <random> // Random number generation
#include <chrono> // RND and timer

#include "functions.h" // Functions lib

void FileRead (std::vector<StudentStructure> &BadStudents, std::string FileName) {
    std::ifstream FRead (FileName);

    int HWAmount = 0;
    std::string header;
    std::getline(FRead, header); // Read first line
    std::stringstream firstRow (header);  // Copy into string stream
    std::string str;
    while (firstRow >> str) // Count the number of separate strings
        HWAmount ++;
    HWAmount -= 3;  // Ignore first three strings

    StudentStructure TempVector;
    TempVector.HW.reserve(HWAmount);

    int CurrHW;
    std::string row;
    std::stringstream DataRow;
    while (std::getline(FRead, row)) {   // Continue reading until EOF
        DataRow.str(row);
        DataRow >> TempVector.FirstName >> TempVector.LastName;
        TempVector.HW.clear();                    // Clear temporary vector
        for (int i = 0; i < HWAmount; i ++) {
            DataRow >> CurrHW;
            TempVector.HW.push_back(CurrHW);
        }
        DataRow >> TempVector.ExamGrade;
        BadStudents.push_back(TempVector); // Push structure
    }
	FRead.close();
}

double GradeAverage (int* HW, int n) {
    double sum = 0;
    for (int i = 0; i < n; i ++)
        sum += HW[i];
    return (sum / n);
}

double GradeMedian (int *HW, int n) {
    double m;
    std::sort(HW, HW + n);
    n % 2 == 0 ? (m = 1.00 * (HW[n / 2 - 1] + HW[n / 2]) / 2) : m = HW[n / 2];
    return m;
}

double Result (StudentStructure* BadStudents, char type){
    double hw;
    if (!BadStudents->HW.empty())  // Test that the vector is not empty
        type == 'm' ? hw = GradeMedian(&BadStudents->HW[0], BadStudents->HW.size()) : hw = GradeAverage(&BadStudents->HW[0], BadStudents->HW.size());
    else hw = 0;
    return (0.4 * hw + 0.6 * BadStudents->ExamGrade);
}

void GroupStudents (std::vector<StudentStructure> &BadStudents, std::vector<StudentStructure> &GoodStudents) {
    // Sort students by their final grades
    std::sort(BadStudents.begin(), BadStudents.end(), [](StudentStructure &s1, StudentStructure &s2) {return s1.FinalGrade < s2.FinalGrade;});

    int BadStudentsAmount = 0;
    while (BadStudents[BadStudentsAmount].FinalGrade < 5.0)     // Get students with grade > 5
        BadStudentsAmount ++;

    GoodStudents.reserve(BadStudents.size() - BadStudentsAmount);    // Set capacity
    std::copy(BadStudents.begin() + BadStudentsAmount, BadStudents.end(), std::back_inserter(GoodStudents)); // Copy good students

    BadStudents.resize(BadStudentsAmount);                 // Resize shrink bad students
    BadStudents.shrink_to_fit();                          // Shrink
}

template <typename T>
void RepeatInput(T& input) {
    std::cin.clear();
    std::cin.ignore(256,'\n');
    std::cin >> input;
}

// 2 parameter test
void ValidateOption (char& input, char option1, char option2) {
    while (!(input == option1 || input == option2)) {
        std::cout << "Error. Please choose (" << option1 << "/" << option2 << ") \n";
        RepeatInput(input);
    }
}

// 3 parameter test
void ValidateOption (char& input, char option1, char option2, char option3) {
    while (!(input == option1 || input == option2 || input == option3)) {
        std::cout << "Error. Please choose (" << option1 << "/" << option2  << "/" << option3 << ") \n";
        RepeatInput(input);
    }
}

// Test if entered a number
void ValidateNumber (int& input, int lowest, int highest) {
    while (input < lowest || input > highest || std::cin.fail()) {
        std::cout << "Error. Please choose [" << lowest << " ; " << highest << "] \n";
        RepeatInput(input);
    }
}

void GradesGenerate (StudentStructure* BadStudents) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count())); // Random number generator
    std::uniform_int_distribution<int> random10(1, 10);

    char MoreGrades;
    std::cout << "\nGenerating grades.\n\n";
    do {
        BadStudents->HW.push_back(random10(mt));                      // Generate random grade
        std::cout << "Grade: " << BadStudents->HW.back() << "\nGenerate another ? (y/n)";
        std::cin >> MoreGrades;
        ValidateOption(MoreGrades, 'y', 'n');
    } while (MoreGrades == 'y');

    BadStudents->ExamGrade = random10(mt);                                 // Random exam grade
    std::cout << "Generated exam grade: " << BadStudents->ExamGrade << "\n";
}

void GenerateFile (int numOfStudents) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count())); // Random number generator
    std::uniform_int_distribution<int> random10(1, 10);
    std::uniform_int_distribution<int> random20(1, 20);
    int HWAmount = random20(mt);                     // Generate the amount of grades

    std::ostringstream FileName;
    FileName << "kursiokai" << numOfStudents << ".txt"; // Create data file name
    std::ofstream add (FileName.str());                 // Open data file

    // Print header text
    std::ostringstream row ("");
    row << std::setw(20) << std::left << "Vardas" << std::setw(21) << "Pavarde";

    for (int i = 1; i <= HWAmount; i ++)
        row << "ND" << std::setw(8) << std::left << i;
    row << "Egz.\n";
    add << row.str();

    // Print student data text
    int Last = 0, grade;
    for (int i = 1; i <= numOfStudents; i ++) {
        row.str("");
        row << "Vardas" << std::setw(14) << std::left << i << "Pavarde" << std::setw(14) << std::left << i;
        for (int j = 0; j <= HWAmount; j ++) {
            grade = random10(mt);
            row << std::setw(10) << std::left << grade; // Generate exam grade
            Last = grade;
        }
        row << "\n";
        add << row.str();
    }
    add.close();
}

void SortStudents (std::vector<StudentStructure> &BadStudents, std::vector<StudentStructure> &GoodStudents, char SortChoice) {
    if (SortChoice == 'n') {
        std::sort(BadStudents.begin(), BadStudents.end(), [](StudentStructure &s1, StudentStructure &s2) {return s1.FirstName < s2.FirstName;});
        std::sort(GoodStudents.begin(), GoodStudents.end(), [](StudentStructure &s1, StudentStructure &s2) {return s1.FirstName < s2.FirstName;});
    } else if (SortChoice == 'l') {
        std::sort(BadStudents.begin(), BadStudents.end(), [](StudentStructure &s1, StudentStructure &s2) {return s1.LastName < s2.LastName;});
        std::sort(GoodStudents.begin(), GoodStudents.end(), [](StudentStructure &s1, StudentStructure &s2) {return s1.LastName < s2.LastName;});
    }
}

void WriteFile(std::vector<StudentStructure> &BadStudents, char FinalChoice, std::string FileName) {
    std::ofstream FWrite (FileName);                // Open the results file
    std::ostringstream row ("");                // Create empty row stringstream

    // Print header
    row << std::setw(20) << std::left << "First name" << std::setw(20) << "Last name" << "Final grade ";
    FWrite << row.str();

    FinalChoice == 'm' ? FWrite << "(Med.)\n" : FWrite << "(Avg.)\n";
    FWrite << "--------------------------------------------------------\n";

    // Print students' data
    for (int i = 0; i < BadStudents.size(); i ++) {
        row.str("");        // Empty the row stream and add single student's data
        row << std::setw(20) << std::left << BadStudents[i].FirstName << std::setw(20) << BadStudents[i].LastName
            << std::fixed << std::setprecision(2) << BadStudents[i].FinalGrade << "\n";
        FWrite << row.str();    // Print the completed row
    }
    FWrite.close();             // Close the results' file
}
