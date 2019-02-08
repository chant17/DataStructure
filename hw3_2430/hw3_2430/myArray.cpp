#include "myArray.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;



myArray::myArray()
{
	head = NULL;
}


myArray::~myArray()
{

}
bool myArray::isEmpty() {
	if (head != NULL) {
		return false;
	}
	return true;
}

void myArray::insertMidContent(string value)
{
	node * curr = head;
	node * temp = new node;
	node * prev = new node;
	temp->id = value;
	while (curr->id < value)
	{
		prev = curr;
		curr = curr->next;
	}
	temp->next = prev->next;
	prev->next = temp;
}
void myArray::addBeg(string id_, string first_, string last_, string dob_, int workEXP_, int salary_, string position_) {
	node *temp = new node;
	temp->id = id_;
	temp->first = first_;
	temp->last = last_;
	temp->dob = dob_;
	temp->workEXP = workEXP_;
	temp->salary = salary_;
	temp->position = position_;
	if (head == NULL) {
		head = temp;
	}
	else {
		temp->next = head;
		head = temp;
	}
}
void myArray::add(string id_, string first_, string last_, string dob_, int workEXP_, int salary_, string position_) { //add will add at the beginning

	node *temp = new node;
	temp->id = id_;
	temp->first = first_;
	temp->last = last_;
	temp->dob = dob_;
	temp->workEXP = workEXP_;
	temp->salary = salary_;
	temp->position = position_;
	temp->next = NULL;
	if (head == NULL) {
		head = temp;
	}
	else {
		node *last = head;
		while (last->next)
			last = last->next;
		last->next = temp;
	}//Inspired by https://stackoverflow.com/questions/20125477/linked-list-insert-at-the-end-c
}

bool myArray::search(string found) {
	node *current = head;
	if (current == NULL) {
		return false;
	}
	while (current->next != NULL) {
		if (current->id == found) {
			return true;
		}
		current = current->next;
	}
	return false;
}
void myArray::deleteMultiple(int low, int high)
{
	node* curr = head;
	node* t;
	int count_;
	for (count_ = 1; count_<low && curr != NULL; count_++)
		curr = curr->next;

	// If we reached end of list, then return 
	if (curr == NULL)
		return;

	// Start from next node and delete N nodes 
	t = curr->next;
	for (count_ = 1; count_ <= high && t != NULL; count_++)
	{
		node *temp = t;
		t = t->next;
		free(temp);
	}
	curr->next = t; // Link the previous list with remaining nodes 

					// Set current pointer for next iteration 
	curr = t;
	
} //by https://www.geeksforgeeks.org/delete-n-nodes-after-m-nodes-of-a-linked-list/

void myArray::delatBeg(/*string &old_id*/) {
	if (isEmpty()) {
		return;
	}
	node * temp = head; //locate
	head = head->next; //update
	//old_id = temp->id; //empty
}
void myArray::deleteEnd() {
	if (isEmpty()) {
		return;
	}
	node *temp = head;
	node *prev = new node;
	while (temp->next != nullptr) {
		prev = temp;
		temp = temp->next;
	}
	free(temp);
	prev->next = NULL;
	
}

void myArray::deleteMidbyContent(string key) {
	// Store head node 
	node * temp = head; node * prev = new node;

	if (temp != NULL && temp->id == key)
	{
		head = temp->next;
		delete temp;
		return;
	}

	while (temp != NULL && temp->id != key)
	{
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) return;

	prev->next = temp->next;

	delete temp;
} //Inspired by https://www.geeksforgeeks.org/delete-a-given-node-in-linked-list-under-given-constraints/

