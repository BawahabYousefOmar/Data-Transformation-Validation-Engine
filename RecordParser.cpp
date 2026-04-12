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
	cout << "[DEBUG] setHeader called with header row: " << headerRow << "\n";
    DynamicArray<string> rawHeaders = splitLine(headerRow);
    cout << "[DEBUG] splitLine done, size: " << rawHeaders.getSize() << "\n";
    int columnCount = rawHeaders.getSize();

    bool unknownFound = false;

    for (int i = 0; i < columnCount; i++) {
        cout << "[DEBUG] processing column " << i << "\n";
        string raw = rawHeaders.get(i);
        cout << "[DEBUG] raw header: " << raw << "\n";
        string translated = HeadProcess.translate(raw);
        cout << "[DEBUG] translated: " << translated << "\n";

        if (translated.empty()) {
            if (!unknownFound) {
                cout << "[RecordParser] NOTE: Unknown columns will be skipped:\n";
                unknownFound = true;
            }
            cout << "   - \"" << raw << "\" (column " << i + 1 << ")\n";
        }

        standardHeaders.add(translated);   // "" = skip this column in parseLine
        cout << "[DEBUG] added to standardHeaders\n";
    }
    cout << "[RecordParser] Header set — "
         << columnCount << " column(s) found.\n";

    cout << "[DEBUG] setHeader complete\n";
}

// ----------------------------------------------------------------
// parseLine to be called per record when reading a file. 
// Maps each value to its standard key and appends to records.
// ----------------------------------------------------------------
void RecordParser::parseLine(const string& dataLine) {
    if (dataLine.empty())
        return;

    cout << "[DEBUG] parseLine called with: " << dataLine << "\n";

    DynamicArray<string> values = splitLine(dataLine);
    cout << "[DEBUG] splitLine done, values size: " << values.getSize() << "\n";

    int columnCount = standardHeaders.getSize();
    cout << "[DEBUG] columnCount: " << columnCount << "\n";

    HashMap<string> record;
    cout << "[DEBUG] HashMap created\n";

    for (int col = 0; col < columnCount; col++) {
        cout << "[DEBUG] col " << col << "\n";

        string key = standardHeaders.get(col);
        cout << "[DEBUG] key: " << key << "\n";

        if (key.empty()) continue;

        string value;
        if (col < values.getSize()) {
            value = HeadProcess.trim(values.get(col));
        }
        else {
            value = "";
        }
        cout << "[DEBUG] value: " << value << "\n";

        record.put(key, value);
        cout << "[DEBUG] put done\n";
    }

    records.add(record);
    cout << "[DEBUG] record added\n";
}
// ----------------------------------------------------------------
// getRecords
// ----------------------------------------------------------------
const DynamicArray<HashMap<string>>& RecordParser::getRecords() const {
    return records;
}

const DynamicArray<string>& RecordParser::getStandardHeader() const
{
	return standardHeaders;
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
