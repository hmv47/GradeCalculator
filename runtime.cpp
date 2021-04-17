#include "containers.h"

int main () {
    Timer t;

    // Select performance measurement
    char TimerChoice;
    std::cout << "Measure execution time? (y/n)\n";
    std::cin >> TimerChoice;
    ValidateOption(TimerChoice, 'y', 'n');

    // Select input type (read from a file, generate or enter grades manually)
    char DataChoice;
    std::cout << "\nPlease choose input type:\n";
    std::cout << "Read file:\t  f\nGenerate:\t  g\nInput:\t\t  m\n"; 
    std::cin >> DataChoice;
    ValidateOption(DataChoice, 'f', 'g', 'm');

    // Select a std ContainerChoice
    char ContainerChoice;
    std::cout << "\nPlease choose a std container: \n";
    std::cout << "std::vector:\tv\nstd::list:\tl\nstd::deque:\td\n";
    std::cin >> ContainerChoice;
    ValidateOption(ContainerChoice, 'v', 'l', 'd');

    // Select optimization algorithms
    char OptimizationChoice;
    if (ContainerChoice == 'v') {
        std::cout << "\nUse optimizations? (y/n)\n";
        std::cin >> OptimizationChoice;
        ValidateOption(OptimizationChoice, 'y', 'n');
    }

    // Select FinalResult grade calculation method (median or average)
    char FinalChoice;
    std::cout << "\nPlease choose final grade type";
    std::cout << "\nMedian:\t\tm\nAverage:\ta\n";
    std::cin >> FinalChoice;
    ValidateOption(FinalChoice, 'm', 'a');

    // Select data partition SortStrategy
    int SortStrategy;
    std::cout << "\nPlease choose sorting strategy: \n";
    std::cout << "Create two new containers:\t1\nCreate one new container: \t2\n";
    std::cin >> SortStrategy;
    ValidateNumber(SortStrategy, 1, 2);

    // Select sorting type (alphabetically of by FinalResult grades)
    char SortChoice;
    std::cout << "\nPlease choose student sorting type:\n";
    std::cout << "First name:\tn\nLast name:\tl\nFinal mark:\tm\n";
    std::cin >> SortChoice;
    ValidateOption(SortChoice, 'n', 'l', 'm');

    // Select file generation
    char FileNumber = '1';       // Number of files to read
    std::string GeneratedFiles[5];    // Array of generated files' names
    if (DataChoice == 'f') {
        char NewFile;
    std::cout << "\nGenerate new data files? (y/n)\n";
        std::cin >> NewFile;
        ValidateOption(NewFile, 'y', 'n');

        // Generate files
        if (NewFile == 'y') {
            int multiplier = 1;
            if (TimerChoice == 'y') std::cout << "\nData file generation took:\n";

            for (int i = 0 ; i < 5; i ++) {
                if (TimerChoice == 'y') t.set();
                GradesGenerateFile(1000 * multiplier, GeneratedFiles[i]);
                std::cout << GeneratedFiles[i];
                TimerChoice == 'y' ? std::cout << " - " << t.elapsed() << " sec. \n" : std::cout << " generated\n";
                multiplier *= 10;
            }
        }

        // Select the number of files to read
        if (NewFile == 'y') {
            std::cout << "\nHow many files to read?\n";
            std::cout << "All generated:\t5\nOnly one:\t1\n"; 
            std::cin >> FileNumber;
            ValidateOption(FileNumber, '5', '1');
        };
    }


    // Read, group, sort and print data
    std::string FileName;
    for (int i = 0; i < FileNumber - '0'; i ++) {
        if (DataChoice == 'f')
            FileNumber == '5' ? FileName = GeneratedFiles[i] : FileName = InputFileName();

        if (ContainerChoice == 'v')
            VectorContainer(DataChoice, FinalChoice, SortChoice, SortStrategy, TimerChoice, OptimizationChoice, FileName);
        else if (ContainerChoice == 'd')
            DequeContainer(DataChoice, FinalChoice, SortChoice, SortStrategy, TimerChoice, FileName);
        else ListContainer(DataChoice, FinalChoice, SortChoice, SortStrategy, TimerChoice, FileName);
        if (FileNumber == '5') std::cout << "(" << i + 1 << "/5)\n";
    }
    return 0;
}