int myArray::count() {
	if (isEmpty()) {
		return 0;
	}
	node *temp = head;
	int counter = 0;
	while (temp->next != NULL) {
		counter++;
		temp = temp->next;
	}
	return counter;
}
void myArray::addBefore(string id_, string first_, string last_, string dob_, int workEXP_, int salary_, string position_, int pos) {
	if (isEmpty()) {
		addBeg(id_, first_, last_, dob_, workEXP_, salary_, position_);
		return;
	}
	if (pos > count() || pos < 0) {
		return;
	}
	if (pos == 0) {
		addBeg(id_, first_, last_, dob_, workEXP_, salary_, position_);
		return;
	}
	
	node *curr = head;
	node *temp = new node;
	temp->id = id_;
	temp->first = first_;
	temp->last = last_;
	temp->dob = dob_;
	temp->workEXP = workEXP_;
	temp->salary = salary_;
	temp->position = position_;
	for (int j = 0; j < pos-1; j++) {
		curr = curr->next;
	}
	temp->next = curr->next;
	curr->next = temp;
}
void myArray::addAfter(string id_, string first_, string last_, string dob_, int workEXP_, int salary_, string position_, int pos) {
	int count01 = count();
	if (isEmpty()) {
		addBeg(id_, first_, last_, dob_, workEXP_, salary_, position_);
		return;
	}
	if (pos > count01 || pos < 0) {
		return;
	}
	if (pos == count01) {
		add(id_, first_, last_, dob_, workEXP_, salary_, position_);
		return;
	}
	pos++;
	node *curr = head;
	node *after = new node;
	node *temp = new node;
	temp->id = id_;
	temp->first = first_;
	temp->last = last_;
	temp->dob = dob_;
	temp->workEXP = workEXP_;
	temp->salary = salary_;
	temp->position = position_;
	if (pos == 0) {
		pos--;
		curr = curr->next;
		curr->next = temp;
	}
	for (int j = 0; j < pos-1; j++) {
		curr = curr->next;
	}
	temp->next = curr->next;
	curr->next = temp;

}
void myArray::swap(node *a, node *b)
{
	string temp = a->id;
	a->id = b->id;
	b->id = temp;
	string first_temp = a->first;
	a->first = b->first;
	b->first = first_temp;
	string last_temp = a->last;
	a->last = b->last;
	b->last = last_temp;
	string dob_temp = a->dob;
	a->dob = b->dob;
	b->dob = dob_temp;
	int workEXP_temp = a->workEXP;
	a->workEXP = b->workEXP;
	b->workEXP = workEXP_temp;
	int salary_temp = a->salary;
	a->salary = b->salary;
	b->salary = salary_temp;
	string position_temp = a->position;
	a->position = b->position;
	b->position = position_temp;
}

void myArray::bubbleSort(string command)
{
	int swapped;
	node * ptr1;
	node *lptr = NULL;

	if (head == NULL)
		return;

	do
	{
		swapped = 0;
		ptr1 = head;

		while (ptr1->next != lptr)
		{
			if (command.find("sortid") != std::string::npos) {
				if (ptr1->id > ptr1->next->id)
				{
					swap(ptr1, ptr1->next);
					swapped = 1;
				}
			}
			else if (command.find("sortlastname") != std::string::npos){
				if (ptr1->last > ptr1->next->last)
				{
					swap(ptr1, ptr1->next);
					swapped = 1;
				}
			}
			else if (command.find("sortfirstname") != std::string::npos){
				if (ptr1->first > ptr1->next->first)
				{
					swap(ptr1, ptr1->next);
					swapped = 1;
				}
			}
			else if (command.find("sortDOB") != std::string::npos) {
				if (ptr1->dob > ptr1->next->dob)
				{
					swap(ptr1, ptr1->next);
					swapped = 1;
				}
			}
			
			else if (command.find("sortyearsworked") != std::string::npos) {
				if (ptr1->workEXP > ptr1->next->workEXP)
				{
					swap(ptr1, ptr1->next);
					swapped = 1;
				}
			}
			else if (command.find("sortsalary") != std::string::npos) {
				if (ptr1->salary > ptr1->next->salary)
				{
					swap(ptr1, ptr1->next);
					swapped = 1;
				}
			}
			else if (command.find("sortposition") != std::string::npos) {
				if (ptr1->position > ptr1->next->position)
				{
					swap(ptr1, ptr1->next);
					swapped = 1;
				}
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
} //Inspired by https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/


void myArray::write(ostream &file) {
	node * curr = head;
	while (curr != NULL) {
		string date = curr->dob;
		string mm = date.substr(5, 2);
		string dd = date.substr(8, 2);
		string yyyy = date.substr(0, 4);
		string newDOB = mm + ' ' + dd + ' ' + yyyy;

		file << curr->id << ' ';
		file << curr->first << ' ';
		file << curr->last << ' ';
		file << newDOB << ' ';
		file << curr->workEXP << ' ';
		file << curr->salary << ' ';
		file << curr->position << endl;
		curr = curr->next;
	}
	file << endl;
}