// STD containers

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>

#include "structure.h"
#include "validation.h"
#include "file.h"
#include "vector.h"
#include "deque.h"
#include "list.h"

void VectorContainer (char DataChoice, char FinalChoice, char SortChoice) {
    std::vector<Students> BadStudents, GoodStudents; // All students and bad students
    BadStudents.reserve(10000000);        // To prevent over-allocation

    // Timer
    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed;

    // Read data
    if (DataChoice == 'm' || DataChoice == 'g') {
        GetDataVector(BadStudents, DataChoice, FinalChoice);
    } else {
        std::string FileName = GetFile();
        start = hrClock::now();
        FileReadVector(BadStudents, FileName, FinalChoice);
        end = hrClock::now();
        elapsed = end - start;
        std::cout << "\nFile read took: " << elapsed.count() << " sec.\n";
    }
    BadStudents.shrink_to_fit();

    // Group students
    start = hrClock::now(); 
    GroupStudentsVector(BadStudents, GoodStudents);
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "Student sorting took: " << elapsed.count() << " sec.\n";

    // Sort
    SortVector(BadStudents, GoodStudents, SortChoice);

    // Write results
    WriteFileVector(GoodStudents, FinalChoice, "good.txt");
    WriteFileVector(BadStudents, FinalChoice, "bad.txt");
}

void DequeContainer (char DataChoice, char FinalChoice, char SortChoice) {
    std::deque<Students> BadStudents, GoodStudents; // All students and bad students

    // Timer
    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed;

    // Read data
    if (DataChoice == 'm' || DataChoice == 'g') {
        GetDataDeque(BadStudents, DataChoice, FinalChoice);
    } else {
        std::string FileName = GetFile();
        start = hrClock::now();
        FileReadDeque(BadStudents, FileName, FinalChoice);
        end = hrClock::now();
        elapsed = end - start;
        std::cout << "\nFile read took: " << elapsed.count() << " sec.\n";
    }

    // Group students
    start = hrClock::now(); 
    GroupStudentsDeque(BadStudents, GoodStudents);
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "Student sorting took: " << elapsed.count() << " sec.\n";

    // Sort
    SortDeque(BadStudents, GoodStudents, SortChoice);

    // Write results
    WriteFileDeque(GoodStudents, FinalChoice, "good.txt");
    WriteFileDeque(BadStudents, FinalChoice, "bad.txt");
}

void ListContainer (char DataChoice, char FinalChoice, char SortChoice) {
    std::list<Students> BadStudents, GoodStudents; // All students and bad students

    // Timer
    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed;

    // Read data
    if (DataChoice == 'm' || DataChoice == 'g') {
        GetDataList(BadStudents, DataChoice, FinalChoice);
    } else {
        std::string FileName = GetFile();
        start = hrClock::now();
        FileReadList(BadStudents, FileName, FinalChoice);
        end = hrClock::now();
        elapsed = end - start;
        std::cout << "\nFile read took: " << elapsed.count() << " sec.\n";
    }

    // Group students
    start = hrClock::now(); 
    GroupStudentsList(BadStudents, GoodStudents);
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "Student sorting took: " << elapsed.count() << " sec.\n";

    // Sort
    SortList(BadStudents, GoodStudents, SortChoice);

    // Write results
    WriteFileList(GoodStudents, FinalChoice, "good.txt");
    WriteFileList(BadStudents, FinalChoice, "bad.txt");
}
