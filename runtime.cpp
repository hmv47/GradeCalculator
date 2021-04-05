// Main file

#include <iostream>
#include <chrono>

#include "validation.h"
#include "containers.h"
#include "file.h"

int main () {
    // Timer
    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed;

    // Container choice
    char ContainerChoice;
    std::cout << "Please choose a std container: \n";
    std::cout << "std::vector:\tv\nstd::list:\tl\nstd::deque:\td\n";
    std::cin >> ContainerChoice;
    ValidateOption(ContainerChoice, 'v', 'l', 'd');

    // New file
    char NewFile;
    std::cout << "\nGenerate new data files (y/n)\n";
    std::cin >> NewFile;
    ValidateOption(NewFile, 'y', 'n');

    // Generate files
    if (NewFile == 'y') {
        int mulitplier = 1;
        std::cout << "\nGeneration took:\n";
        for (int i = 0 ; i < 5; i ++) {
            start = hrClock::now();
            GradesGenerateFile(1000 * mulitplier);
            std::cout << "kursiokai" << 1000 * mulitplier << ".txt - ";
            mulitplier *= 10;
            end = hrClock::now();
            elapsed = end - start;
            std::cout << elapsed.count() << " sec. \n";
        }
    }

    // Input type
    char DataChoice;
    std::cout << "\nChoose input type:\n";
    std::cout << "Read file:\t  f\nGenerate:\t  g\nInput:\t\t  m\n"; 
    std::cin >> DataChoice;
    ValidateOption(DataChoice, 'f', 'g', 'm');

    // Sort type
    char SortChoice;
    std::cout << "\nChoose sorting type:\n";
    std::cout << "First name:\tn\nLast name:\tl\nFinal mark:\tm\n"; 
    std::cin >> SortChoice;
    ValidateOption(SortChoice, 'n', 'l', 'm');

    // Final type
    char FinalChoice;
    std::cout << "\nChoose final grade type";
    std::cout << "\nMedian:\t\tm\nAverage:\ta\n";
    std::cin >> FinalChoice;
    ValidateOption(FinalChoice, 'm', 'a');

    if (ContainerChoice == 'v')
        VectorContainer(DataChoice, FinalChoice, SortChoice);
    else if (ContainerChoice == 'd')
        DequeContainer(DataChoice, FinalChoice, SortChoice);
    else ListContainer(DataChoice, FinalChoice, SortChoice);

    return 0;
}
