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

    // Reads headers.txt and populates the translator map.
    // Returns true on success, false if the file cannot be opened.
    bool loadFromFile(const string& filePath);
    bool addMappingToFile(const string& filePath, const string& rawHeader, const string& standardKey);

    // Translates a raw column name to its standard key.
    // Returns the standard key (e.g. "ID") if found.
    // Returns an empty string "" if the column is unknown.
    string translate(const string& rawHeader) const;

    const HashMap<string>& getTranslatorMap() const;


    // Returns the number of mappings loaded
    int getMappingCount() const;

    bool addMappingToFile(const string& filePath, const string& rawHeader, const string& standardKey);
};
