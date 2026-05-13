#pragma once

#include <string>
#include <functional>

#include "DynamicArray.h"
#include "HashMap.h"
#include "HeaderProcessor.h"

using namespace std;

// CSV reader: maps header row through HeaderProcessor, builds one HashMap per data row.

using UnknownHeaderCallback = function<string(const string& rawColumn)>;


//// Callback type: given an unknown raw column name, returns:
//   - the standard key to use ("ID", "Name", etc.), OR
//   - "" to skip the column
using UnknownHeaderCallback = function<string(const string& rawColumn)>;


class RecordParser {
private:
    HeaderProcessor& HeadProcess;
    DynamicArray<string> standardHeaders;
    DynamicArray<HashMap<string>> records;

    UnknownHeaderCallback m_unknownHeaderCb = nullptr;



    // Splits a CSV line into parts, handles quoted fields e.g. "Smith, John"
    DynamicArray<string> splitLine(const string& line, char delimiter = ',') const;

public:
    RecordParser(HeaderProcessor& hp);

    void setHeader(const string& headerRow);

    void parseLine(const string& dataLine);

    const DynamicArray<HashMap<string>>& getRecords() const;


    const DynamicArray<string>& getStandardHeader() const;

    int getRecordCount() const;

    // Clears all records and resets the header.

    void reset();

    // Add a setter for the callback:
    void setUnknownHeaderCallback(UnknownHeaderCallback cb);
};
