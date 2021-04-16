#include "list.h" // List lib

void GenerateGradesList (StudentContainer* AllStudents, char FinalChoice) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(1, 10);

    char moreGrades;
    std::list<int> HW;
    std::cout << "\nGenerating grades\n\n";
    do {
        HW.push_back(random10(mt)); // Generating random grade
        std::cout << "Generated grade: " << HW.back() << "\nGenerate another? (y/n) ";
        std::cin >> moreGrades;
        ValidateOption(moreGrades, 'y', 'n');
    } while (moreGrades == 'y');

    int ExamGrade = random10(mt);      // Generating exam grade
    std::cout << "Generated exam grade: " << ExamGrade << "\n";
    
   // Calculating the FinalResult grade
    AllStudents->FinalResult = FinalList(HW, ExamGrade, FinalChoice);
}

double ListAverage (std::list<int> &HW, int n) {
    double sum = 0;
    auto it = HW.begin();
    for (auto it = HW.begin(); it != HW.end(); it ++)
        sum += *(it);
    return (sum / n);
}

double MedianList (std::list<int> &HW, int n) {
    double m;
    HW.sort();                      // Sort ascending

    auto it1 = HW.begin();          // Iterators for middle value
    auto it2 = it1;
    std::advance(it1, n / 2 - 1);   // Move the iterator before the middle
    std::advance(it2, n / 2);       // Move the iterator to the middle

    n % 2 == 0 ? (m = 1.00 * (*it1 + *it2) / 2) : m = *it2; // Get median
    return m;
}

double FinalList (std::list<int> &HW, int ExamGrade, char type){
    double HWTotal;
    if (!HW.empty())  // If not empty
        type == 'm' ? HWTotal = MedianList(HW, HW.size()) : HWTotal = ListAverage(HW, HW.size());
    else HWTotal = 0;
    return (0.4 * HWTotal + 0.6 * ExamGrade);
}

void GetDataList (std::list<StudentContainer> &AllStudents, char DataChoice, char FinalChoice) {
    char StudentsMore = 'n';
    bool HWMore;
    int HWTemp;       // Temporary grade
    std::list<int> HW;  // Temporary structure
    StudentContainer tmp;   // List of grades
    int ExamGrade;
    do {
        HWMore = true;
        HW.clear();   // Clear

        std::cout << "\nStudent's full name:\n";
        std::cin >> tmp.FirstName >> tmp.LastName;

        if (DataChoice == 'g')
            GenerateGradesList(&tmp, FinalChoice); // Generate grades
        else {
            std::cout << "\nEnter grades, 0 after the last one:\n";
            do {
                std::cin >> HWTemp;
                ValidateNumber(HWTemp, 0, 10);
                if (HWTemp == 0)
                    HWMore = false;             // Halt if 0
                else HW.push_back(HWTemp);      // Add the grade
            } while (HWMore);                   // Continue

            std::cout << "\nExam grade:\n";
            std::cin >> ExamGrade;
            ValidateNumber(ExamGrade, 1, 10);
            tmp.FinalResult = FinalList(HW, ExamGrade, FinalChoice);
        }
        AllStudents.push_back(tmp);                       // Add to the container

        std::cout << "\nAdd another student? (y/n) \n";
        std::cin >> StudentsMore;
        ValidateOption(StudentsMore, 'y', 'n');
    } while (StudentsMore == 'y');
}

void FileReadList (std::list<StudentContainer> &AllStudents, std::string FileName, char FinalChoice) {
    std::ifstream FRead (FileName);

    int HWNumber = 0;
    std::string header;
    std::getline(FRead, header);            // Get first line of the file
    std::stringstream firstRow (header); // Copy to stringstream
    std::string str;
    while (firstRow >> str)              // Count the strings reaches the end
        HWNumber ++;
    HWNumber -= 3;                        // Ignore name, last name and grade

    StudentContainer tmp;
    int HWTemp, ExamGrade;
    std::string row;
    std::stringstream dataRow;
    std::list<int> HW;
    while (std::getline(FRead, row)) { // Continue until EOF
        dataRow.clear();
        dataRow.str(row);
        dataRow >> tmp.FirstName >> tmp.LastName;
        HW.clear();                 // Clear
        for (int i = 0; i < HWNumber; i ++) {
            dataRow >> HWTemp;
            HW.push_back(HWTemp);
        }
        dataRow >> ExamGrade;
        tmp.FinalResult = FinalList(HW, ExamGrade, FinalChoice);
        AllStudents.push_back(tmp);           // Push to the container
    }
	FRead.close();
}

void GroupStudentsList (std::list<StudentContainer> &AllStudents, std::list<StudentContainer> &GoodStudents, std::list<StudentContainer> &BadStudents, int SortStrategy) {
     // Sort students
    AllStudents.sort([](StudentContainer &s1, StudentContainer &s2) {return s1.FinalResult < s2.FinalResult;});

    // Count bad students
    int BadNumber = 0;
    auto it = AllStudents.begin();
    while (it->FinalResult < 5.0 && it != AllStudents.end()) {
        BadNumber ++;
        it ++;
    }

    GoodStudents.assign(it, AllStudents.end());               // Copy good students
    if (SortStrategy == 1) {
        BadStudents.assign(AllStudents.begin(), it);        // Copy bad students
        AllStudents.clear();
    } else AllStudents.resize(BadNumber);    // Resize the main vector
}

void ListSort (std::list<StudentContainer> &AllStudents, std::list<StudentContainer> &GoodStudents, char SortChoice) {
    if (SortChoice == 'n') {
        AllStudents.sort([](StudentContainer &s1, StudentContainer &s2) {return s1.FirstName < s2.FirstName;});
        GoodStudents.sort([](StudentContainer &s1, StudentContainer &s2) {return s1.FirstName < s2.FirstName;});
    } else if (SortChoice == 'l') {
        AllStudents.sort([](StudentContainer &s1, StudentContainer &s2) {return s1.LastName < s2.LastName;});
        GoodStudents.sort([](StudentContainer &s1, StudentContainer &s2) {return s1.LastName < s2.LastName;});
    }
}

void WriteFileList (std::list<StudentContainer> &AllStudents, char FinalChoice, std::string FileName) {
    std::ofstream FWrite (FileName);
    std::ostringstream row ("");

    // Print header
    row << std::setw(20) << std::left << "First name" << std::setw(20) << "Last name" << "Final grade ";
    FWrite << row.str();

    FinalChoice == 'm' ? FWrite << "(Med.)\n" : FWrite << "(Avg.)\n";
    FWrite << "--------------------------------------------------------\n";

    // Print student data
    auto it = AllStudents.begin();
    for (auto it = AllStudents.begin(); it != AllStudents.end(); it ++) {
        row.str("");        // Clear the stream
        row << std::setw(20) << std::left << it->FirstName << std::setw(20) << it->LastName
            << std::fixed << std::setprecision(2) << it->FinalResult << "\n";
        FWrite << row.str();    // Print
    }
    FWrite.close();
}
