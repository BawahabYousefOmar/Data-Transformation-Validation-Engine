#pragma once

#include <string>
#include <stdexcept>

using namespace std;

class Rule {
private:
    bool isRequired;           
    bool checkNumericRange;    
    float minVal;
    float maxVal;
    int expectedLength;        

    string requiredPrefix;     
    string requiredSubstring;  

public:
    //Default Constructor 
    Rule() {
        isRequired = false;
        checkNumericRange = false;
        minVal = -9999999.0f; //default value
        maxVal = 999999.0f;     //default value
        expectedLength = -1;
        requiredPrefix = "";
        requiredSubstring = "";
    }

    //Setters
    void setRequired(bool req) { isRequired = req; }

    void setMinVal(float min) {
        checkNumericRange = true; // Turn on range checking
        minVal = min;
    }

    void setMaxVal(float max) {
        checkNumericRange = true; // Turn on range checking
        maxVal = max;
    }

    void setExpectedLength(int len) { expectedLength = len; }
    void setRequiredPrefix(string prefix) { requiredPrefix = prefix; }
    void setRequiredSubstring(string sub) { requiredSubstring = sub; }

    // Validation function
    bool isValid(const string& value, string& errorMessage) const {
        //  Is it empty?
        if (value.empty()) {
            if (isRequired) {
                errorMessage = "Field is required but was left empty.";
                return false;
            }
            return true; // If it's empty but not required, it passes.
        }

        // check Expected Length
        if (expectedLength != -1 && (int)value.length() != expectedLength) {
            errorMessage = "Expected exactly " + to_string(expectedLength) + " characters.";
            return false;
        }

        // Check Required Prefix
        if (!requiredPrefix.empty()) {//if not contain the prefix, return false;
            if (value.substr(0, requiredPrefix.length()) != requiredPrefix) {
                errorMessage = "Must start with '" + requiredPrefix + "'.";
                return false;
            }
        }

        // Check Required Substring
        if (!requiredSubstring.empty()) {
            if (value.find(requiredSubstring) == string::npos) {//if not contain the sub, return false;
                errorMessage = "Must contain '" + requiredSubstring + "'.";
                return false;
            }
        }

        // Check Numeric Range
        if (checkNumericRange) {
            try {
                float numValue = stof(value);//try to convert to float
                if (numValue < minVal || numValue > maxVal) {
                    errorMessage = "Value " + value + " is out of range [" +
                        to_string(minVal) + " - " + to_string(maxVal) + "].";
                    return false;
                }
            }
            catch (...) {
                errorMessage = "Expected a numeric value, but got text.";
                return false;
            }
        }

        // If it survives all, it's valid!
        return true;
    }

    // getters
    bool getIsRequired() const { return isRequired; }
    bool getCheckNumericRange() const { return checkNumericRange; }
    float getMinVal() const { return minVal; }
    float getMaxVal() const { return maxVal; }
    int getExpectedLength() const { return expectedLength; }
    string getRequiredPrefix() const { return requiredPrefix; }
    string getRequiredSubstring() const { return requiredSubstring; }
};