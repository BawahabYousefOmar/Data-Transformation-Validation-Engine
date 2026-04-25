#include <iostream>
#include <fstream>
#include <string>
#include "HeaderProcessor.h"
#include "RecordParser.h"
#include "HashMap.h"
#include "HashSet.h"
#include "Stack.h"

using namespace std;

// Standard keys printed in fixed order
//const string KEYS[] = { "ID", "Name", "GPA", "Email", "Phone" };
//const int KEY_COUNT = 5;

// Prints one record using getKeys()
void printRecord(const HashMap<string>& record, int index) {
    cout << "  [Record " << index + 1 << "]\n";
    DynamicArray<string> keys = record.getKeys();
    for (int i = 0; i < keys.getSize(); i++) {
        string val;
        record.get(keys.get(i), val);
        cout << "    " << keys.get(i) << ": " << (val.empty() ? "(empty)" : val) << "\n";
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
        printRecord(records.get(i), i);
        cout << "[DEBUG] printed record " << i << "\n";
    }
    cout << "\n";
}

// Feeds a CSV file into the parser line by line
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
        parser.setHeader(line);
        cout << "[DEBUG] setHeader done\n";
    }
    cout << "[feedFile] Processing file: " << filePath << "\n";
    while (getline(file, line)) parser.parseLine(line);
    file.close();
}

// Temporary placeholder validator for student 2's implementation
// Checks: duplicate ID, missing GPA, GPA range, empty name
// Returns a Stack of error messages if any
Stack<string> tempValidate(HashMap<string>& record, HashSet<string>& idSet) {
    Stack<string> errors;
    string id, gpa, name;

    // check duplicate ID
    record.get("ID", id);
    if (id.empty())
        errors.push("ID is missing");
    else if (!idSet.add(id))
        errors.push("Duplicate ID: " + id);

    // check GPA
    record.get("GPA", gpa);
    if (gpa.empty()) {
        errors.push("GPA is missing");
    } else {
        try {
            float g = stof(gpa);
            if (g < 0.0f || g > 4.0f)
                errors.push("GPA out of range: " + gpa);
        } catch (...) {
            errors.push("GPA is not a valid number: " + gpa);
        }
    }

    // check name
    record.get("Name", name);
    if (name.empty())
        errors.push("Name is missing");

    return errors;
}

// Prints the final validation report
void printReport(const DynamicArray<HashMap<string>>& validRecords,
                 DynamicArray<HashMap<string>>& invalidRecords,
                 DynamicArray<Stack<string>>& errorLogs) {

    cout << "\n===========================================\n";
    cout << "           VALIDATION REPORT               \n";
    cout << "===========================================\n";
    cout << "Total Valid:   " << validRecords.getSize() << "\n";
    cout << "Total Invalid: " << invalidRecords.getSize() << "\n";

    // print valid records
    cout << "\n--- Valid Records ---\n";
    for (int i = 0; i < validRecords.getSize(); i++)
        printRecord(validRecords.get(i), i);

    // print invalid records with their errors
    cout << "\n--- Invalid Records ---\n";
    for (int i = 0; i < invalidRecords.getSize(); i++) {
        printRecord(invalidRecords.get(i), i);

        cout << "  Errors:\n";
        Stack<string>& errors = errorLogs.get(i);
        while (!errors.isEmpty())
            cout << "    - " << errors.pop() << "\n";
        cout << "\n";
    }
}

