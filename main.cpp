#include <iostream>
#include <string>
#include "HashMap.h"
#include "HashSet.h"

using namespace std;

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
    cout << "===========================================\n";

    return 0;
}