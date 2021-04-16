#include "file.h"

std::string InputFileName () {
    bool badFile;
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
                badFile = false;
            }
        } catch (int exception) {   // Catch exception
            badFile = true;
            std::cout << "Data file " << FileName << " does not exist. Please try again: \n";
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> FileName;
        }
    } while (badFile);              // Repeat
    return FileName;
}

void GradesGenerateFile (int StudentNumber, std::string& FileName) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(1, 10); // 1-10
    std::uniform_int_distribution<int> random20(1, 20); // 1-20

        int HWNumber = random20(mt);         // HW number
     // int HWNumber = 20;         // Pre-set number

    std::ostringstream FileNameStream;        // File name stream
    FileNameStream << "kursiokai" << StudentNumber << ".txt";
    FileName = FileNameStream.str();
    std::ofstream add (FileName); // Open File

    // Print header text
    std::ostringstream row ("");        // Clear
    row << std::setw(20) << std::left << "FirstName" << std::setw(21) << "LastName";
    for (int i = 1; i <= HWNumber; i ++)
        row << "ND" << std::setw(8) << std::left << i;
    row << "Egz.\n";
    add << row.str();                   // Print

    // Print student data
    for (int i = 1; i <= StudentNumber; i ++) {
        row.str("");                    // Clear
        row << "FirstName" << std::setw(14) << std::left << i << "LastName" << std::setw(14) << std::left << i;
        for (int j = 0; j <= HWNumber; j ++)
            row << std::setw(10) << std::left << random10(mt);
        row << "\n";
        add << row.str();
    }
    add.close();
}
