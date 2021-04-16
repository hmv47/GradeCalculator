# Student final grade calculator

A program written in C++ to calculate the final mark of students using the formula:

    FinalMark = 0.4 * HomeworkMark + 0.6 * ExamMark

## Speed analysis, grouping strategies:

Testbed specs:  AMD EPYC 7502P 32C 64T @ 2.5 GHz; 512 GB DDR4 ECC; 480 GB NVMe SSD 3D XPoint in RAID 10
Homework amount: 20
Calculation method: Average
Sorting type: Final mark

**First strategy:** creating two new containers, the original one is deleted.

**Second strategy:** creating one new container, moving the students and shrinking the original (used in earlier versions).

| HW amount | 1 * vector | 2 * vector | 1 * deque | 2 * deque | 1 * list | 2 * list |
|--|--|--|--|--|--|--|
| 100000 |0.0544945s | 0.0546768s | 0.0820833s | 0.0768347s | 0.13402s | 0.091341s |
| 1000000 | 0.623508s  | 0.648407s | 0.891132s | 0.855583s | 1.81378s | 0.95404s |
| 10000000 | 8.48666s | 7.13467s | 10.2848s | 8.4427s | 24.1845s | 16.1637s |

The second strategy is much faster mainly seen in **deque** and **list**.

### Speed analysis with *std::vector*
**Normal**: using second strategy, no optimizations
**Optimized**: sorting using *std::partition* and second strategy

| HW amount | Normal | Optimized |
|--|--|--|
| 10000 | 0.0546768s | 0.0103654s |
| 1000000 | 0.648407s | 0.096699s |
| 10000000 | 7.13467s | 0.946318s |

The optimization improved the speed up to seven times, hence the optimization worked well.

## Functions:

 - Entering the name of the student
 - Entering or generating as many marks as the user wants
 - Choosing to enter more students if so wished
 - Choosing the final mark either calculated by median of homework mark or by the mean average of homework mark
 - Reading data from file
 - Choosing the std container
 - Reading all five files for easier testing
 - Using optimizations with std vector

## Installation and usage:

 1. Download a [release](https://github.com/hmv47/GradeCalculator/releases)
 2. Get a C++ compiler (e.g. [GCC](https://gcc.gnu.org/)) or use an IDE such as CodeBlocks or Visual Studio
 3. Run make to compile the entire program. Prepare "kursiokai.txt" if you want to read data
 
    4a. You can run make clean to delete previous build
    
    4b. You can run make clean-all to clean all files including data files
    
 5. Run the file in the terminal using ./runtime (or runtime.exe if using Windows)
 6. Follow on screen instructions

## Versions:

 0.1 Initial version
 
 0.2 Added the ability to read data from files. From now on, only Vector version is developed.
 
 0.3 Added exception handling and makefiles.
 
 0.4 Added student grade files generation and separation to good and bad students.
 
 0.5 Added ability to choose the container.
 
 0.5.1 Fixed minor file generation bug and added automated tests.
 
 1.0.0 Final release, added optimization for vector, added two ways to sort.
