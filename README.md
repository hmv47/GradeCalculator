# Student final grade calculator

A program written in C++ to calculate the final mark of students using the formula:

    FinalMark = 0.4 * HomeworkMark + 0.6 * ExamMark



## Functions:

 - Entering the name of the student
 - Entering or generating as many marks as the user wants
 - Choosing to enter more students if so wished
 - Choosing the final mark either calculated by median of homework mark or by the mean average of homework mark
 - Reading data from file

## Installation and usage:

 1. Download a [release](https://github.com/hmv47/GradeCalculator/releases)
 2. Get a C++ compile (e.g. [GCC](https://gcc.gnu.org/)) or use an IDE such as CodeBlocks or Visual Studio
 3. Run make to compile the entire program. Prepare "kursiokai.txt" if you want to read data
 4. You can run make clean to delete previous build
 5. Run the file in the terminal using ./vector (or vector.exe if using Windows)
 6. Follow on screen instructions

## Versions:

 0.1 Initial version
 
 0.2 Added the ability to read data from files. From now on, only Vector version is developed.
 
 0.3 Added exception handling and makefiles
