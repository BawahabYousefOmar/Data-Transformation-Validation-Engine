# Data-Transformation-Validation-Engine

**Data Transformation and Validation Engine**

## Project Goal
We are making a program that reads a file of student records, cleans up the messy column names, and checks if the data follows the university rules. Good records are kept, and bad records are rejected with a clear list of what went wrong.

## The Data Structures We Are Using
* **Dynamic Array:** This is just for storing our records when reading from a file. Then, we will use it to hold the final list of "Valid" records and the final list of "Invalid" records.
* **Hash Maps:** We will use two of these.
    * **Map 1 (The Translator):** It takes messy words from the file (like "stud_id") and tells us the standard word to use (like "ID").
    * **Map 2 (The Rules):** It stores the exact rules for each field (like "GPA max is 4.0").
* **Hash Set:** This will just store the student IDs we have already checked. If the program sees an ID that is already inside the set, it immediately knows it is a duplicate.
* **Stack:** Every single student record gets its own stack. If a student breaks three different rules, we push all three error messages into their stack so we can print them out at the end.

## How the Program Will Run (Step-by-Step)
1. **Load the Rules:** First, the program reads a simple text file called `rules.txt`. It loads things like the maximum GPA into the Rules Hash Map. We do this so we can change the rules later without having to rewrite the C++ code.
2. **Read the File:** The program opens the messy `students.csv` file and reads it line by line. It splits the text by commas (or other symbols) to get the raw data.
3. **Clean the Data:** The program uses the Translator Hash Map to fix the column names. Then, it packs this clean data into a Record object.
4. **Check the Rules:** A separate piece of code looks at the Record. It checks the Rules using the Hash Map to see if the GPA and Credits are valid. It asks the Hash Set if the ID is a duplicate. Any mistakes are added to the record's error stack.
5. **Sort and Report:** Finally, the program checks every record. If its error stack is empty, it goes into the Valid Array. If it has errors, it goes into the Invalid Array, and we print out the errors from the stack so the user knows exactly why it failed.

> This way, we have a clear and organized way to handle messy data, check it against rules, and give feedback on what went wrong.