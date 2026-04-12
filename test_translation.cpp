
//#include <iostream>
//#include <fstream>
//#include <string>
//#include "HeaderProcessor.h"
//#include "RecordParser.h"
//#include "HashMap.h"
//
//using namespace std;
//
//// Standard keys printed in fixed order
////const string KEYS[] = { "ID", "Name", "GPA", "Email", "Phone" };
////const int KEY_COUNT = 5;
//
//// Prints one record
//void printRecord(const DynamicArray<string>& headers, const HashMap<string>& record, int index) {
//    cout << "\n  [Record " << index + 1 << "]\n";
//    for (int i = 0; i < headers.getSize(); i++) {
//        string value;
//        if (record.get(headers.get(i), value))
//            cout << "    " << headers.get(i) << ": " << (value.empty() ? "(empty)" : value) << "\n";
//        else
//            cout << "    " << headers.get(i) << ": (missing)\n";
//    }
//}
//
//// Prints all records currently in the parser
//void printAllRecords(const RecordParser& parser) {
//    const DynamicArray<HashMap<string>>& records = parser.getRecords();
//    const DynamicArray<string>& headers = parser.getStandardHeader();
//    for (int i = 0; i < records.getSize(); i++)
//        printRecord(headers, records.get(i), i);
//    cout << "\n";
//}
//
//// Simulates what Student 3's reader will do: feed the parser line by line
//void feedFile(const string& filePath, RecordParser& parser) {
//    ifstream file(filePath);
//    if (!file.is_open()) {
//        cerr << "ERROR: Cannot open " << filePath << "\n";
//        return;
//    }
//
//    string line;
//    if (getline(file, line)) parser.setHeader(line);   // first line = header
//	cout << "[feedFile] Processing file: " << filePath << "\n";
//    while (getline(file, line)) parser.parseLine(line); // rest = data
//
//    file.close();
//}
//
//int main() {
//    cout << "=== Translation Layer Test ===\n\n";
//
//    // -- Load translator --
//    HeaderProcessor hp;
//    if (!hp.loadFromFile("headers.txt"))
//        return 1;
//    cout << "Mappings loaded: " << hp.getMappingCount() << "\n\n";
//
//    // -- Spot check --
//    cout << "--- translate() checks ---\n";
//    string checks[] = { "stud_id", "FULL_NAME", "cgpa", "e_mail", "telephone", "department" };
//    for (int i = 0; i < 6; i++) {
//        string result = hp.translate(checks[i]);
//        cout << "  \"" << checks[i] << "\" -> "
//            << (result.empty() ? "(unknown)" : result) << "\n";
//    }
//
//    RecordParser parser(hp);
//
//    // -- File 1: standard column order --
//    cout << "\n--- File 1: students.csv ---\n";
//    feedFile("students.csv", parser);
//    printAllRecords(parser);
//
//    // -- File 2: different column order to test order logic --
//
//    feedFile("students2.csv", parser);
//    printAllRecords(parser);
//
//    cout << "Total records: " << parser.getRecordCount() << "\n";
//    return 0;
//}





/////////////////////////////////////////////////

