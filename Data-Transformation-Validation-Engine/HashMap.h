#pragma once

#include <string>
#include "DynamicArray.h"

using namespace std;

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
	
	HashMap(const HashMap& other); //copy constructor
	HashMap& operator=(const HashMap& other); //assignment operator

	void put(string key, T value); //insert a rule
	bool get(string key, T& value) const;		  // get a rule

	bool contains(string key) const;
	int getSize() const { return size; };			//return the size fo the array
	void setFactor(float f);// set the factor
	DynamicArray<string> getKeys() const; // returns keys as a DynamicArray (no order)
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


//-------------------------------- COPY CONSTRUCTOR -------------------------------
template<typename T>
HashMap<T>::HashMap(const HashMap<T>& other) {
	capacity = other.capacity;
	size = other.size;
	factor = other.factor;

	table = new Node * [capacity];
	for (int i = 0; i < capacity; i++)
		table[i] = nullptr;

	for (int i = 0; i < capacity; i++) {
		Node* current = other.table[i];
		while (current != nullptr) {
			// directly copy node without calling put()
			Node* newNode = new Node(current->key, current->value);
			newNode->next = table[i];
			table[i] = newNode;
			current = current->next;
		}
	}
}



//-------------------------------- ASSIGNMENT OPERATOR -------------------------------


template<typename T>
HashMap<T>& HashMap<T>::operator=(const HashMap<T>& other) {
	if (this == &other) return *this;

	// delete my current data
	for (int i = 0; i < capacity; i++) {
		Node* current = table[i];
		while (current != nullptr) {
			Node* prev = current;
			current = current->next;
			delete prev;
		}
	}
	delete[] table;

	// copy from other
	capacity = other.capacity;
	size = other.size;
	factor = other.factor;

	table = new Node * [capacity];
	for (int i = 0; i < capacity; i++)
		table[i] = nullptr;

	// direct node copy � no put(), no rehash() risk
	for (int i = 0; i < capacity; i++) {
		Node* current = other.table[i];
		while (current != nullptr) {
			Node* newNode = new Node(current->key, current->value);
			newNode->next = table[i];
			table[i] = newNode;
			current = current->next;
		}
	}

	return *this;
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

		
	}

	//delete the table
	delete[] table;
}

//-------------------------------- HASH FUNCTION -------------------------------
template<typename T> 
int HashMap<T>::hashFunction(string key) const {
	
	unsigned long long val = 0; //positive to prevent negative, and long to prevent overflow

	//convert string to number
	for (char c : key) {
	//polynomial Rolling hash Method.
		val = (unsigned char)c + (31* val); // 31 is a prime number so less collisions
	}
	
	return val % capacity;
}

//-------------------------------- Put Function ---------------------------

template<typename T>
void HashMap<T>::put(string key, T val) {
	//get index for the key
	int index = hashFunction(key);

	Node* current = table[index];
	//check if the key is already exist
	while (current != nullptr) {
		//update the rule if key already exist
		if (current->key == key) {
			current->value = val;
			return; //get out of the function
		}

		current = current->next; //move to next node on the same chain
	}

	//if not exist, create a new
	Node* newNode = new Node(key, val);
	newNode->next = table[index]; //let the new node points to the first node on the table
	table[index] = newNode; //let the newNode be the first node on the chain
	size++; // increment the size fo the table

	//Check the capacity is less than  0.75
	if (static_cast<float>(size) >= capacity * factor) {
		rehash();
	}

}

//---------------------------------- rehash --------------------------------
template<typename T>
void HashMap<T>::rehash() {
 
	Node** oldTable = table;
	int oldC = capacity;
	//double the capacity
	capacity *= 2;
	table = new Node * [capacity];
	
	//set all the nodes in the new table to null
	for (int i = 0; i < capacity; i++)
	{
		table[i] = nullptr;
	}

	//put the old nodes into the new table
	for (int i = 0; i < oldC; i++)
	{
		Node* current = oldTable[i];
		
		//if current contains data, copy it
		while (current != nullptr) {
			
			

			int index = hashFunction(current->key);//get the new index 

			Node* next = current->next; //to not lose current.next;
			current->next = table[index];//points on the head of the chain 
			table[index] = current;//insert at the head of the chain
			current = next;// move to the next node in the old chain
			
		}
	}

	delete[] oldTable;
}

//---------------------------------- get VAlue ------------------------------

template<typename T>
bool HashMap<T>::get(string key, T& value) const {
	
	//get index
	int index = hashFunction(key);


	Node* current = table[index];//point to the first

	//loop over the chain till you find the node with the same key
	while (current != nullptr) {
		if (current->key == key) {
			value = current->value;//found
			return true;//return true
		}
		current = current->next;//move to the next node in the chain
	}

	//if not found	
	return false;
}

//---------------------------------- Contains ---------------------------------
template<typename T>
bool HashMap<T>::contains(string key) const{

	//get index
	int index = hashFunction(key);


	Node* current = table[index];//point to the first

	//loop over the chain till you find the node with the same key
	while (current != nullptr) {
		if (current->key == key) {
		   return true;//return true
		}
		current = current->next;//move to the next node in the chain
	}

	//if not found	
	return false;
}

//---------------------------- set Factor ------------------------
template<typename T>
void HashMap<T>::setFactor(float f) {
	
	if(f>0)			//factor should be postive
	factor = f; 
}

//---------------------------- get Keys ------------------------
template<typename T>
DynamicArray<string> HashMap<T>::getKeys() const {
    DynamicArray<string> keys;

	// loop over table
    for (int i = 0; i < capacity; i++) {
        Node* current = table[i];

		// add each key to the dynamic array
        while (current != nullptr) {
            keys.add(current->key);
            current = current->next;
        }
    }

    return keys;
}