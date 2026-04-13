

#include "Validator.h"


Stack<string> Validator::validateRecord(
    const HashMap<string>& record,
    const HashMap<Rule>& rulesMap,
    HashSet<string>& seenIDs)
{
    Stack<string> errors;//stack to store the errors

    // Get all the rules we need to check
    DynamicArray<string> ruleKeys = rulesMap.getKeys();

    // Iterate over the rules
    for (int i = 0; i < ruleKeys.getSize(); i++) {
        string field = ruleKeys.get(i);//get first key e.i "ID, NAME, etc."

        // Get the specific rule for this field
        Rule currentRule;
        rulesMap.get(field, currentRule);

        // Get the value from the record
        
        string value = "";// If the column doesn't exist in the CSV, value stays "".
        record.get(field, value);

        // Apply the Rule validation
        string errorMsg;
        if (!currentRule.isValid(value, errorMsg)) {
            // Push the error onto the stack with the field name so the user knows what failed
            errors.push(field + " Error: " + errorMsg);
        }
        // if field is ID, check for duplicates
        else if (field == "ID" && !value.empty()) {

           if (!seenIDs.add(value)) {
                errors.push("ID Error: Duplicate ID found (" + value + ").");
            }
        }
    }

    return errors; //Return the stack of Errors
}