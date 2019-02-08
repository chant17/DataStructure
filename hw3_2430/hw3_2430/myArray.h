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
		string dob;
		int salary;
		int workEXP;
		string position;
		node * next;
	};
	node * head; node * original;
public:
	myArray();
	~myArray();
	void deleteMidbyContent(string key);
	void delatBeg(/*string &*/);
	bool isEmpty();
	void insertMidContent(string);
	void addBeg(string id_, string first_, string last_, string dob_, int workEXP_, int salary_, string position);
	void add(string id_, string first_, string last_, string dob_, int workEXP_, int salary_, string position);
	void addBefore(string id_, string first_, string last_, string dob_, int workEXP_, int salary_, string position, int pos);
	void addAfter(string id_, string first_, string last_, string dob_, int workEXP_, int salary_, string position, int pos);
	void swap(node *a, node *b);
	void deleteMultiple(int low, int high);
	void deleteEnd();
	void bubbleSort(string command);
	void sortList(string command);
	bool search(string );
	int count();
	void write(ostream &);

};

