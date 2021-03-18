# Student final grade calculator

A program written in C++ to calculate the final mark of students using the formula:

    FinalMark = 0.4 * HomeworkMark + 0.6 * ExamMark

## Speed analysis

Testbed specs:  AMD EPYC 7502P 32C 64T @ 2.5 GHz; 512 GB DDR4 ECC; 480 GB NVMe SSD 3D XPoint in RAID 10
Homework amount: 10
Calculation method: Average
Sorting type: Final mark

| HW amount | Generating | Reading | Grouping | Good output | Bad output | File size |
|--|--|--|--|--|--|--|
| 1000 | 0.0025858 sec. | 0.00192755 sec. | 0.00250414 sec. | 0.000762517 sec. | 0.000478883 sec. | 149K |
| 10000 | 0.0201729 sec. | 0.0177261 sec. | 0.0156242 sec. | 0.00347689 sec. | 0.00241029 sec. | 1.5M |
| 100000 | 0.128811 sec.  | 0.104822 sec. | 0.207657 sec. | 0.0345887 sec. | 0.0237679 sec. | 15M |
| 1000000 | 1.27242 sec. | 0.965054 sec. | 2.7389 sec. | 0.3486 sec. | 0.236903 sec.| 145M |
| 10000000 | 12.8224 sec. | 9.56449 sec. | 33.4682 sec. | 3.33438 sec. | 2.34011 sec. | 1.5G |

## Functions:

 - Entering the name of the student
 - Entering or generating as many marks as the user wants
 - Choosing to enter more students if so wished
 - Choosing the final mark either calculated by median of homework mark or by the mean average of homework mark
 - Reading data from file

## Installation and usage:

 1. Download a [release](https://github.com/hmv47/GradeCalculator/releases)
 2. Get a C++ compiler (e.g. [GCC](https://gcc.gnu.org/)) or use an IDE such as CodeBlocks or Visual Studio
 3. Run make to compile the entire program. Prepare "kursiokai.txt" if you want to read data
 4. You can run make clean to delete previous build
 5. Run the file in the terminal using ./vector (or vector.exe if using Windows)
 6. Follow on screen instructions

## Versions:

 0.1 Initial version
 
 0.2 Added the ability to read data from files. From now on, only Vector version is developed.
 
 0.3 Added exception handling and makefiles
 
 0.4 Added student grade files generation and separation to good and bad students
