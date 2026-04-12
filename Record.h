//#pragma once
//
//#include <string>
//#include "Stack.h"
//
//using namespace std;
//
//class Record {
//
//private:
//	string id;
//	string name;
//	string gpa;
//	string email;
//	string phone;
//	bool valid; // to indicate if the record is valid or not
//
//	Stack <string> ErrorsStack; // to store the errors of each record
//	string getErrorsMessage() const; // to get the errors of each record in a string format
//
//
//public:	
//	//constructors:
//	Record() : id(0), name(""), gpa(0.0), email(""), phone("") {};
//	Record(string id, string name, string gpa, string email, string phone) : id(id), name(name), gpa(gpa), email(email), phone(phone) {};
//
//	//Getters:
//	string getId() const { return id; };
//	string getName() const { return name; };
//	string getGpa() const { return gpa; };
//	string getEmail() const { return email; };
//	string getPhone() const { return phone; };
//
//	string DisplayErrors() const; // to display the errors of each record
//
//	//Setters:
//
//	bool setValid(bool v) { valid = v; }; // to set the record as valid or invalid
//
//	
//};