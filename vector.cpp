// Libraries

#include <iostream> // IO library
#include <iomanip> // IO manipulation library
#include <vector> // Vector
#include <fstream> // File read / write
#include <sstream> // Used to read string
#include <algorithm> // Used to sort vector
#include <random> // Library, used to generate random numbers


// Student Structure
struct StudentStructure {
    std::string FirstName, LastName;
    int ExamGrade;
    double TotalResult;
    std::vector<int> HomeworkVector;                    // Vector of homework grades
};

// Library to read data from file
void FileInput (std::vector<StudentStructure> &IndividualVector) {
    std::ifstream FRead ("kursiokai.txt");     // Open the file
    int HomeworkAmount = 0;

    if (FRead.good()) {  // If the file is good
        std::string FLine;
        std::getline(FRead, FLine);  // Read the first line of the file
        std::stringstream ss1 (FLine);   // Copy into stringstream
        std::string str1;
        while (ss1 >> str1)                   // Count the number of separate strings
            HomeworkAmount ++;
        HomeworkAmount -= 3;               // Ignore FirstName, LastName and ExamGrade strings
    }

    StudentStructure VectorStore;   // Initialize temporary vector
    int HWStore; // Temporary homework amount
    do {                                    // Read one students data into structure
        FRead >> VectorStore.FirstName >> VectorStore.LastName; // Read name and last name
        VectorStore.HomeworkVector.clear();                    // Clear the vector before filling it
        for (int i = 0; i < HomeworkAmount; i ++) {
            FRead >> HWStore; // Read grade
            VectorStore.HomeworkVector.push_back(HWStore); // Push homework grades
        }
        FRead >> VectorStore.ExamGrade; // Read exam grade
        IndividualVector.push_back(VectorStore); // Push into to the main vector
    } while (!FRead.eof());                    // Continue reading until the end of file
	FRead.close();                             // Close the file
}

double GradeAverage (int* HomeworkVector, int n) { // Calculate average homework grade
    double sum = 0;
    for (int i = 0; i < n; i ++)
        sum += HomeworkVector[i];
    return (sum / n);
}

double GradeMedian (int *HomeworkVector, int n) { // Calculate median grade
    double m;
    std::sort(HomeworkVector, HomeworkVector + n);
    n % 2 == 0 ? (m = 1.00 * (HomeworkVector[n / 2 - 1] + HomeworkVector[n / 2]) / 2) : m = HomeworkVector[n / 2];
    return m;
}

double Result (StudentStructure* IndividualVector, char type){
    double HomeworkGrade;
    if (!IndividualVector->HomeworkVector.empty())  // Check that the vector is not empty
        type == 'm' ? HomeworkGrade = GradeMedian(&IndividualVector->HomeworkVector[0], IndividualVector->HomeworkVector.size()) : HomeworkGrade = GradeAverage(&IndividualVector->HomeworkVector[0], IndividualVector->HomeworkVector.size());
    else HomeworkGrade = 0;
    return (0.4 * HomeworkGrade + 0.6 * IndividualVector->ExamGrade); // Return final result
}

// Validate users choice with 2 parameters
void ValidateChoice (char& input, char option1, char option2) {
    while (!(input == option1 || input == option2)) {
        std::cout << "Error. You can choose (" << option1 << "/" << option2 << ") \n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> input;
    }
}

// Validate users choice with 3 parameters
void ValidateChoice (char& input, char option1, char option2, char option3) {
    while (!(input == option1 || input == option2 || input == option3)) {
        std::cout << "Error. You can choose (" << option1 << "/" << option2  << "/" << option3 << ") \n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> input;
    }
}

// Check for numbers
void ValidateNumber (int& input, int lowest, int highest) {
    while (input < lowest || input > highest || std::cin.fail()) {
        std::cout << "Error. You can choose [" << lowest << " ; " << highest << "] \n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> input;
    }
}

void generateGrades (StudentStructure* IndividualVector) {
    char MoreGrades;
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(1, 10); // Define the range

    do {
        IndividualVector->HomeworkVector.push_back(distr(gen));                      // Generate grade 1 to 10
        std::cout << "\nGenerated grade: " << IndividualVector->HomeworkVector.back() << "\nGenerate another? (y/n) ";
        std::cin >> MoreGrades;
        ValidateChoice(MoreGrades, 'y', 'n');
    } while (MoreGrades == 'y');

    IndividualVector->ExamGrade = distr(gen);                                 // Generate exam grade 1 10
    std::cout << "\n\nGenerated exam grade: " << IndividualVector->ExamGrade << "\n";
}

