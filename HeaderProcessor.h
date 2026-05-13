#pragma once

#include <string>
#include "HashMap.h"

using namespace std;

// Loads headers.txt: raw column name -> standard field (ID, Name, GPA, Email, Phone).

class HeaderProcessor {
private:
    HashMap<string> translatorMap;

    string toLower(const string& str) const;

public:
    HeaderProcessor();

    bool loadFromFile(const string& filePath);
    bool addMappingToFile(const string& filePath, const string& rawHeader, const string& standardKey);

    string translate(const string& rawHeader) const;

    const HashMap<string>& getTranslatorMap() const;
    int getMappingCount() const;

    // Shared with RecordParser for trimming cell values
    string trim(const string& str) const;
};
