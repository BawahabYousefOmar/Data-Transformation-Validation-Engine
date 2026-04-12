#include <string>
#include <iostream>

using namespace std;

// define a ValidationFunc is a pointer to a function taking a string and returning a bool.
typedef bool (*ValidationFunc)(const string&);


class Rule {
    string description;        // description of the rule
    ValidationFunc checkLogic; // The function pointer

    // Default constructor 
    Rule() : description("No rule"), checkLogic(nullptr) {}

    // Parameterized constructor
    Rule(string desc, ValidationFunc func) : description(desc), checkLogic(func) {}

    // Helper method to safely execute the rule
    bool isValid(const string& val) const {
        if (checkLogic == nullptr) {
            return true; // Or false, depending on if you want empty rules to pass or fail
        }
        return checkLogic(val); // Execute the function pointed to!
    }
};

// ----------------------- Rule Functions ---------------------------------

bool validateID(const string& val) {
    // Check length
    if (val.length() != 9) return false;

    // Check prefix
    if (val.substr(0, 3) != "900") return false;

    // Ensure all characters are digits
    for (char c : val) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool validateGPA(const string& val) {
    try {
        float gpa = stof(val); // Convert string to float
        return (gpa >= 0.0f && gpa <= 4.0f);
    }
    catch (...) {
        // stof throws an exception if the string isn't a number or is empty
        return false;
    }
}

bool validateName(const string& val) {
    //check that it isn't empty
    return !val.empty();
}