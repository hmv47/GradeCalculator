#include "validation.h"

template <typename T>
void RepeatInput(T& input) {
    std::cin.clear();
    std::cin.ignore(256,'\n');
    std::cin >> input;
}

// Check option choice (2 choiced)
void ValidateOption (char& input, char option1, char option2) {
    while (!(input == option1 || input == option2)) {
        std::cout << "Error. You can choose: (" << option1 << "/" << option2 << ") \n";
        RepeatInput(input);
    }
}

// Check option choice (3 choiced)
void ValidateOption (char& input, char option1, char option2, char option3) {
    while (!(input == option1 || input == option2 || input == option3)) {
        std::cout << "Error. You can choose: (" << option1 << "/" << option2  << "/" << option3 << ") \n";
        RepeatInput(input);
    }
}

// Check for number in range
void ValidateNumber (int& input, int lowest, int highest) {
    while (input < lowest || input > highest || std::cin.fail()) {
        std::cout << "Error. You can choose between: [" << lowest << " ; " << highest << "] \n";
        RepeatInput(input);
    }
}
