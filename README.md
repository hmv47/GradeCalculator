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
| 1000 | 0.00184915 sec. | 0.0026162 sec. | 0.00419076 sec. |
| 10000 | 0.174586 sec | 0.145858s | 0.159842 sec. |
| 100000 | 1.70992 sec  | 1.4789 sec | 1.1710 sec. |
| 1000000 | 6.4789 sec. | 8.2478 sec. | 12.4782 sec. |
| 10000000 | 9.4859 sec. | 13.5378 sec. | 21.4353 sec. |

The most effective for data read is **vector**, **deque** is slower and **list** is the slowest

**Data sorting:**
| HW amount | vector | deque | list |
|--|--|--|--|
| 1000 | 0.000680192 sec. | 0.0012453 sec. | 0.00115116 sec. |
| 10000 | 0.035579 sec. | 0.041785 sec. | 0.042606 sec. |
| 100000 | 0.474306 sec.  | 0.536518 sec. | 0.688719 sec. |
| 1000000 | 6.92151 sec. | 6.92584 sec. | 7.06539 sec. |
| 10000000 | 8.35139 sec. | 14.7464 sec. | 15.3681 sec. |

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
