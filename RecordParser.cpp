#include "RecordParser.h"
#include <iostream>

using namespace std;

RecordParser::RecordParser(HeaderProcessor& hp) : HeadProcess(hp) {
}

// Splits csv line by the given delimiter
DynamicArray<string> RecordParser::splitLine(const string& line, char delimiter) const {
    DynamicArray<string> parts;
    string current = "";
    bool insideQuotes = false;

    for (int i = 0; i < (int)line.size(); i++) {
        char c = line[i];

        if (c == '"') {
            insideQuotes = !insideQuotes;
        }
        else if (c == delimiter && !insideQuotes) {
            parts.add(current);
            current = "";
        }
        else {
            current += c;
        }
    }

    parts.add(current);
    return parts;
}

// Translates the raw header row
void RecordParser::setHeader(const string& headerRow) {
    standardHeaders = DynamicArray<string>();
	cout << "[DEBUG] setHeader called with header row: " << headerRow << "\n";
    DynamicArray<string> rawHeaders = splitLine(headerRow);
    cout << "[DEBUG] splitLine done, size: " << rawHeaders.getSize() << "\n";
    int columnCount = rawHeaders.getSize();

    for (int i = 0; i < columnCount; i++) {
        cout << "[DEBUG] processing column " << i << "\n";
        string raw = rawHeaders.get(i);
        cout << "[DEBUG] raw header: " << raw << "\n";
        string translated = HeadProcess.translate(raw);
        cout << "[DEBUG] translated: " << translated << "\n";

        if (translated.empty()) {
            if (m_unknownHeaderCb) {
                string resolved = m_unknownHeaderCb(raw);
                translated = resolved;
            }

        }

        standardHeaders.add(translated);
        cout << "[DEBUG] added to standardHeaders\n";
    }
    cout << "[RecordParser] Header set — "
         << columnCount << " column(s) found.\n";

    cout << "[DEBUG] setHeader complete\n";
}

// Maps each value to its standard key
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

const DynamicArray<HashMap<string>>& RecordParser::getRecords() const {
    return records;
}

const DynamicArray<string>& RecordParser::getStandardHeader() const
{
	return standardHeaders;
}

int RecordParser::getRecordCount() const {
    return records.getSize();
}

void RecordParser::reset() {
    records = DynamicArray<HashMap<string>>();
    standardHeaders = DynamicArray<string>();
    cout << "[RecordParser] Parser reset.\n";
}

void RecordParser::setUnknownHeaderCallback(UnknownHeaderCallback cb)
{
    this->m_unknownHeaderCb = cb;
}