void FileOutput(std::vector<StudentStructure> &IndividualVector, char AvgManChoice) {
    std::ofstream FWrite ("rezultatai.txt");                // Open the results' file

    FWrite << std::setw(20) << std::left << "First name" << std::setw(20) << "Last name" << "Final grade ";        // Header
    AvgManChoice == 'm' ? FWrite << "(Med.)\n" : FWrite << "(Avg.)\n";
    FWrite << "--------------------------------------------------------\n";
    for (int i = 0; i < IndividualVector.size(); i ++)                 // First name, last name, grade
        FWrite << std::setw(20) << std::left << IndividualVector[i].FirstName << std::setw(20) << IndividualVector[i].LastName << std::fixed << std::setprecision(2) << IndividualVector[i].TotalResult << "\n";

    FWrite.close();                                         // Close file
}

int main () {
    std::vector<StudentStructure> IndividualVector;                    // Student's vector
    char AvgManChoice;                            // m or a
    char FilGenMan;                            // f or g or m

    std::cout << "Please choose the input method:\n\n";
    std::cout<< "Read from file:\t  f\nGenerate: \t  g\nInput manually:\t  m\n";
    std::cin >> FilGenMan;                      // Read type
    ValidateChoice(FilGenMan, 'f', 'g', 'm');

    std::cout << "\nPlease choose the calculation method:\n";
    std::cout << "\nMedian:\t\tm\nAverage:\ta\n";
    std::cin >> AvgManChoice;                      // Read result type
    ValidateChoice(AvgManChoice, 'm', 'a');

    if (FilGenMan == 'm' || FilGenMan == 'g') {
        char MoreStudents = 'n';                // Input validation
        bool HWMore;
        int HWStore;
        StudentStructure VectorStore;                           // Temporary structure
        do {
            HWMore = true;
            VectorStore.HomeworkVector.clear();                        // Clear temporary structure

            std::cout << "\nStudent's full name:\n";
            std::cin >> VectorStore.FirstName >> VectorStore.LastName;  // Read first and last name

            if (FilGenMan == 'g')
                generateGrades(&VectorStore);              // Generate grades
            else {
                std::cout << "\nPlease enter the marks separated by return (ENTER). After the last one enter 0:\n";
                do {
                    std::cin >> HWStore;             // Read and validate homework grade
                    ValidateNumber(HWStore, 0, 10);
                    if (HWStore == 0)
                        HWMore = false;             // Halt once 0
                    else VectorStore.HomeworkVector.push_back(HWStore); // Add grade to vector
                } while (HWMore);                   // Continue while more grades
                VectorStore.HomeworkVector.shrink_to_fit();            // Shrink
                std::cout << "\nPlease enter the exam grade:\n";
                std::cin >> VectorStore.ExamGrade;              // Read exam grade
                ValidateNumber(VectorStore.ExamGrade, 1, 10);
            }
            IndividualVector.push_back(VectorStore);                      // Add the structure to the vector of student data

            std::cout << "\nWould you like to add another student? (y/n) ";
            std::cin >> MoreStudents;               // Check if more students
            ValidateChoice(MoreStudents, 'y', 'n');
        } while (MoreStudents == 'y');              // Continue while wanted to add more students
    } else FileInput(IndividualVector);                             // Read grades from file
    IndividualVector.shrink_to_fit();

    // Calculate TotalResult grades
    for (int i = 0; i < IndividualVector.size(); i ++)
        IndividualVector[i].TotalResult = Result(&IndividualVector[i], AvgManChoice);

    // Sort by first name
    std::sort(IndividualVector.begin(), IndividualVector.end(), [](StudentStructure &s1, StudentStructure &s2) {return s1.FirstName < s2.FirstName;});

    FileOutput(IndividualVector, AvgManChoice);
    std::cout << "\n\nThe results were written to file rezultatai.txt";

    IndividualVector.clear(); // Clear
    IndividualVector.shrink_to_fit(); // Shrink
    return 0;
}
