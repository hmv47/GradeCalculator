// STD::DEQUE and related functions

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <deque>

#include "deque.h"
#include "validation.h"
#include "structure.h"

void GenerateGradesDeque (Students* BadStudents, char FinalChoice) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(1, 10);

    char moreGrades;
    std::deque<int> HW;
    std::cout << "\nGenerating grades\n\n";
    do {
        HW.push_back(random10(mt)); // Generate grade
        std::cout << "Generated grade: " << HW.back() << "\nGenerate another (y/n) ";
        std::cin >> moreGrades;
        ValidateOption(moreGrades, 'y', 'n');
    } while (moreGrades == 'y');

    int ExamGrade = random10(mt); // Generate exam grade
    std::cout << "Generated exam grade: " << ExamGrade << "\n";
    
    // Get final grade
    BadStudents->FinalGrade = FinalDeque(HW, ExamGrade, FinalChoice);
}

double AverageDeque (std::deque<int> &HW, int n) {
    double sum = 0;
    for (int i = 0; i < n; i ++)
        sum += HW[i];
    return (sum / n);
}

double MedianDeque (std::deque<int> &HW, int n) {
    double m;
    std::sort(HW.begin(), HW.end());
    n % 2 == 0 ? (m = 1.00 * (HW[n / 2 - 1] + HW[n / 2]) / 2) : m = HW[n / 2];
    return m;
}

double FinalDeque (std::deque<int> &HW, int ExamGrade, char type) {
    double hw;
    if (!HW.empty()) // If not empty
        type == 'm' ? hw = MedianDeque(HW, HW.size()) : hw = AverageDeque(HW, HW.size());
    else hw = 0;
    return (0.4 * hw + 0.6 * ExamGrade);
}

void GetDataDeque (std::deque<Students> &BadStudents, char DataChoice, char FinalChoice) {
    char MoreStudents = 'n';
    bool moreHW;
    int tempMark;        // Temporary homework
    Students tmp;      // Temporary structure
    std::deque<int> HW;// Deque
    int ExamGrade;
    do {
        moreHW = true;
        HW.clear();    // Clear the deque

        std::cout << "\nStudent's full name:\n";
        std::cin >> tmp.FirstName >> tmp.LastName;

        if (DataChoice == 'g')
            GenerateGradesDeque(&tmp, FinalChoice); // Generate grades and exam grade
        else {
            std::cout << "\nEnter grades, 0 after the last one:\n";
            do {
                std::cin >> tempMark;
                ValidateNumber(tempMark, 0, 10);
                if (tempMark == 0)
                    moreHW = false;             // Halt if 0
                else HW.push_back(tempMark);      // Add grade
            } while (moreHW);                   // While not 0
            HW.shrink_to_fit();

            std::cout << "\nExam grade:\n";
            std::cin >> ExamGrade;
            ValidateNumber(ExamGrade, 1, 10);
            tmp.FinalGrade = FinalDeque(HW, ExamGrade, FinalChoice);
        }
        BadStudents.push_back(tmp);                      // Add the structure to the deque of students

        std::cout << "\nAdd another student (y/n) \n";
        std::cin >> MoreStudents;
        ValidateOption(MoreStudents, 'y', 'n');
    } while (MoreStudents == 'y');
}

void FileReadDeque (std::deque<Students> &BadStudents, std::string FileName, char FinalChoice) {
    std::ifstream FRead (FileName);

    int HWNumber = 0;
    std::string header;
    std::getline(FRead, header);  // Read first line
    std::istringstream firstRow (header); // Copy to stringstream
    std::string str;
    while (firstRow >> str)              // Count number of strings
        HWNumber ++;
    HWNumber -= 3;                        // Ignore first three

    Students tmp;
    int tempMark, ExamGrade;
    std::string row;
    std::istringstream dataRow;
    std::deque<int> HW;
    while (std::getline(FRead, row)) {      // EOF
        dataRow.clear();
        dataRow.str(row);
        dataRow >> tmp.FirstName >> tmp.LastName;
        HW.clear();                      // Clear
        for (int i = 0; i < HWNumber; i ++) {
            dataRow >> tempMark;
            HW.push_back(tempMark);
        }
        dataRow >> ExamGrade;
        tmp.FinalGrade = FinalDeque(HW, ExamGrade, FinalChoice);
        BadStudents.push_back(tmp);               // Push to main structure
    }
	FRead.close();
}

void GroupStudentsDeque (std::deque<Students> &BadStudents, std::deque<Students> &GoodStudents) {
    // Sort
    std::sort(BadStudents.begin(), BadStudents.end(), [](Students &s1, Students &s2) {return s1.FinalGrade < s2.FinalGrade;}); 

    // Count bad students
    int numOfBadStudents = 0;
    while (BadStudents[numOfBadStudents].FinalGrade < 5.0 && numOfBadStudents != BadStudents.size())
        numOfBadStudents ++;

    // Copy good students
    std::copy(BadStudents.begin() + numOfBadStudents, BadStudents.end(), std::back_inserter(GoodStudents));

    BadStudents.resize(numOfBadStudents); // Shrink
    BadStudents.shrink_to_fit();
}

void SortDeque (std::deque<Students> &BadStudents, std::deque<Students> &GoodStudents, char SortChoice) {
    if (SortChoice == 'n') {
        std::sort(BadStudents.begin(), BadStudents.end(), [](Students &s1, Students &s2) {return s1.FirstName < s2.FirstName;});
        std::sort(GoodStudents.begin(), GoodStudents.end(), [](Students &s1, Students &s2) {return s1.FirstName < s2.FirstName;});
    } else if (SortChoice == 'l') {
        std::sort(BadStudents.begin(), BadStudents.end(), [](Students &s1, Students &s2) {return s1.LastName < s2.LastName;});
        std::sort(GoodStudents.begin(), GoodStudents.end(), [](Students &s1, Students &s2) {return s1.LastName < s2.LastName;});
    }
}

void WriteFileDeque (std::deque<Students> &BadStudents, char FinalChoice, std::string FileName) {
    std::ofstream FWrite (FileName);
    std::ostringstream row ("");

    // Print header
    row << std::setw(20) << std::left << "First name" << std::setw(20) << "Last name" << "Final grade ";
    FWrite << row.str();
    FinalChoice == 'm' ? FWrite << "(Med.)\n" : FWrite << "(Avg.)\n";
    FWrite << "--------------------------------------------------------\n";

    // Print
    for (int i = 0; i < BadStudents.size(); i ++) {
        row.str("");        // Empty row
        row << std::setw(20) << std::left << BadStudents[i].FirstName << std::setw(20) << BadStudents[i].LastName
            << std::fixed << std::setprecision(2) << BadStudents[i].FinalGrade << "\n";
        FWrite << row.str();    // Print
    }
    FWrite.close();
}
