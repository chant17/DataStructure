#pragma once
#include <iostream>
using namespace std;

class myArray
{
private:
	struct node {
		string id;
		string first;
		string last;
		string DOB;
		string gpa;
		node * next;
	};
	node * head;
public:
	myArray();
	~myArray();
	void deleteMidbyContent(string key);
	void delatBeg(string &);
	bool isEmpty();
	void insertMidContent(string);
	void add(string id_, string first_, string last_, string dob_, string gpa_);
	void removeDuplicate();
	void swap(node *a, node *b);
	void bubbleSort(string command);
	void write(ostream &);

};

