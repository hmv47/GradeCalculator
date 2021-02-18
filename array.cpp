// Libraries

#include <iostream> // IO library
#include <iomanip> // IO manipulation library
#include <random> // Library, used to generate random numbers
#include <algorithm> // Used to sort array


// Student Structure
struct StudentStructure {
    std::string FirstName, LastName; // Student's name
    int ExamGrade; // Exam grade
    int *HomeworkArray = (int*)malloc(sizeof(int) * 1); // Dynamic C array initialized at size 1 to store grades
    int HomeworkAmount = 0; // Variable to store the amount of homework grades
};

// Average grade calculation
double GradeAverage (int* HomeworkArray, int n) {
    if (n != 0) { // Calculate average only if the amount is more than 0;
    double sum = 0; // Initial sum
    for (int i = 0; i < n; i ++)
        sum += HomeworkArray[i]; // Summing up all array grades
    return (sum / n); //Return result if n != 0
        }
        else return 0; // Return result if n = 0
}

// Median grade calculation
double GradeMedian (int* HomeworkArray, int n) {
    if (n != 0) { // Calculate median only if the amount is more than 0;
    double m;
    std::sort(HomeworkArray, HomeworkArray + n); // Sort the array ascending
    n % 2 == 0 ? (m = 1.00 * (*(HomeworkArray + (n / 2) - 1) + *(HomeworkArray + (n / 2))) / 2) : m = *(HomeworkArray + (n / 2)); // get median value depending on the amount of values
    return m; //Return result if n != 0
	}
	else return 0; // Return result if n = 0
}

// Final result
double Result (StudentStructure* IndividualArray, int i, char type){
    double TotalHomeworkGrade;
    type == 'm' ? TotalHomeworkGrade = GradeMedian(IndividualArray[i].HomeworkArray, IndividualArray[i].HomeworkAmount) : TotalHomeworkGrade = GradeAverage(IndividualArray[i].HomeworkArray, IndividualArray[i].HomeworkAmount); // Calulate result depending on the choice
    return (0.4 * TotalHomeworkGrade + 0.6 * IndividualArray[i].ExamGrade); // Return result
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

// Generating random grades
void generateGrades (StudentStructure* IndividualArray, int i) {
    char MoreGradesGen;
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(1, 10); // Define the range
    do {
        IndividualArray[i].HomeworkArray[IndividualArray[i].HomeworkAmount] = distr(gen);  // Generate random grade
        std::cout << "The grade is: " << IndividualArray[i].HomeworkArray[IndividualArray[i].HomeworkAmount] << std::endl << "Generate another? (y/n) ";
        IndividualArray[i].HomeworkAmount ++; // Increase homework counter
        IndividualArray[i].HomeworkArray = (int*)realloc(IndividualArray[i].HomeworkArray, sizeof(int) * IndividualArray[i].HomeworkAmount + 1); // Expand array by one
        std::cin >> MoreGradesGen;
        ValidateChoice(MoreGradesGen, 'y', 'n');
    } while (MoreGradesGen == 'y');

    IndividualArray[i].ExamGrade = distr(gen); // Generate exam grade
    std::cout << std::endl;
    std::cout << "The exam grade is: " << IndividualArray[i].ExamGrade << std::endl;
}

int main () {
    StudentStructure *IndividualArray = new StudentStructure[1];            // Dynamic array of StudentStructure
    char AvgMedChoice; // m or a
    char RanManChoice; // y or n
    int HomeworkGrade = 0; // Total homework grade
    bool MoreGrades;
    bool MoreStudents;
    int ProcessedStudentNumber = 0; // Number of students


    do {
        MoreGrades = true; // At least one grade per student unless provided 0
        std::cout << "\nEnter student's first and last name: \n";
        std::cin >> IndividualArray[ProcessedStudentNumber].FirstName;
        std::cin >> IndividualArray[ProcessedStudentNumber].LastName;

        std::cout << "\n\nWould you like to generate marks randomly (y/n): ";
        std::cin >> RanManChoice; // Check choice
        ValidateChoice(RanManChoice, 'y', 'n');
        if (RanManChoice == 'y')
            generateGrades(IndividualArray, ProcessedStudentNumber); // Generate homework and exam marks
        else {
            std::cout << "\n\nPlease enter the marks separated by return (ENTER). After the last one enter 0: " << std::endl;
            do {
                std::cin >> HomeworkGrade;              // Validate
                ValidateNumber(HomeworkGrade, 0, 10);
                if (HomeworkGrade == 0)
                    MoreGrades = false;              // End if 0
                else {
                    IndividualArray[ProcessedStudentNumber].HomeworkArray[IndividualArray[ProcessedStudentNumber].HomeworkAmount] = HomeworkGrade; // Add the grade to the array
                    IndividualArray[ProcessedStudentNumber].HomeworkAmount++; // Increase the number of grades
                    IndividualArray[ProcessedStudentNumber].HomeworkArray = (int*)realloc(IndividualArray[ProcessedStudentNumber].HomeworkArray, sizeof(int) * IndividualArray[ProcessedStudentNumber].HomeworkAmount + 1); // Increase the array by 1
                }

            } while (MoreGrades);                    // Continue the loop while more grades are added

            std::cout << "\nPlease enter the exam grade: " << std::endl;;
            std::cin >> IndividualArray[ProcessedStudentNumber].ExamGrade;              // Read and validate the entered grade
            ValidateNumber(IndividualArray[ProcessedStudentNumber].ExamGrade, 1, 10);
        }
        ProcessedStudentNumber ++;                                   // Increase the number of processed students
        std::cout << "\nWould you like to add more students? (y/n): ";
        char temp;
        std::cin >> temp;                // Read and validate if it's wanted to enter data of more students
        ValidateChoice(temp, 'y', 'n');
        if (temp == 'y') {
            MoreStudents = true;
            StudentStructure *TempArray = new StudentStructure[ProcessedStudentNumber + 1]; // Create a larger array
            std::copy(IndividualArray, IndividualArray + ProcessedStudentNumber, TempArray); // Copy the array
            delete[] IndividualArray; // Delete old array
            IndividualArray = TempArray; // Rename
            }
            else MoreStudents = false; // Halt
    } while (MoreStudents);

    std::cout << "\nGenerate the result by median or average (m/a)";
    std::cin >> AvgMedChoice;                      // Read and validate the entered type of final grade (GradeAverage or GradeMedian)
    ValidateChoice(AvgMedChoice, 'm', 'a');

    // Calculate final grades and print results
    std::cout << "\nLast name\t\tFirst name\t\tMark ";
    AvgMedChoice == 'm' ? std::cout << "(Med.)\n" : std::cout << "(Avg.)\n" ; // Print result depending on choice
    for (int i = 0; i < ProcessedStudentNumber; i ++)
        std::cout << IndividualArray[i].LastName << "\t\t" << IndividualArray[i].FirstName << "\t\t" << std::fixed << std::setprecision(2) << Result(IndividualArray, i, AvgMedChoice) << "\n";
    delete[] IndividualArray; // Crear memory and delete array
    return 0;
}
