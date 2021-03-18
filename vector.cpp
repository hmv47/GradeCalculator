#include <iostream> // Screen lib
#include <vector> // Vector lib
#include <algorithm> // Used for sort
#include <fstream> // File lib
#include <chrono> // RND and timer

#include "structure.h" // Structure lib
#include "functions.h" // Functions lib

int main () {
    std::vector<StudentStructure> BadStudents, GoodStudents; // All students are at first BadStudents
    BadStudents.reserve(10000000); // To avoid memory overallocation

    // Timer
    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed;

    // Choose whether generate new files
    char NewFile;
    std::cout << "Would you like to generate new data files? (y/n)\n";
    std::cin >> NewFile;
    ValidateOption(NewFile, 'y', 'n');

    // Generate files
    if (NewFile == 'y') {
        int mulitplier = 1;
        std::cout << "\nData file generation took:\n";
        for (int i = 0 ; i < 5; i ++) {
            start = hrClock::now();
            GenerateFile(1000 * mulitplier);
            std::cout << "kursiokai" << 1000 * mulitplier << ".txt - ";
            mulitplier *= 10;
            end = hrClock::now();
            elapsed = end - start;
            std::cout << elapsed.count() << " sec. \n";
        }
    }

    // Select input type (read from a file, generate or enter grades manually)
    char DataChoice;
    std::cout << "\nChoose input choice:\n";
    std::cout << "Read from file:\t   f\nGenerate randomly: g\nInput manually:\t   m\n";
    std::cin >> DataChoice;
    ValidateOption(DataChoice, 'f', 'g', 'm');

    // Ask for file name
    std::string FileName;
    if (DataChoice == 'f') {
        bool BadFile;
        std::cout << "\nPlease enter the filename:\n";
        std::cin >> FileName;
        do {
            try {
                std::ifstream in (FileName);
                if (!in.good()) // Check if file exists
                    throw 0;
                else {
                    in.close();
                    BadFile = false;
                }
            } catch (int exception) { // Catch exception, ask for re-entry
                BadFile = true;
                std::cout << "Data file " << FileName << " does not exist. Please try again:\n";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> FileName;
            }
        } while (BadFile);
    }

    // Select sorting
    char SortChoice;
    std::cout << "\nChoose result sorting type:\n";
    std::cout << "First name:\tn\nLast name:\tl\nFinal grade:\tg\n";
    std::cin >> SortChoice;
    ValidateOption(SortChoice, 'n', 'l', 'g');

    // Choose calculation method
    char FinalChoice;
    std::cout << "\nChoose result calculation method:";
    std::cout << "\nMedian:\t\tm\nAverage:\ta\n";
    std::cin >> FinalChoice;
    ValidateOption(FinalChoice, 'm', 'a');

    // Enter manually
    if (DataChoice == 'm' || DataChoice == 'g') {
        char MoreStudents = 'n';
        bool MoreHW;
        int CurrHW;       // Temporary value
        StudentStructure TempVector;     // Temporary structure before pushing back to the vector
        do {
            MoreHW = true;
            TempVector.HW.clear(); // Empty the vector for new values

            std::cout << "\nStudent's full name:\n";
            std::cin >> TempVector.FirstName >> TempVector.LastName;

            if (DataChoice == 'g')
                GradesGenerate(&TempVector); // Generate grades
            else {
                std::cout << "\nPlease enter the grades. After each grade push ENTER. After the last one enter 0:\n";
                do {
                    std::cin >> CurrHW;
                    ValidateNumber(CurrHW, 0, 10);
                    if (CurrHW == 0)
                        MoreHW = false; // Halt
                    else TempVector.HW.push_back(CurrHW); // Add the grade to the homework vector
                } while (MoreHW);                   // Continue the loop
                TempVector.HW.shrink_to_fit();

                std::cout << "\nExam grade:\n";
                std::cin >> TempVector.ExamGrade;
                ValidateNumber(TempVector.ExamGrade, 1, 10);
            }
            BadStudents.push_back(TempVector); // Push back

            std::cout << "\nWould you like to add more students? (y/n) ";
            std::cin >> MoreStudents;
            ValidateOption(MoreStudents, 'y', 'n');
        } while (MoreStudents == 'y');
    } else {
        start = hrClock::now();
        FileRead(BadStudents, FileName);  // Read data
        end = hrClock::now();
        elapsed = end - start;
        std::cout << "\nData read took: " << elapsed.count() << " sec.\n";
    }
    BadStudents.shrink_to_fit();

    // Calculate final grades
    for (int i = 0; i < BadStudents.size(); i ++)
        BadStudents[i].FinalGrade = Result(&BadStudents[i], FinalChoice);

    // Divide students
    start = hrClock::now();
    GroupStudents(BadStudents, GoodStudents);
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "\nDividing students took " << elapsed.count() << " sec.\n";

    // Sort results
    SortStudents(BadStudents, GoodStudents, SortChoice);

    // Write good students
    start = hrClock::now();
    WriteFile(GoodStudents, FinalChoice, "good.txt");
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "\nWriting good students took: " << elapsed.count() << " sec.";

    // Write bad students
    start = hrClock::now();
    WriteFile(BadStudents, FinalChoice, "bad.txt");
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "\nWriting bad students took: " << elapsed.count() << " sec.\n";

    return 0;
}
