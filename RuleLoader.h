#pragma once

#include <string>
#include "HashMap.h"
#include "Rule.h"

using namespace std;

class RuleLoader {
private:
    HashMap<Rule> rulesMap;

    //remove leading/trailing whitespace
    string trim(const string& str) const;

    // convert string "true"/"1" to boolean
    bool toBool(const string& str) const;

public:
    RuleLoader();

    // Reads rules.txt and populates the rulesMap
    bool loadFromFile(const string& filePath);

    // Returns the fully built map of rules
    const HashMap<Rule>& getRulesMap() const;
    void updateRule(const string& field, const Rule& newRule);
};