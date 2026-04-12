



#include <iostream>
#include <fstream>
#include <string>
#include "HeaderProcessor.h"
#include "RecordParser.h"
#include "HashMap.h"
#include "HashSet.h"

using namespace std;

// Standard keys printed in fixed order
//const string KEYS[] = { "ID", "Name", "GPA", "Email", "Phone" };
//const int KEY_COUNT = 5;

// Prints one record
void printRecord(const DynamicArray<string>& headers, const HashMap<string>& record, int index) {
    cout << "\n  [Record " << index + 1 << "]\n";
    for (int i = 0; i < headers.getSize(); i++) {
        string value;
        if (record.get(headers.get(i), value))
            cout << "    " << headers.get(i) << ": " << (value.empty() ? "(empty)" : value) << "\n";
        else
            cout << "    " << headers.get(i) << ": (missing)\n";
    }
}

// Prints all records currently in the parser
void printAllRecords(const RecordParser& parser) {
    const DynamicArray<HashMap<string>>& records = parser.getRecords();
    const DynamicArray<string>& headers = parser.getStandardHeader();

    cout << "[DEBUG] records size: " << records.getSize() << "\n";
    cout << "[DEBUG] headers size: " << headers.getSize() << "\n";

    for (int i = 0; i < records.getSize(); i++) {
        cout << "[DEBUG] getting record " << i << "\n";
        printRecord(headers, records.get(i), i);
        cout << "[DEBUG] printed record " << i << "\n";
    }
    cout << "\n";
}

// Simulates what Student 3's reader will do: feed the parser line by line
void feedFile(const string& filePath, RecordParser& parser) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "ERROR: Cannot open " << filePath << "\n";
        return;
    }
    cout << "[DEBUG] File opened successfully\n";
    string line;
    if (getline(file, line)) {

        cout << "[DEBUG] Header line: " << line << "\n";
        parser.setHeader(line);  // first line = header
        cout << "[DEBUG] setHeader done\n";
    }
    
    cout << "[feedFile] Processing file: " << filePath << "\n";
    while (getline(file, line)) parser.parseLine(line); // rest = data

    file.close();
}

int main() {

    cout << "===========================================\n";
    cout << "   TESTING DATA TRANSFORMATION ENGINE      \n";
    cout << "===========================================\n\n";

    // ---------------------------------------------------------
    // 1. Testing HashMap (Validation Rules)
    // ---------------------------------------------------------
    cout << "--- Testing HashMap (Validation Rules) ---\n";

    // We will map a string (Field Name) to a string (Validation Rule)
    HashMap<string> rulesMap;

    // Test Insertion // later we will use struct functions to process the rules, but for now we will just use strings to represent them
    rulesMap.put("ID", "Must be 9 digits");
    rulesMap.put("GPA", "Between 0.0 and 4.0");
    rulesMap.put("Name", "Cannot be empty");

    cout << "Current Map Size: " << rulesMap.getSize() << "\n";

    // Test Contains & Get (Pass by Reference)
    string gpaRule;
    if (rulesMap.contains("GPA")) {
        rulesMap.get("GPA", gpaRule);
        cout << "Rule for GPA: " << gpaRule << "\n";
    }

    // Test Update
    rulesMap.put("GPA", "Between 0.0 and 4.0 (Strict Enforcement)");
    rulesMap.get("GPA", gpaRule);
    cout << "Updated Rule for GPA: " << gpaRule << "\n";

    // Test Missing Key
    if (!rulesMap.contains("Age")) {
        cout << "Age rule not found. (Correct behavior)\n";
    }

    cout << "\n";

    // ---------------------------------------------------------
    // 2. Testing HashSet (Duplicate ID Detection)
    // ---------------------------------------------------------
    cout << "--- Testing HashSet (Duplicate ID Detection) ---\n";
    HashSet<string> idSet;

    // Test Insertion (Using standard 900-series university IDs)
    bool added1 = idSet.add("900221101");
    bool added2 = idSet.add("900221102");
    cout << "Added ID 900221101? " << (added1 ? "Yes" : "No") << "\n";
    cout << "Added ID 900221102? " << (added2 ? "Yes" : "No") << "\n";

    // Test Duplicate Detection
    bool addedDuplicate = idSet.add("900221101");
    cout << "Added duplicate ID 900221101? " << (addedDuplicate ? "Yes" : "No") << " (Should be No)\n";

    // Test Contains
    cout << "Contains 900221102? " << (idSet.contains("900221102") ? "Yes" : "No") << "\n";
    cout << "Contains 900221199? " << (idSet.contains("900221199") ? "Yes" : "No") << " (Should be No)\n";

    cout << "\nTotal Unique IDs Tracked: " << idSet.getSize() << "\n";

    cout << "\n===========================================\n";
    cout << "          ALL TESTS COMPLETED              \n";
    cout << "===========================================\n\n\n";

    cout << "=== Translation Layer Test ===\n\n";

    // -- Load translator --
    HeaderProcessor hp;
    if (!hp.loadFromFile("headers.txt"))
        return 1;
    cout << "Mappings loaded: " << hp.getMappingCount() << "\n\n";

    // -- Spot check --
    cout << "--- translate() checks ---\n";
    string checks[] = { "stud_id", "FULL_NAME", "cgpa", "e_mail", "telephone", "department" };
    for (int i = 0; i < 6; i++) {
        string result = hp.translate(checks[i]);
        cout << "  \"" << checks[i] << "\" -> "
            << (result.empty() ? "(unknown)" : result) << "\n";
    }

    RecordParser parser(hp);

    // -- File 1: standard column order --
    cout << "\n--- File 1: students.csv ---\n";
    feedFile("students.csv", parser);
    printAllRecords(parser);

    // -- File 2: different column order to test order logic --

    feedFile("students2.csv", parser);
    printAllRecords(parser);

    cout << "Total records: " << parser.getRecordCount() << "\n";
    return 0;
}





/////////////////////////////////////////////////

