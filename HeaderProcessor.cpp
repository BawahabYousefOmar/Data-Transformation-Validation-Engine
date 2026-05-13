#include "HeaderProcessor.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

HeaderProcessor::HeaderProcessor() {
}

string HeaderProcessor::toLower(const string& str) const {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

string HeaderProcessor::trim(const string& str) const {
    int start = 0;
    while (start < (int)str.size() && isspace((unsigned char)str[start]))
        start++;

    int end = (int)str.size() - 1;
    while (end >= start && isspace((unsigned char)str[end]))
        end--;

    return str.substr(start, end - start + 1);
}

// Each line: raw_column=STANDARD_KEY. # starts a comment.
bool HeaderProcessor::loadFromFile(const string& filePath) {
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "[HeaderProcessor] ERROR: Could not open file: " << filePath << "\n";
        return false;
    }

    string line;
    int lineNumber = 0;
    int loadedCount = 0;

    while (getline(file, line)) {
        lineNumber++;

        line = trim(line);
        if (line.empty() || line[0] == '#')
            continue;

        int separatorPos = line.find('=');

        if (separatorPos == (int)string::npos) {
            cerr << "[HeaderProcessor] WARNING: Skipping malformed line "
                << lineNumber << ": \"" << line << "\"\n";
            continue;
        }

        string rawHeader = trim(line.substr(0, separatorPos));
        string standardKey = trim(line.substr(separatorPos + 1));

        if (rawHeader.empty() || standardKey.empty()) {
            cerr << "[HeaderProcessor] WARNING: Empty key or value on line "
                << lineNumber << ". Skipping.\n";
            continue;
        }

        translatorMap.put(toLower(rawHeader), standardKey);
        loadedCount++;

    }

    file.close();

    cout << "[HeaderProcessor] Loaded " << loadedCount
        << " header mappings from: " << filePath << "\n";
    return true;
}

string HeaderProcessor::translate(const string& rawHeader) const {
    string key = toLower(trim(rawHeader));

    string standardKey;
    if (translatorMap.get(key, standardKey))
        return standardKey;

    return "";
}

const HashMap<string>& HeaderProcessor::getTranslatorMap() const {
    return translatorMap;
}

int HeaderProcessor::getMappingCount() const {
    return translatorMap.getSize();
}

bool HeaderProcessor::addMappingToFile(const string& filePath, const string& rawHeader, const string& standardKey) {
    // 1. Open file in append mode
    ofstream file(filePath, ios::app);
    if (!file.is_open()) return false;

    // 2. Write the new mapping
    file << "\n" << rawHeader << "=" << standardKey;
    file.close();

    // 3. Update the live map so we don't have to reload the whole file
    translatorMap.put(toLower(trim(rawHeader)), standardKey);

    return true;
}