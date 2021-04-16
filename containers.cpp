#include "containers.h" // Containers header

void VectorContainer (char DataChoice, char FinalChoice, char SortChoice, int SortStrategy, char TimerChoice, char OptimizationChoice, std::string FileName) {
    std::vector<StudentContainer> AllStudents, GoodStudents, BadStudents; // Containers for all students, bad students and good students
    AllStudents.reserve(10000000);            // Safe guard to prevent memory over-allocation
    Timer t;

    // Read student data
    if (DataChoice == 'm' || DataChoice == 'g') {
        GetDataVector(AllStudents, DataChoice, FinalChoice);
    } else {
        if (TimerChoice == 'y') t.set();
        FileReadVector(AllStudents, FileName, FinalChoice);
        if (TimerChoice == 'y') std::cout << "\n" << FileName << " file read took: \t" << t.elapsed() << " sec.\n";
    }
    AllStudents.shrink_to_fit();

    // Dividing students into groups
    if (TimerChoice == 'y') t.set();
    GroupStudentsVector(AllStudents, GoodStudents, BadStudents, SortStrategy, OptimizationChoice);
    if (TimerChoice == 'y') std::cout << "Student grouping took: \t\t\t" << t.elapsed() << " sec. \n";

    // Sort students
    if (TimerChoice == 'y') t.set();
    SortStrategy == 1 ? SortVector(BadStudents, GoodStudents, SortChoice) : SortVector(AllStudents, GoodStudents, SortChoice);
    if (TimerChoice == 'y') std::cout << "Result grouping took: \t\t\t" << t.elapsed() << " sec. \n";

    // Write results to files
    if (TimerChoice == 'y') t.set();
    WriteFileVector(GoodStudents, FinalChoice, "good.txt");
    if (TimerChoice == 'y') std::cout << "Good writing took: \t\t\t" << t.elapsed() << " sec. \n";

    if (TimerChoice == 'y') t.set();
    SortStrategy == 1 ?  WriteFileVector(BadStudents, FinalChoice, "bad.txt"): WriteFileVector(AllStudents, FinalChoice, "bad.txt");
    if (TimerChoice == 'y') std::cout << "Bad writing took: \t\t\t" << t.elapsed() << " sec.\n";
}

void DequeContainer (char DataChoice, char FinalChoice, char SortChoice, int SortStrategy, char TimerChoice, std::string FileName) {
    std::deque<StudentContainer> AllStudents, GoodStudents, BadStudents; // Containers for all students, bad students and good students
    Timer t;

    // Read student data
    if (DataChoice == 'm' || DataChoice == 'g') {
        GetDataDeque(AllStudents, DataChoice, FinalChoice);
    } else {
        if (TimerChoice == 'y') t.set();
        FileReadDeque(AllStudents, FileName, FinalChoice);
        if (TimerChoice == 'y') std::cout << "\n" << FileName << " file read took: \t" << t.elapsed() << " sec.\n";
    }

    // Dividing students into groups
    if (TimerChoice == 'y') t.set();
    GroupStudentsDeque(AllStudents, GoodStudents, BadStudents, SortStrategy);
    if (TimerChoice == 'y') std::cout << "Student grouping took: \t\t\t" << t.elapsed() << " sec. \n";

    // Sort students
    if (TimerChoice == 'y') t.set();
    SortStrategy == 1 ? SortDeque(BadStudents, GoodStudents, SortChoice) : SortDeque(AllStudents, GoodStudents, SortChoice);
    if (TimerChoice == 'y') std::cout << "Result grouping took: \t\t\t" << t.elapsed() << " sec. \n";

    // Write results to files
    if (TimerChoice == 'y') t.set();
    WriteFileDeque(GoodStudents, FinalChoice, "good.txt");
    if (TimerChoice == 'y') std::cout << "Good writing took: \t\t\t" << t.elapsed() << " sec. \n";

    if (TimerChoice == 'y') t.set();
    SortStrategy == 1 ? WriteFileDeque(BadStudents, FinalChoice, "bad.txt") : WriteFileDeque(AllStudents, FinalChoice, "bad.txt");
    if (TimerChoice == 'y') std::cout << "Bad writing took: \t\t\t" << t.elapsed() << " sec.\n";
}

void ListContainer (char DataChoice, char FinalChoice, char SortChoice, int SortStrategy, char TimerChoice, std::string FileName) {
    std::list<StudentContainer> AllStudents, GoodStudents, BadStudents; // Containers for all students, bad students and good students
    Timer t;

    // Read student data
    if (DataChoice == 'm' || DataChoice == 'g') {
        GetDataList(AllStudents, DataChoice, FinalChoice);
    } else {
        if (TimerChoice == 'y') t.set();
        FileReadList(AllStudents, FileName, FinalChoice);
        if (TimerChoice == 'y') std::cout << "\n" << FileName << " file read took: \t" << t.elapsed() << " sec.\n";
    }

    // Dividing students into groups
    if (TimerChoice == 'y') t.set();
    GroupStudentsList(AllStudents, GoodStudents, BadStudents, SortStrategy);
    if (TimerChoice == 'y') std::cout << "Student grouping took: \t\t\t" << t.elapsed() << " sec. \n";

    // Sort students
    if (TimerChoice == 'y') t.set();
    SortStrategy == 1 ? ListSort(BadStudents, GoodStudents, SortChoice) : ListSort(AllStudents, GoodStudents, SortChoice);
    if (TimerChoice == 'y') std::cout << "Result grouping took: \t\t\t" << t.elapsed() << " sec. \n";

    // Write results to files
    if (TimerChoice == 'y') t.set();
    WriteFileList(GoodStudents, FinalChoice, "good.txt");
    if (TimerChoice == 'y') std::cout << "Good writing took: \t\t\t" << t.elapsed() << " sec. \n";

    if (TimerChoice == 'y') t.set();
    SortStrategy == 1 ? WriteFileList(BadStudents, FinalChoice, "bad.txt") : WriteFileList(AllStudents, FinalChoice, "bad.txt");
    if (TimerChoice == 'y') std::cout << "Bad writing took: \t\t\t" << t.elapsed() << " sec.\n";
}
