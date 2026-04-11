#include "HeaderProcessor.h"
#include <fstream>
#include <iostream>
#include <algorithm>   // for transform (toLower)

using namespace std;

// ----------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------
HeaderProcessor::HeaderProcessor() {
    // translatorMap is default-constructed 
}

// ----------------------------------------------------------------
// Private Helpers
// ----------------------------------------------------------------

string HeaderProcessor::toLower(const string& str) const {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

string HeaderProcessor::trim(const string& str) const {
    // Find the first non-whitespace character
    int start = 0;
    while (start < (int)str.size() && isspace((unsigned char)str[start]))
        start++;

    // Find the last non-whitespace character
    int end = (int)str.size() - 1;
    while (end >= start && isspace((unsigned char)str[end]))
        end--;

    return str.substr(start, end - start + 1);
}

// ----------------------------------------------------------------
// loadFromFile
// Reads headers.txt line by line.
// Expected format per line:   raw_name=STANDARD_KEY
// Lines starting with '#' or empty lines are skipped.
// ----------------------------------------------------------------
bool HeaderProcessor::loadFromFile(const string& filePath) {
    
}

// ----------------------------------------------------------------
// translate
// Looks up the raw column name (case-insensitive) in the map.
// Returns the standard key, or "" if not found.
// ----------------------------------------------------------------
string HeaderProcessor::translate(const string& rawHeader) const {
	return "";
}

// ----------------------------------------------------------------
// getTranslatorMap
// ----------------------------------------------------------------
const HashMap<string>& HeaderProcessor::getTranslatorMap() const {
    return translatorMap;
}

// ----------------------------------------------------------------
// getMappingCount
// ----------------------------------------------------------------
int HeaderProcessor::getMappingCount() const {
    return translatorMap.getSize();
}
