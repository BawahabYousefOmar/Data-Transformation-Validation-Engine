#pragma once

#include <string>
#include "HashMap.h"

using namespace std;

// ============================================================
//  HeaderProcessor
//  Responsibility: Load headers.txt and provide a translation
//  service that maps any messy column name to its standard key.
//
//  Standard keys: ID, Name, GPA, Email, Phone
// ============================================================

class HeaderProcessor {
private:
    // Stores  messy_name -> STANDARD_KEY   (e.g. "stud_id" -> "ID")
    HashMap<string> translatorMap;

    // Converts a string to lowercase for case-insensitive matching
    string toLower(const string& str) const;

    // Strips leading/trailing whitespace from a string
    string trim(const string& str) const;

public:
    HeaderProcessor(); // default constructor

    // Reads headers.txt and populates the translator map.
    // Returns true on success, false if the file cannot be opened.
    bool loadFromFile(const string& filePath);

    // Translates a raw column name to its standard key.
    // Returns the standard key (e.g. "ID") if found.
    // Returns an empty string "" if the column is unknown.
    string translate(const string& rawHeader) const;

    // Returns the fully built translator map (read-only reference).
    // Useful if another component needs direct access to the map.
    const HashMap<string>& getTranslatorMap() const;

    // Returns the number of mappings loaded
    int getMappingCount() const;
};
