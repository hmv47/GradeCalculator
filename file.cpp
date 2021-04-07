// File generation and reading

#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>

#include "file.h"

std::string GetFile () {
    bool BadFile;
    std::string FileName;
    std::cout << "\nEnter the file name: \n";
    std::cin >> FileName;
    do {
        try {
            std::ifstream in (FileName);
            if (!in.good())         // Check if file exists
                throw 0;
            else {
                in.close();
                BadFile = false;
            }
        } catch (int exception) {   // If doesn't exist - re-enter
            BadFile = true;
            std::cout << "Data file " << FileName << " Does not exist. Please try again:\n";
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> FileName;
        }
    } while (BadFile);              // While bad file
    return FileName;
}

void GradesGenerateFile (int StudNumber) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(1, 10); // 1-10
    std::uniform_int_distribution<int> random20(1, 20); // 1-20

    int HWNumber = random20(mt);         // Gennerate random number of grades, can be hard-coded for testing

    std::ostringstream FileName;        // File name
    FileName << "kursiokai" << StudNumber << ".txt";
    std::ofstream add (FileName.str()); // Open

    // Print header text
    std::ostringstream row ("");        // Empty row to be filled in with header data
    row << std::setw(20) << std::left << "FirstName" << std::setw(21) << "LastName";
    for (int i = 1; i <= HWNumber; i ++)
        row << "HW" << std::setw(8) << std::left << i;
    row << "Ex.\n";
    add << row.str();                   // Print out the row

    // Print student data
    for (int i = 1; i <= StudNumber; i ++) {
        row.str("");                    // Clear and fill
        row << "FirstName" << std::setw(14) << std::left << i << "LastName" << std::setw(14) << std::left << i;
        for (int j = 0; j <= HWNumber; j ++)
            row << std::setw(10) << std::left << random10(mt);
        row << "\n";
        add << row.str();
    }
    add.close();
}
