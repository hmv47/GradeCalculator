// Libraries

#include <iostream> // IO library
#include <iomanip> // IO manipulation library
#include <random> // Library, used to generate random numbers
#include <algorithm> // Used to sort vector
#include <vector> // Vector


// Student Structure
struct StudentStructure {
    std::string FirstName, LastName; // Student's name
    int ExamGrade; // Exam grade
    std::vector<int> HomeworkVector;    // Vector of homework grades
};

// Average grade calculation
double GradeAverage (int* HomeworkVector, int n) {
    double sum = 0; // Initial sum
    for (int i = 0; i < n; i ++)
        sum += HomeworkVector[i]; // Summing up all vector grades
    return (sum / n); // Return result
}


// Median grade calculation
double GradeMedian (int *HomeworkVector, int n) {
    double m;
    n % 2 == 0 ? (m = 1.00 * (*(HomeworkVector + (n / 2) - 1) + *(HomeworkVector + (n / 2))) / 2) : m = *(HomeworkVector + (n / 2));
    return m; // Return result
}

// Final result
double Result (StudentStructure* IndividualVector, char type){
    double HomeworkGrade;
    if (!IndividualVector->HomeworkVector.empty())  // Check that homework vector != empty
        type == 'm' ? HomeworkGrade = GradeMedian(&IndividualVector->HomeworkVector[0], IndividualVector->HomeworkVector.size()) : HomeworkGrade = GradeAverage(&IndividualVector->HomeworkVector[0], IndividualVector->HomeworkVector.size()); // Calulate result depending on the choice
    else HomeworkGrade = 0; // HomeworkGrade is 0 if vector is empty
    return (0.4 * HomeworkGrade + 0.6 * IndividualVector->ExamGrade);
}

// Checking the choice
void ValidateChoice (char& input, char option1, char option2) {
    while (!(input == option1 || input == option2)) {
        std::cout << "You can choose either " << option1 << " or " << option2 << std::endl << "Please try again: ";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> input;
    }
}

// Checking if entered numbers are valit
void ValidateNumber (int& input, int lowest, int highest) {

         while (input < lowest || input > highest || std::cin.fail()) { // Meant for grades
            std::cout << "The number can be from " << lowest << " to " << highest << std::endl << "Please try again: ";
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> input;
            }
}


void generateGrades (StudentStructure* IndividualVector) {
    char moreGrades;
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(1, 10); // Define the range
    do {
        IndividualVector->HomeworkVector.push_back(distr(gen)); // Generate a random homework
        std::cout << "The grade is: " << IndividualVector->HomeworkVector.back() << std::endl  << "Generate another? (y/n) ";
        std::cin >> moreGrades;
        ValidateChoice(moreGrades, 'y', 'n');
    } while (moreGrades == 'y');

    IndividualVector->ExamGrade =  distr(gen);  // Generate a random exam grade
    std::cout << "\nThe exam grade is: " << IndividualVector->ExamGrade << "\n";
}

int main () {
    std::vector<StudentStructure> IndividualVector; // Vector structure
    char AvgManChoice; // a or m
    char MoreStudents; // y or n
    char RanManChoice; // y or n
    bool MoreGrades; // whether or not more grades will be added
    int HomeworkStore; // temporary int for homework mark

    do {
        StudentStructure VectorStore; // temporary structure for one student
        MoreGrades = true;
        std::cout << "\nEnter student's first and last name:\n";
        std::cin >> VectorStore.FirstName;
        std::cin >> VectorStore.LastName;

        std::cout << "\n\nWould you like to generate marks randomly (y/n): ";
        std::cin >> RanManChoice;
        ValidateChoice(RanManChoice, 'y', 'n');
        if (RanManChoice == 'y')
            generateGrades(&VectorStore);              // Generate homework and exam grades
        else {
            std::cout << "\n\nPlease enter the marks separated by return (ENTER). After the last one enter 0: \n";
            do {
                std::cin >> HomeworkStore;
                ValidateNumber(HomeworkStore, 0, 10); // validate the grade
                if (HomeworkStore == 0)
                    MoreGrades = false; // halt loop
                else VectorStore.HomeworkVector.push_back(HomeworkStore); // add the grade to temporary vector
            } while (MoreGrades);
            std::cout << "\nPlease enter the exam grade: ";
            std::cin >> VectorStore.ExamGrade;
            ValidateNumber(VectorStore.ExamGrade, 1, 10);
        }
        std::sort(VectorStore.HomeworkVector.begin(), VectorStore.HomeworkVector.end());
        IndividualVector.push_back(VectorStore); // push to permanent structure

        std::cout << "\nWould you like to add more students? (y/n): ";
        std::cin >> MoreStudents;
        ValidateChoice(MoreStudents, 'y', 'n');
    } while (MoreStudents == 'y');
    IndividualVector.shrink_to_fit(); // clear up

    std::cout << "\nGenerate the result by median or average (m/a) ";
    std::cin >> AvgManChoice;   // Read and validate the entered type of final grade
    ValidateChoice(AvgManChoice, 'm', 'v');

    // Calculate final grades and print results
    std::cout << "\nLast name\t\tFirst name\t\tMark ";
    AvgManChoice == 'm' ? std::cout << "(Med.)\n" : std::cout << "(Avg.)\n" ;
    for (int i = 0; i < IndividualVector.size(); i ++)
        std::cout << IndividualVector[i].LastName << "\t\t" << IndividualVector[i].FirstName << "\t\t" << std::fixed << std::setprecision(2) << Result(&IndividualVector[i], AvgManChoice) << "\n";

    IndividualVector.clear(); // clear vector
    IndividualVector.shrink_to_fit();
    return 0;
}
