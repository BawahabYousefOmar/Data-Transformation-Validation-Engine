    #include "RuleLoader.h"
    #include <fstream>
    #include <iostream>

    using namespace std;

    RuleLoader::RuleLoader() {}

    string RuleLoader::trim(const string& str) const {
        int start = 0;
        //while the charachter is empty space and we don't reach the end of the line, decrenment start
        while (start < (int)str.size() && isspace((unsigned char)str[start])) start++;
        //while the charachter is empty space and we don't reach the start of the line, increnment start
        int end = (int)str.size() - 1;
        while (end >= start && isspace((unsigned char)str[end])) end--;
        //return the trimmed line
        return str.substr(start, end - start + 1);
    }

    bool RuleLoader::toBool(const string& str) const {
        string lowerStr = str;
        for (char& c : lowerStr) c = tolower(c);//convert to lower
        return (lowerStr == "true" || lowerStr == "1");
    }

    bool RuleLoader::loadFromFile(const string& filePath) {
        ifstream file(filePath);//pass the path

        if (!file.is_open()) {//check if the file exist
            cerr << "RuleLoader ERROR: Could not open file: " << filePath << "\n";
            return false;
        }

        string line;  //;current line
        int lineNumber = 0; //counter for number of lines
        //Iterates over lines
        while (getline(file, line)) {
            lineNumber++; //increase number of lines by 1
            line = trim(line); //get rid of leading and last spaces

            // Skip empty lines and comments
            if (line.empty() || line[0] == '#') continue;

            // Parse format: FIELD.PROPERTY=VALUE
            int dotPos = line.find('.'); //get position of the dot in the line
            int eqPos = line.find('='); //get position of the '=' in the line
            //if you don't find the posititons of '.' or '=', skip the line
            if (dotPos == (int)string::npos || eqPos == (int)string::npos || dotPos > eqPos) {
                cerr << "RuleLoader WARNING: Malformed rule on line " << lineNumber << ". Skipping.\n";
                continue;
            }

            // Extract the three parts
            string field = trim(line.substr(0, dotPos));//get rule name like ID
            string property = trim(line.substr(dotPos + 1, eqPos - dotPos - 1));//get property
            string value = trim(line.substr(eqPos + 1));//get values 

            // get the existing Rule and update it, or create a new one if it's the first time we see this field
            Rule currentRule;
            rulesMap.get(field, currentRule);

            // Apply the property
            if (property == "isRequired") {
                currentRule.setRequired(toBool(value));
            }
            else if (property == "expectedLength") {
                currentRule.setExpectedLength(stoi(value));
            }
            else if (property == "requiredPrefix") {
                currentRule.setRequiredPrefix(value);
            }
            else if (property == "requiredSubstring") {
                currentRule.setRequiredSubstring(value);
            }
            else if (property == "minVal") {
                currentRule.setMinVal(stof(value));
            }
            else if (property == "maxVal") {
                currentRule.setMaxVal(stof(value));
            }

            // Update the map
            rulesMap.put(field, currentRule);
        }

        file.close();
        cout << "RuleLoader Successfully loaded rules configuration.\n";
        return true;
    }
    //get Rule in the hashMap
    const HashMap<Rule>& RuleLoader::getRulesMap() const {
        return rulesMap;
    }