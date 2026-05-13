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

    DynamicArray<string> splitLine(const string& line, char delimiter = ',') const;

public:
    RecordParser(HeaderProcessor& hp);

    void setHeader(const string& headerRow);

    void parseLine(const string& dataLine);

    const DynamicArray<HashMap<string>>& getRecords() const;

    const DynamicArray<string>& getStandardHeader() const;

    int getRecordCount() const;

    void reset();

    void setUnknownHeaderCallback(UnknownHeaderCallback cb);
};
