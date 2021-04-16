#include "deque.h" // Deque lib

void GenerateGradesDeque (StudentContainer* AllStudents, char FinalChoice) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(1, 10);

    char moreGrades;
    std::deque<int> HW;
    std::cout << "\nGenerating grades\n\n";
    do {
        HW.push_back(random10(mt)); // Generating random grade
        std::cout << "Generated grade: " << HW.back() << "\nGenerate another? (y/n)";
        std::cin >> moreGrades;
        ValidateOption(moreGrades, 'y', 'n');
    } while (moreGrades == 'y');

    int ExamGrade = random10(mt);        // Generating exam grade
    std::cout << "Generated exam grade: " << ExamGrade << "\n";
    
    // Calculating the FinalResult grade
    AllStudents->FinalResult = FinalDeque(HW, ExamGrade, FinalChoice);
}

double AverageDeque (std::deque<int> &HW, int n) {
    double sum = 0;
    for (int i = 0; i < n; i ++)
        sum += HW[i];
    return (sum / n);
}

double MedianDeque (std::deque<int> &HW, int n) {
    double m;
    std::sort(HW.begin(), HW.end());
    n % 2 == 0 ? (m = 1.00 * (HW[n / 2 - 1] + HW[n / 2]) / 2) : m = HW[n / 2];
    return m;
}

double FinalDeque (std::deque<int> &HW, int ExamGrade, char type) {
    double HWTotal;
    if (!HW.empty())  // If not empty
        type == 'm' ? HWTotal = MedianDeque(HW, HW.size()) : HWTotal = AverageDeque(HW, HW.size());
    else HWTotal = 0;
    return (0.4 * HWTotal + 0.6 * ExamGrade);
}

void GetDataDeque (std::deque<StudentContainer> &AllStudents, char DataChoice, char FinalChoice) {
    char StudentsMore = 'n';
    bool HWMore;
    int HWTemp;        // Temporary grade
    StudentContainer tmp;      // Temporary structure
    std::deque<int> HW;// Deque of grades
    int ExamGrade;
    do {
        HWMore = true;
        HW.clear();    // Clear

        std::cout << "\nStudent's full name:\n";
        std::cin >> tmp.FirstName >> tmp.LastName;

        if (DataChoice == 'g')
            GenerateGradesDeque(&tmp, FinalChoice); // Generate grades
        else {
            std::cout << "\nEnter grades, 0 after the last one:\n";
            do {
                std::cin >> HWTemp;
                ValidateNumber(HWTemp, 0, 10);
                if (HWTemp == 0)
                    HWMore = false;             // Halt if 0
                else HW.push_back(HWTemp);      // Add the grade
            } while (HWMore);                   // Continue
            HW.shrink_to_fit();

            std::cout << "\nExam grade:\n";
            std::cin >> ExamGrade;
            ValidateNumber(ExamGrade, 1, 10);
            tmp.FinalResult = FinalDeque(HW, ExamGrade, FinalChoice);
        }
        AllStudents.push_back(tmp);                      // Add to the container

        std::cout << "\nAdd another student? (y/n) \n";
        std::cin >> StudentsMore;
        ValidateOption(StudentsMore, 'y', 'n');
    } while (StudentsMore == 'y');
}

void FileReadDeque (std::deque<StudentContainer> &AllStudents, std::string FileName, char FinalChoice) {
    std::ifstream FRead (FileName);

    int HWNumber = 0;
    std::string header;
    std::getline(FRead, header);            // Get first line of the file
    std::istringstream firstRow (header); // Copy to stringstream
    std::string str;
    while (firstRow >> str)              // Count the strings
        HWNumber ++;
    HWNumber -= 3;                        // Ignore name, last name and grade

    StudentContainer tmp;
    int HWTemp, ExamGrade;
    std::string row;
    std::istringstream dataRow;
    std::deque<int> HW;
    while (std::getline(FRead, row)) {      // Continue until EOF
        dataRow.clear();
        dataRow.str(row);
        dataRow >> tmp.FirstName >> tmp.LastName;
        HW.clear();                      // Clear
        for (int i = 0; i < HWNumber; i ++) {
            dataRow >> HWTemp;
            HW.push_back(HWTemp);
        }
        dataRow >> ExamGrade;
        tmp.FinalResult = FinalDeque(HW, ExamGrade, FinalChoice);
        AllStudents.push_back(tmp);               // Push to the container
    }
	FRead.close();
}

void GroupStudentsDeque (std::deque<StudentContainer> &AllStudents, std::deque<StudentContainer> &GoodStudents, std::deque<StudentContainer> &BadStudents, int SortStrategy) {
    // Sort students
    std::sort(AllStudents.begin(), AllStudents.end(), [](StudentContainer &s1, StudentContainer &s2) {return s1.FinalResult < s2.FinalResult;}); 

    // Count bad students
    int BadNumber = 0;
    while (AllStudents[BadNumber].FinalResult < 5.0 && BadNumber != AllStudents.size())
        BadNumber ++;

    std::copy(AllStudents.begin() + BadNumber, AllStudents.end(), std::back_inserter(GoodStudents));       // Copy good students
    if (SortStrategy == 1) {
        std::copy(AllStudents.begin(), AllStudents.begin() + BadNumber, std::back_inserter(BadStudents)); // Copy bad students
        AllStudents.clear();
    } else AllStudents.resize(BadNumber);  // Resize the main vector
    AllStudents.shrink_to_fit();
}

void SortDeque (std::deque<StudentContainer> &AllStudents, std::deque<StudentContainer> &GoodStudents, char SortChoice) {
    if (SortChoice == 'n') {
        std::sort(AllStudents.begin(), AllStudents.end(), [](StudentContainer &s1, StudentContainer &s2) {return s1.FirstName < s2.FirstName;});
        std::sort(GoodStudents.begin(), GoodStudents.end(), [](StudentContainer &s1, StudentContainer &s2) {return s1.FirstName < s2.FirstName;});
    } else if (SortChoice == 'l') {
        std::sort(AllStudents.begin(), AllStudents.end(), [](StudentContainer &s1, StudentContainer &s2) {return s1.LastName < s2.LastName;});
        std::sort(GoodStudents.begin(), GoodStudents.end(), [](StudentContainer &s1, StudentContainer &s2) {return s1.LastName < s2.LastName;});
    }
}

void WriteFileDeque (std::deque<StudentContainer> &AllStudents, char FinalChoice, std::string FileName) {
    std::ofstream FWrite (FileName);
    std::ostringstream row ("");

    // Print header
    row << std::setw(20) << std::left << "First name" << std::setw(20) << "Last name" << "Final grade ";
    FWrite << row.str();
    FinalChoice == 'm' ? FWrite << "(Med.)\n" : FWrite << "(Avg.)\n";
    FWrite << "--------------------------------------------------------\n";

    // Print student data
    for (int i = 0; i < AllStudents.size(); i ++) {
        row.str("");        // Clear the stream
        row << std::setw(20) << std::left << AllStudents[i].FirstName << std::setw(20) << AllStudents[i].LastName
            << std::fixed << std::setprecision(2) << AllStudents[i].FinalResult << "\n";
        FWrite << row.str();    // Print
    }
    FWrite.close();
}
