#pragma once

#include <string>
#include "HashMap.h"
#include "HashSet.h"
#include "Stack.h"
#include "Rule.h"
#include "DynamicArray.h"

using namespace std;

class Validator {
public:
    // Validates a single record against the rules and duplicate tracker.
    // Returns a Stack of error messages. If the Stack is empty, the record is valid.
    Stack<string> validateRecord(
        const HashMap<string>& record,
        const HashMap<Rule>& rulesMap,
        HashSet<string>& seenIDs
    );
};