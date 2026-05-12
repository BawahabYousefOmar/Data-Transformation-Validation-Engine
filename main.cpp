#include <iostream>
#include <fstream>
#include <string>

// Core Data Structures
#include "DynamicArray.h"
#include "HashMap.h"
#include "HashSet.h"
#include "Stack.h"

// Application Modules
#include "Rule.h"
#include "HeaderProcessor.h"
#include "RecordParser.h"
#include "RuleLoader.h"
#include "Validator.h"

using namespace std;

// =====================================================================
// printSeparator — prints a divider line
// =====================================================================
void printSeparator() {
    cout << "-------------------------------------------\n";
}

// =====================================================================
// printRecord — prints all fields of a single HashMap record
// =====================================================================
void printRecord(const HashMap<string>& record, int index) {
    cout << "Record #" << index + 1 << ":\n";
    DynamicArray<string> keys = record.getKeys();
    for (int i = 0; i < keys.getSize(); i++) {
        string val;
        record.get(keys.get(i), val);
        cout << "    " << keys.get(i) << ": " << (val.empty() ? "(empty)" : val) << "\n";
    }
}

// =====================================================================
// feedFile — opens a CSV file and feeds it line-by-line into the parser
// =====================================================================
bool feedFile(const string& filePath, RecordParser& parser) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "[ERROR] Cannot open file: " << filePath << "\n";
        return false;
    }

    cout << "[Pipeline] Ingesting \"" << filePath << "\"...\n";
    string line;

    // First line is the header row
    if (getline(file, line)) {
        parser.setHeader(line);
    }

    // Remaining lines are data records
    while (getline(file, line)) {
        parser.parseLine(line);
    }

    file.close();
    return true;
}

// =====================================================================
// runPipeline — core pipeline: ingest -> validate -> collect results
// =====================================================================
void runPipeline(
    const DynamicArray<string>& filePaths,
    HeaderProcessor& hp,
    RuleLoader& ruleLoader,
    DynamicArray<HashMap<string>>& validRecords,
    DynamicArray<HashMap<string>>& invalidRecords,
    DynamicArray<Stack<string>>& errorLogs)
{
    // Reset result arrays
    validRecords  = DynamicArray<HashMap<string>>();
    invalidRecords = DynamicArray<HashMap<string>>();
    errorLogs     = DynamicArray<Stack<string>>();

    // --- Phase 2: Ingest & Translate ---
    cout << "\n--- Phase 2: Ingestion & Translation ---\n";
    RecordParser parser(hp);
    for (int i = 0; i < filePaths.getSize(); i++) {
        feedFile(filePaths.get(i), parser);
    }
    const DynamicArray<HashMap<string>>& allRecords = parser.getRecords();
    cout << "Total records ingested: " << allRecords.getSize() << "\n";

    // --- Phase 3: Validation ---
    cout << "\n--- Phase 3: Validation ---\n";
    Validator validator;
    HashSet<string> globalIdTracker;    // tracks IDs across all files
    const HashMap<Rule>& activeRules = ruleLoader.getRulesMap();

    for (int i = 0; i < allRecords.getSize(); i++) {
        HashMap<string> record = allRecords.get(i);
        Stack<string> errors = validator.validateRecord(record, activeRules, globalIdTracker);

        if (errors.isEmpty()) {
            validRecords.add(record);
        } else {
            invalidRecords.add(record);
            errorLogs.add(errors);
        }
    }

    cout << "Validation complete.\n";
}

// =====================================================================
// printReport — displays the full pipeline report
// =====================================================================
void printReport(
    const DynamicArray<HashMap<string>>& validRecords,
    const DynamicArray<HashMap<string>>& invalidRecords,
    DynamicArray<Stack<string>>& errorLogs)
{
    int total = validRecords.getSize() + invalidRecords.getSize();

    cout << "\n===========================================\n";
    cout << "PIPELINE REPORT\n";
    cout << "===========================================\n";
    cout << "Total Records Processed : " << total << "\n";
    cout << "Valid                   : " << validRecords.getSize() << "\n";
    cout << "Invalid                 : " << invalidRecords.getSize() << "\n";
    cout << "===========================================\n";

    // --- Valid Records ---
    cout << "\n[ VALID RECORDS ]\n";
    printSeparator();
    if (validRecords.getSize() == 0) {
        cout << "  (none)\n";
    }
    for (int i = 0; i < validRecords.getSize(); i++) {
        printRecord(validRecords.get(i), i);
        printSeparator();
    }

    // --- Invalid Records ---
    cout << "\n[ INVALID RECORDS ]\n";
    printSeparator();
    if (invalidRecords.getSize() == 0) {
        cout << "(none)\n";
    }
    for (int i = 0; i < invalidRecords.getSize(); i++) {
        printRecord(invalidRecords.get(i), i);
        cout << "Errors:\n";
        Stack<string> errors = errorLogs.get(i);
        while (!errors.isEmpty()) {
            cout << "! " << errors.pop() << "\n";
        }
        printSeparator();
    }
}

