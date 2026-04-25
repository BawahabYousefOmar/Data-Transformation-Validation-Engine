#include <iostream>
#include <fstream>
#include <string>

// Core Data Structures
#include "DynamicArray.h"
#include "HashMap.h"
#include "HashSet.h"
#include "Stack.h"
#include "Rule.h" 
#include "HeaderProcessor.h"
#include "RecordParser.h"
#include "RuleLoader.h"
#include "Validator.h"

using namespace std;

// =====================================================================
// Helper: Print a single record
// =====================================================================
void printRecord(const HashMap<string>& record, int index) {
    cout << "  [Record " << index + 1 << "]\n";
    DynamicArray<string> keys = record.getKeys();
    for (int i = 0; i < keys.getSize(); i++) {
        string val;
        record.get(keys.get(i), val);
        cout << "    " << keys.get(i) << ": " << (val.empty() ? "(empty)" : val) << "\n";
    }
}

// =====================================================================
// Helper: Feed CSV into Parser
// =====================================================================
void feedFile(const string& filePath, RecordParser& parser) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "[ERROR] Cannot open file: " << filePath << "\n";
        return;
    }

    cout << "[Pipeline] Ingesting " << filePath << "...\n";
    string line;

    // First line is the header
    if (getline(file, line)) {
        parser.setHeader(line);
    }

    // Remaining lines are data
    while (getline(file, line)) {
        parser.parseLine(line);
    }
    file.close();
}

// =====================================================================
// MAIN INTEGRATION TEST
// =====================================================================
int main() {
    cout << "===========================================\n";
    cout << "   DATA TRANSFORMATION ENGINE - FULL TEST  \n";
    cout << "===========================================\n\n";

    // ---------------------------------------------------------
    // Phase 1: Initialization & Configuration Loading
    // ---------------------------------------------------------
    cout << "--- Phase 1: Loading Configurations ---\n";

    HeaderProcessor hp;
    if (!hp.loadFromFile("headers.txt")) {
        cerr << "Failed to load header mappings. Exiting.\n";
        return 1;
    }

    RuleLoader ruleLoader;
    if (!ruleLoader.loadFromFile("rules.txt")) {
        cerr << "Failed to load validation rules. Exiting.\n";
        return 1;
    }

    cout << "Configurations loaded successfully.\n\n";

    // ---------------------------------------------------------
    //  Data Ingestion & Translation
    // ---------------------------------------------------------
    cout << "--- Phase 2: Ingestion & Translation ---\n";

    RecordParser parser(hp);
    feedFile("students.csv", parser);
    feedFile("students2.csv", parser);

    const DynamicArray<HashMap<string>>& allRecords = parser.getRecords();
    cout << "Total records ingested: " << allRecords.getSize() << "\n\n";

    // ---------------------------------------------------------
    // Phase 3: Validation Engine
    // ---------------------------------------------------------
    cout << "--- Phase 3: Validation ---\n";

    Validator validator;
    HashSet<string> globalIdTracker; // To track cross-file duplicate IDs
    const HashMap<Rule>& activeRules = ruleLoader.getRulesMap();

    DynamicArray<HashMap<string>> validRecords;
    DynamicArray<HashMap<string>> invalidRecords;
    DynamicArray<Stack<string>> errorLogs;

    for (int i = 0; i < allRecords.getSize(); i++) {
        HashMap<string> record = allRecords.get(i);

        // Run the record through the dynamic validation engine
        // Passing the record, the loaded rules map, and the global ID tracker
        Stack<string> errors = validator.validateRecord(record, activeRules, globalIdTracker);

        if (errors.isEmpty()) {
            validRecords.add(record);
        }
        else {
            invalidRecords.add(record);
            errorLogs.add(errors);
        }
    }

    cout << "Validation complete.\n\n";

    // ---------------------------------------------------------
    // Phase 4: Final Reporting
    // ---------------------------------------------------------
    cout << "===========================================\n";
    cout << "           FINAL PIPELINE REPORT           \n";
    cout << "===========================================\n";
    cout << "Total Records Processed: " << allRecords.getSize() << "\n";
    cout << "Total Valid:             " << validRecords.getSize() << "\n";
    cout << "Total Invalid:           " << invalidRecords.getSize() << "\n";
    cout << "===========================================\n";

    cout << "\n[ VALID RECORDS ]\n";
    for (int i = 0; i < validRecords.getSize(); i++) {
        printRecord(validRecords.get(i), i);
    }

    cout << "\n[ INVALID RECORDS & ERROR LOGS ]\n";
    for (int i = 0; i < invalidRecords.getSize(); i++) {
        printRecord(invalidRecords.get(i), i);

        cout << "  Errors Found:\n";
        Stack<string> errors = errorLogs.get(i);
        // Pop errors off the stack to display them
        while (!errors.isEmpty()) {
            cout << "    - " << errors.pop() << "\n";
        }
        cout << "\n";
    }

    return 0;
}