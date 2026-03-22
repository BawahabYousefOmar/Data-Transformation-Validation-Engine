#pragma once
#include <string>


template <typename T>
class HashMap {
	private:
		//Node Structure
		struct Node {
			string key;
			T value;
			Node* next;

			//constructor
			Node(string k, T val) : key(k), value(val), next(nullptr) {};
		};

			// array of pointers
			Node** table;
			//Current size of the array
			int capacity;
			//Current number of stored data
			int size;
			//factor to resize
			float factor;


			//Private Functions
			int hashFunction(string key) const;
			void rehash();  // double size of the table
public:
	HashMap(int capa = 16);  //set the intial capacity to 16
		
	~HashMap(); //destuctor
	
	void put(string key, T value); //insert a rule
	T get(string key) const;		  // get a rule

	bool contains(string key) const;
	int getSize() const { return size; };			//return the size fo the array
	void setFactor(float f);// set the factor
};

//-------------------------------
//-----------IMPLEMENTATION-------
//-----------------------------
 

//-------------------------------- CONSTRUCTOR -------------------------------
template<typename T>
HashMap<T>::HashMap(int capa) {
	capacity = capa;
	size = 0;
	factor = 0.75f;

	//intial the table
	table = new Node * [capacity];

	//put all pointers to null
	for (int i = 0; i < capacity; i++)
	{
		table[i] = nullptr;
	}
}



//-------------------------------- DESTRUCTOR -------------------------------
template<typename T>
HashMap<T>::~HashMap() {
	//Iterate over every chain of nodes in the table
	for (int i = 0; i < capacity; i++)
	{
		Node* current = table[i];
		//loop over each linked list and delete it
		while (current != nullptr) {
			Node* prev = current;
			current = current->next;
			delete prev;
		}

		delete current; //Delete current
	}

	//delete the table
	delete[] table;
}

//-------------------------------- HASH FUNCTION -------------------------------
template<typename T> //custom template for string input keys
int HashMap<T>::hashFunction(string key) const {
	long long val = 0;

	//convert string to number
	for (char c : key) {
		val = (unsigned char)c + (11* val);
	}

	return val % capacity;
}