// =====================================================================
// showMenu — prints the main CLI menu
// =====================================================================
void showMenu() {
    cout << "\n===========================================\n";
    cout << "DATA TRANSFORMATION & VALIDATION ENGINE\n";
    cout << "===========================================\n";
    cout << "1. Run pipeline with default files\n";
    cout << "2. Run pipeline with custom CSV file(s)\n";
    cout << "3. View last report\n";
    cout << "4. Search valid records by field\n";
    cout << "5. Exit\n";
    cout << "-------------------------------------------\n";
    cout << "Enter choice: ";
}

// =====================================================================
// searchRecords — lets the user query valid records by any field value
// =====================================================================
void searchRecords(const DynamicArray<HashMap<string>>& validRecords) {
    if (validRecords.getSize() == 0) {
        cout << "[Search] No valid records to search.\n";
        return;
    }

    cout << "Enter field name to search (e.g. ID, Name, GPA, Email, Phone): ";
    string field;
    cin >> field;
    // Capitalize first letter to match standard keys
    if (!field.empty()) field[0] = toupper(field[0]);

    cout << "Enter value to find: ";
    string query;
    cin.ignore();
    getline(cin, query);

    int found = 0;
    printSeparator();
    for (int i = 0; i < validRecords.getSize(); i++) {
        string val;
        if (validRecords.get(i).get(field, val) && val == query) {
            printRecord(validRecords.get(i), i);
            printSeparator();
            found++;
        }
    }

    if (found == 0) {
        cout << "No records found where " << field << " = \"" << query << "\".\n";
    } else {
        cout << "Found " << found << " matching record(s).\n";
    }
}

// =====================================================================
// MAIN
// =====================================================================
int main() {
    // --- Phase 1: Load configurations (done once at startup) ---
    cout << "===========================================\n";
    cout << "DATA TRANSFORMATION & VALIDATION ENGINE\n";
    cout << "===========================================\n";
    cout << "Loading configurations...\n";

    HeaderProcessor hp;
    if (!hp.loadFromFile("headers.txt")) {
        cerr << "[ERROR] Could not load headers.txt. Exiting.\n";
        return 1;
    }

    RuleLoader ruleLoader;
    if (!ruleLoader.loadFromFile("rules.txt")) {
        cerr << "[ERROR] Could not load rules.txt. Exiting.\n";
        return 1;
    }

    cout << "Configurations loaded successfully.\n";

    // State — persists across menu interactions
    DynamicArray<HashMap<string>> validRecords;
    DynamicArray<HashMap<string>> invalidRecords;
    DynamicArray<Stack<string>>   errorLogs;
    bool pipelineHasRun = false;

    // --- CLI Loop ---
    int choice = 0;
    while (choice != 5) {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            // Default files
            DynamicArray<string> files;
            files.add("students.csv");
            files.add("students2.csv");
            cout << "\n--- Phase 1: Using default files ---\n";
            runPipeline(files, hp, ruleLoader, validRecords, invalidRecords, errorLogs);
            pipelineHasRun = true;
            printReport(validRecords, invalidRecords, errorLogs);
        }
        else if (choice == 2) {
            // Custom file(s)
            cout << "How many CSV files do you want to load? ";
            int n;
            cin >> n;
            DynamicArray<string> files;
            for (int i = 0; i < n; i++) {
                cout << "Enter path for file " << i + 1 << ": ";
                string path;
                cin >> path;
                files.add(path);
            }
            runPipeline(files, hp, ruleLoader, validRecords, invalidRecords, errorLogs);
            pipelineHasRun = true;
            printReport(validRecords, invalidRecords, errorLogs);
        }
        else if (choice == 3) {
            if (!pipelineHasRun) {
                cout << "[!] No pipeline has been run yet. Choose option 1 or 2 first.\n";
            } else {
                printReport(validRecords, invalidRecords, errorLogs);
            }
        }
        else if (choice == 4) {
            if (!pipelineHasRun) {
                cout << "[!] No pipeline has been run yet. Choose option 1 or 2 first.\n";
            } else {
                searchRecords(validRecords);
            }
        }
        else if (choice == 5) {
            cout << "Exiting...\n";
        }
        else {
            cout << "[!] Invalid choice. Please enter 1-5.\n";
        }
    }

    return 0;
}