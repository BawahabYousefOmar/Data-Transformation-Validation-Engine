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
 
}

string HeaderProcessor::trim(const string& str) const {
 
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
