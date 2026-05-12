#pragma once

#include <string>
#include "DynamicArray.h"
#include "HashMap.h"
#include "HeaderProcessor.h"

using namespace std;

// ============================================================
//  RecordParser
//  Responsibility: Receive raw CSV lines, translate column header using the
//  HeaderProcessor, and accumulate records with standardized headers.
//
//  Each record is stored as a HashMap<string> with standard
//  keys: ID, Name, GPA, Email, Phone.
// ============================================================

class RecordParser {
private:
    HeaderProcessor& HeadProcess;            // reference to the loaded translator
    DynamicArray<string> standardHeaders;  // translated column order for current file
    DynamicArray<HashMap<string>> records; // all accumulated records across all files

    // Splits a CSV line into parts, handles quoted fields e.g. "Smith, John"
    DynamicArray<string> splitLine(const string& line, char delimiter = ',') const;

public:
    // Constructor — takes a ready HeaderProcessor to use for translating headers.
    RecordParser(HeaderProcessor& hp);

    // Called once per file with the first (header) line.
    // Unknown columns are reported to console and marked to be skipped (we later will add user input for unkown colums).
    void setHeader(const string& headerRow);

    // Called once per data row by Student 3's file reader.
    // Translates and appends one clean record to the internal records array.
    // Skips empty lines silently.
    void parseLine(const string& dataLine);

    // Returns all accumulated records 

    const DynamicArray<HashMap<string>>& getRecords() const;

    
    const DynamicArray<string>& getStandardHeader() const;


    // Returns the total number of records accumulated.
    int getRecordCount() const;

    // Clears all records and resets the header.
    
    void reset();
};
