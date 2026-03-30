#pragma once

#include <string>

using namespace std;
template <typename T>
class HashSet {
private:
	//Node Structure
	struct Node {
		T key;
		Node* next;

		//constructor
		Node( T k) : key(k), next(nullptr) {};
	};

	// array of pointers
	Node** table;
	//Current size of the array
	int capacity;
	//Current number of stored IDs
	int size;
	//factor to resize
	float factor;


	//Private Functions
	int hashFunction(T key) const;
	void rehash();  // double size of the table
public:
	HashSet(int capa = 16);  //set the intial capacity to 16

	~HashSet(); //destuctor

	bool add(T key); //insert a rule
	bool contains(T key) const; //check if the key exist
	int getSize() const { return size; };			//return the size fo the array
	void setFactor(float f);// set the factor
};

//-------------------------------
//-----------IMPLEMENTATION-------
//-----------------------------


//-------------------------------- CONSTRUCTOR -------------------------------
template<typename T>
HashSet<T>::HashSet(int capa) {
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
HashSet<T>::~HashSet() {
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
int HashSet<T>::hashFunction(T key) const {

	unsigned long long val = 0; //positive to prevent negative, and long to prevent overflow

	//convert string to number
	for (char c : key) {
		//polynomial Rolling hash Method.
		val = (unsigned char)c + (31 * val); // 31 is a prime number so less collisions
	}

	return val % capacity;
}

//-------------------------------- Add Function ---------------------------

template<typename T>
bool HashSet<T>::add(T key) {
	//get index for the key
	int index = hashFunction(key);

	Node* current = table[index];
	//check if the key is already exist
	while (current != nullptr) {
		//if found, return false;
		if (current->key == key) {
			return false; //exist, return false;
		}

		current = current->next; //move to next node on the same chain
	}

	//if not exist, create a new
	Node* newNode = new Node(key);
	newNode->next = table[index]; //let the new node points to the first node on the table
	table[index] = newNode; //let the newNode be the first node on the chain
	size++; // increment the size fo the table

	//Check the capacity is less than  0.75
	if (static_cast<float>(size) >= capacity * factor) {
		rehash();
	}

	return true;// new id, not found
}

//---------------------------------- rehash --------------------------------
template<typename T>
void HashSet<T>::rehash() {

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



//---------------------------------- Contains ---------------------------------
template<typename T>
bool HashSet<T>::contains(T key) const {

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
void HashSet<T>::setFactor(float f) {

	if (f > 0)			//factor should be postive
		factor = f;
}

//------------------------
