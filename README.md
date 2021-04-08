# Student final grade calculator

A program written in C++ to calculate the final mark of students using the formula:

    FinalMark = 0.4 * HomeworkMark + 0.6 * ExamMark

## Speed analysis:

Testbed specs:  AMD EPYC 7502P 32C 64T @ 2.5 GHz; 512 GB DDR4 ECC; 480 GB NVMe SSD 3D XPoint in RAID 10

Homework amount: 10

Calculation method: Average

Sorting type: Final mark


**Data read:**

| HW amount | vector | deque | list |
|--|--|--|--|
| 1000 | 0.00121062 sec. | 0.00810994 sec. | 0.00295512 sec. |
| 10000 | 0.0111675 sec. | 0.0147009 sec. | 0.0239978 sec. |
| 100000 | 0.101438 sec.  | 0.135723 sec. | 0.213205 sec. |
| 1000000 | 0.989572 sec. |1.28598 sec. | 2.05806 sec. |
| 10000000 | 9.85548 sec. | 12.5431 sec. | 20.796 sec. |

The most effective for data read is **vector**, **deque** is slower and **list** is the slowest

**Data sorting:**
| HW amount | vector | deque | list |
|--|--|--|--|
| 1000 | 0.000421655 sec. | 0.00260031 sec. | 0.000923334 sec. |
| 10000 | 0.00454617 sec. | 0.0073013 sec. | 0.0083996 sec. |
| 100000 | 0.0517337 sec.  | 0.0788873 sec. | 0.113319 sec. |
| 1000000 | 0.613458 sec. | 0.898727 sec. | 1.71067 sec. |
| 10000000 | 9.24039 sec. | 12.1266 sec. | 23.3117 sec. |

The most effective for data sorting is **vector**, **deque** is slower and **list** is the slowest

## Functions:

 - Entering the name of the student
 - Entering or generating as many marks as the user wants
 - Choosing to enter more students if so wished
 - Choosing the final mark either calculated by median of homework mark or by the mean average of homework mark
 - Reading data from file
 - Choosing the std container

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
 
 0.3 Added exception handling and makefiles
 
 0.4 Added student grade files generation and separation to good and bad students
 
 0.5 Added ability to choose the container
 
 0.5.1 Fixed minor file generation bug and added automated tests
