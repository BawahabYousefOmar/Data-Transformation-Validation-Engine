#include "RecordParser.h"
#include <iostream>

using namespace std;

// ----------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------
RecordParser::RecordParser(HeaderProcessor& hp) : HeadProcess(hp) {
    // records and standardHeaders are default-constructed 
}

// ----------------------------------------------------------------
// Splits a CSV line by the given delimiter.
// ----------------------------------------------------------------
DynamicArray<string> RecordParser::splitLine(const string& line, char delimiter) const {
    DynamicArray<string> parts;
    string current = "";
    bool insideQuotes = false;

    for (int i = 0; i < (int)line.size(); i++) {
        char c = line[i];

        if (c == '"') {
            insideQuotes = !insideQuotes;       //  quote mode
        }
        else if (c == delimiter && !insideQuotes) {
            parts.add(current);                // save completed part
            current = "";
        }
        else {
            current += c;
        }
    }

    parts.add(current);    // last part has no trailing delimiter
    return parts;
}

// ----------------------------------------------------------------
// setHeader
// Called once per file — translates the raw header row and stores
// the standard column order in standardHeaders.
// An empty string "" means that column is unknown and will be skipped.
// ----------------------------------------------------------------
void RecordParser::setHeader(const string& headerRow) {
    // Clear any previous file's header
    standardHeaders = DynamicArray<string>();

    DynamicArray<string> rawHeaders = splitLine(headerRow);
    int columnCount = rawHeaders.getSize();

    bool unknownFound = false;

    for (int i = 0; i < columnCount; i++) {
        string raw = rawHeaders.get(i);
        string translated = HeadProcess.translate(raw);

        if (translated.empty()) {
            if (!unknownFound) {
                cout << "[RecordParser] NOTE: Unknown columns will be skipped:\n";
                unknownFound = true;
            }
            cout << "   - \"" << raw << "\" (column " << i + 1 << ")\n";
        }

        standardHeaders.add(translated);   // "" = skip this column in parseLine
    }

    cout << "[RecordParser] Header set — "
         << columnCount << " column(s) found.\n";
}

// ----------------------------------------------------------------
// parseLine to be called per record when reading a file. 
// Maps each value to its standard key and appends to records.
// ----------------------------------------------------------------
void RecordParser::parseLine(const string& dataLine) {
    // skip empty lines. 
    if (dataLine.empty())
        return;

    DynamicArray<string> values = splitLine(dataLine);
    int columnCount = standardHeaders.getSize();

    HashMap<string> record;

    for (int col = 0; col < columnCount; col++) {
        string key = standardHeaders.get(col);

        // Skip columns that had no translation
        if (key.empty())
            continue;

		// avoid having less values than headers. If so, treat missing values as empty strings.
        string value;
        if (col < values.getSize()) {
            value = values.get(col);
        }
        else {
            value = "";
        }

        record.put(key, value);
    }

    records.add(record);
}

// ----------------------------------------------------------------
// getRecords
// ----------------------------------------------------------------
const DynamicArray<HashMap<string>>& RecordParser::getRecords() const {
    return records;
}

// ----------------------------------------------------------------
// getRecordCount
// ----------------------------------------------------------------
int RecordParser::getRecordCount() const {
    return records.getSize();
}

// ----------------------------------------------------------------
// reset
// Clears everything — useful if reusing the parser for a new session.
// ----------------------------------------------------------------
void RecordParser::reset() {
    records = DynamicArray<HashMap<string>>();
    standardHeaders = DynamicArray<string>();
    cout << "[RecordParser] Parser reset.\n";
}
