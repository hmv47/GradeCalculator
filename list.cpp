// STD::LIST and related functions

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <list>

#include "list.h"
#include "validation.h"
#include "structure.h"

void GenerateGradesList (Students* BadStudents, char FinalChoice) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(1, 10);

    char moreGrades;
    std::list<int> HW;
    std::cout << "\nGenerating grades\n\n";
    do {
        HW.push_back(random10(mt)); // Generate grade
        std::cout << "Generated grade: " << HW.back() << "\nGenerate another (y/n) ";
        std::cin >> moreGrades;
        ValidateOption(moreGrades, 'y', 'n');
    } while (moreGrades == 'n');

    int ExamGrade = random10(mt); // Generate exam grade
    std::cout << "Generated exam grade: " << ExamGrade << "\n";
    
    // Get final grade
    BadStudents->FinalGrade = FinalList(HW, ExamGrade, FinalChoice);
}

double AverageList (std::list<int> &HW, int n) {
    double sum = 0;
    auto it = HW.begin();
    for (auto it = HW.begin(); it != HW.end(); it ++)
        sum += *(it);
    return (sum / n);
}

double MedianList (std::list<int> &HW, int n) {
    double m;
    HW.sort();                      // Sort ascending

    auto it1 = HW.begin();          // To get middle value
    auto it2 = it1;
    std::advance(it1, n / 2 - 1);   // Move iterator before the middle
    std::advance(it2, n / 2);       // Move iterator to the middle

    n % 2 == 0 ? (m = 1.00 * (*it1 + *it2) / 2) : m = *it2; // Get median
    return m;
}

double FinalList (std::list<int> &HW, int ExamGrade, char type){
    double hw;
    if (!HW.empty())  // If not empty
        type == 'm' ? hw = MedianList(HW, HW.size()) : hw = AverageList(HW, HW.size());
    else hw = 0;
    return (0.4 * hw + 0.6 * ExamGrade);
}

void GetDataList (std::list<Students> &BadStudents, char DataChoice, char FinalChoice) {
    char MoreStudents = 'n';
    bool moreHW;
    int tempMark;       // Temporary homework
    std::list<int> HW; // List
    Students tmp;     // Temporary structure
    int ExamGrade;
    do {
        moreHW = true;
        HW.clear();   // Empty the list for new values

        std::cout << "\nStudent's full name:\n";
        std::cin >> tmp.FirstName >> tmp.LastName;

        if (DataChoice == 'g')
            GenerateGradesList(&tmp, FinalChoice); // Generate homework and ExamGrade grades
        else {
            std::cout << "\nEnter grades, 0 after the last one:\n";
            do {
                std::cin >> tempMark;
                ValidateNumber(tempMark, 0, 10);
                if (tempMark == 0)
                    moreHW = false;             // Halt if 0
                else HW.push_back(tempMark);      // Add grade
            } while (moreHW);                   // While not 0

            std::cout << "\nExam grade:\n";
            std::cin >> ExamGrade;
            ValidateNumber(ExamGrade, 1, 10);
            tmp.FinalGrade = FinalList(HW, ExamGrade, FinalChoice);
        }
        BadStudents.push_back(tmp);                      // Add the structure to the list of students

        std::cout << "\nAdd another student (y/n) \n";
        std::cin >> MoreStudents;
        ValidateOption(MoreStudents, 'y', 'n');
    } while (MoreStudents == 'y');
}

void FileReadList (std::list<Students> &BadStudents, std::string FileName, char FinalChoice) {
    std::ifstream FRead (FileName);

    int HWNumber = 0;
    std::string header;
    std::getline(FRead, header);            // Read first line
    std::stringstream firstRow (header); // Copy to stringstream
    std::string str;
    while (firstRow >> str)              // Count the number of strings
        HWNumber ++;
    HWNumber -= 3;                        // Ignore first three

    Students tmp;
    int tempMark, ExamGrade;
    std::string row;
    std::stringstream dataRow;
    std::list<int> HW;
    while (std::getline(FRead, row)) { // EOF
        dataRow.clear();
        dataRow.str(row);
        dataRow >> tmp.FirstName >> tmp.LastName;
        HW.clear();                 // Clear
        for (int i = 0; i < HWNumber; i ++) {
            dataRow >> tempMark;
            HW.push_back(tempMark);
        }
        dataRow >> ExamGrade;
        tmp.FinalGrade = FinalList(HW, ExamGrade, FinalChoice);
        BadStudents.push_back(tmp);          // Push to main structure
    }
	FRead.close();
}

void GroupStudentsList (std::list<Students> &BadStudents, std::list<Students> &GoodStudents) {
    // Sort
    BadStudents.sort([](Students &s1, Students &s2) {return s1.FinalGrade < s2.FinalGrade;});

    // Count bad students
    int numOfBadStudents = 0;
    auto it = BadStudents.begin();
    while (it->FinalGrade < 5.0 && it != BadStudents.end()) {
            numOfBadStudents ++;
            it ++;
    }

    GoodStudents.assign(it, BadStudents.end());        // Copy good students
    BadStudents.resize(numOfBadStudents);    // Shrinkk
}

void SortList (std::list<Students> &BadStudents, std::list<Students> &GoodStudents, char SortChoice) {
    if (SortChoice == 'n') {
        BadStudents.sort([](Students &s1, Students &s2) {return s1.FirstName < s2.FirstName;});
        GoodStudents.sort([](Students &s1, Students &s2) {return s1.FirstName < s2.FirstName;});
    } else if (SortChoice == 'l') {
        BadStudents.sort([](Students &s1, Students &s2) {return s1.LastName < s2.LastName;});
        GoodStudents.sort([](Students &s1, Students &s2) {return s1.LastName < s2.LastName;});
    }
}

void WriteFileList (std::list<Students> &BadStudents, char FinalChoice, std::string FileName) {
    std::ofstream FWrite (FileName);
    std::ostringstream row ("");

    // Print header
    row << std::setw(20) << std::left << "First name" << std::setw(20) << "Last name" << "Final grade ";
    FWrite << row.str();

    FinalChoice == 'm' ? FWrite << "(Med.)\n" : FWrite << "(Avg.)\n";
    FWrite << "--------------------------------------------------------\n";

    // Print
    auto it = BadStudents.begin();
    for (auto it = BadStudents.begin(); it != BadStudents.end(); it ++) {
        row.str("");        // Empty row
        row << std::setw(20) << std::left << it->FirstName << std::setw(20) << it->LastName
            << std::fixed << std::setprecision(2) << it->FinalGrade << "\n";
        FWrite << row.str();    // Print
    }
    FWrite.close();
}