int main() {

    cout << "===========================================\n";
    cout << "   TESTING DATA TRANSFORMATION ENGINE      \n";
    cout << "===========================================\n\n";

    // ---------------------------------------------------------
    // 1. Testing HashMap (Validation Rules)
    // ---------------------------------------------------------
    cout << "--- Testing HashMap (Validation Rules) ---\n";

    HashMap<string> rulesMap;
    rulesMap.put("ID", "Must be 9 digits");
    rulesMap.put("GPA", "Between 0.0 and 4.0");
    rulesMap.put("Name", "Cannot be empty");

    cout << "Current Map Size: " << rulesMap.getSize() << "\n";

    string gpaRule;
    if (rulesMap.contains("GPA")) {
        rulesMap.get("GPA", gpaRule);
        cout << "Rule for GPA: " << gpaRule << "\n";
    }

    rulesMap.put("GPA", "Between 0.0 and 4.0 (Strict Enforcement)");
    rulesMap.get("GPA", gpaRule);
    cout << "Updated Rule for GPA: " << gpaRule << "\n";

    if (!rulesMap.contains("Age"))
        cout << "Age rule not found. (Correct behavior)\n";

    cout << "\n";

    // ---------------------------------------------------------
    // 2. Testing HashSet (Duplicate ID Detection)
    // ---------------------------------------------------------
    cout << "--- Testing HashSet (Duplicate ID Detection) ---\n";
    HashSet<string> idSet;

    bool added1 = idSet.add("900221101");
    bool added2 = idSet.add("900221102");
    cout << "Added ID 900221101? " << (added1 ? "Yes" : "No") << "\n";
    cout << "Added ID 900221102? " << (added2 ? "Yes" : "No") << "\n";

    bool addedDuplicate = idSet.add("900221101");
    cout << "Added duplicate ID 900221101? " << (addedDuplicate ? "Yes" : "No") << " (Should be No)\n";
    cout << "Contains 900221102? " << (idSet.contains("900221102") ? "Yes" : "No") << "\n";
    cout << "Contains 900221199? " << (idSet.contains("900221199") ? "Yes" : "No") << " (Should be No)\n";
    cout << "\nTotal Unique IDs Tracked: " << idSet.getSize() << "\n";

    cout << "\n===========================================\n";
    cout << "          ALL TESTS COMPLETED              \n";
    cout << "===========================================\n\n\n";

    // ---------------------------------------------------------
    // 3. Translation Layer Test
    // ---------------------------------------------------------
    cout << "=== Translation Layer Test ===\n\n";

    HeaderProcessor hp;
    if (!hp.loadFromFile("headers.txt"))
        return 1;
    cout << "Mappings loaded: " << hp.getMappingCount() << "\n\n";

    cout << "--- translate() checks ---\n";
    string checks[] = { "stud_id", "FULL_NAME", "cgpa", "e_mail", "telephone", "department" };
    for (int i = 0; i < 6; i++) {
        string result = hp.translate(checks[i]);
        cout << "  \"" << checks[i] << "\" -> "
             << (result.empty() ? "(unknown)" : result) << "\n";
    }

    RecordParser parser(hp);

    cout << "\n--- File 1: students.csv ---\n";
    feedFile("students.csv", parser);
    printAllRecords(parser);

    feedFile("students2.csv", parser);
    printAllRecords(parser);

    cout << "Total records: " << parser.getRecordCount() << "\n";

    // ---------------------------------------------------------
    // 4. Pipeline — Transform, Validate, Split, Report
    // ---------------------------------------------------------
    cout << "\n===========================================\n";
    cout << "            PIPELINE                       \n";
    cout << "===========================================\n";

    // parser and IdSet for the pipeline
    RecordParser pipelineParser(hp);
    HashSet<string> pipelineIdSet;

    feedFile("students.csv", pipelineParser);
    feedFile("students2.csv", pipelineParser);

    const DynamicArray<HashMap<string>>& allRecords = pipelineParser.getRecords();

    DynamicArray<HashMap<string>> validRecords;
    DynamicArray<HashMap<string>> invalidRecords;
    DynamicArray<Stack<string>> errorLogs;

    // loop over every record, validate, and split
    for (int i = 0; i < allRecords.getSize(); i++) {
        // get a changeable copy of the record
        HashMap<string> record = allRecords.get(i);

        // must replace tempValidate with student 2's validator
        Stack<string> errors = tempValidate(record, pipelineIdSet);

        if (errors.isEmpty()) {
            validRecords.add(record);
        } else {
            invalidRecords.add(record);
            errorLogs.add(errors);
        }
    }

    printReport(validRecords, invalidRecords, errorLogs);

    return 0;
}