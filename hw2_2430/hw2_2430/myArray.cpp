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
void myArray::add(string id_, string first_, string last_, string dob_, string gpa_) { //add will add at the beginning

	node *temp = new node;
	temp->id = id_;
	temp->first = first_;
	temp->last = last_;
	temp->DOB = dob_;
	temp->gpa = gpa_;
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

void myArray::delatBeg(string &old_id) {
	if (isEmpty()) {
		return;
	}
	node * temp = head; //locate
	head = head->next; //update
	old_id = temp->id; //empty
}


void myArray::removeDuplicate()
{
	node* prev = head;
	//node* current = prev->next;

	if (prev == NULL)
		return;
	node *next_next;
	while (prev != NULL && prev->next != NULL)
	{

		if (prev->id == prev->next->id)
		{
			swap(prev, prev->next);
			next_next = prev->next->next;
			free(prev->next);
			prev->next = next_next;
		}
		else /* This is tricky: only advance if no deletion */
		{
			prev = prev->next;
		}
	}

}
void myArray::deleteMidbyContent(string key) {
	// Store head node 
	node * temp = head; node * prev = new node;

	if (temp != NULL && temp->id == key)
	{
		head = temp->next;   
		free(temp);               
		return;
	}

	while (temp != NULL && temp->id != key)
	{
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) return;

	prev->next = temp->next;

	free(temp);
} //Inspired by https://www.geeksforgeeks.org/delete-a-given-node-in-linked-list-under-given-constraints/


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
	string dob_temp = a->DOB;
	a->DOB = b->DOB;
	b->DOB = dob_temp;
	string gpa_temp = a->gpa;
	a->gpa = b->gpa;
	b->gpa = gpa_temp;

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
			if (command == "id") {
				if (ptr1->id > ptr1->next->id)
				{
					swap(ptr1, ptr1->next);
					swapped = 1;
				}
			}
			else if (command == "last") {
				if (ptr1->last > ptr1->next->last)
				{
					swap(ptr1, ptr1->next);
					swapped = 1;
				}
			}
			else if (command == "first") {
				if (ptr1->first > ptr1->next->first)
				{
					swap(ptr1, ptr1->next);
					swapped = 1;
				}
			}
			else if (command == "DOB") {
				if (ptr1->DOB > ptr1->next->DOB)
				{
					swap(ptr1, ptr1->next);
					swapped = 1;
				}
			}
			else if (command == "GPA") {
				if (ptr1->gpa > ptr1->next->gpa)
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
	file.setf((ios::fixed));
	while (curr != NULL) {
		file << "{id:" << curr->id << ',';
		file << "first:" << curr->first << ',';
		file << "last:" << curr->last << ',';
		file << "DOB:" << curr->DOB << ',';
		file << "GPA:" << setprecision(1) << curr->gpa << '}' << endl;
		curr = curr->next;
	}
}