#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "ArgumentManager.h"
#include "myArray.h"
using namespace std;
//properly ignore empty line in the input file
//delete from i to i, add before i, add after i
//add before 0 -> add at beginning

int CountWords(std::string strString)
{
	string word;
	int wordCount = 0;
	stringstream lineStream(strString);
	while (lineStream >> word) ++wordCount;
	cout << wordCount;

	return wordCount;
}
string removeSpace(const string s) {
	string newString;
	for (auto i = 0; i < s.length(); i++)
	{
		if (s[i] != ' ')
		{
			newString += s[i];
		}
	}
	return newString;
}
int main(int argc, char * argv[]) {
	if (argc != 2 && argc != 4) {
		cout << "Usage: densemult \"A=<file> B=<file> C=<file>\"" << endl;
		return -1;
	}
	ArgumentManager parse(argc, argv);
	const string file1 = parse.get("input");
	const string file2 = parse.get("command");
	const string file3 = parse.get("output");

	ifstream input_file, sort_file;
	ofstream output_file;
	input_file.open(file1);
	sort_file.open(file2);
	output_file.open(file3, ios::out | ios::trunc);
	//output_file(ios_base::app);

	myArray linkedlist, original;
	stringstream ss;
	string line;
	string id_, last_, first_, mm, dd, yyyy, position_;
	int salary_, workEXP_;

	if (input_file.peek() == std::ifstream::traits_type::eof())
	{
		cout << "Empty file!" << endl;
		return 0;

	}
	string dob_;
	while (getline(input_file, line)) {
		if (isdigit(line[0])) {
			ss.str(line);
			ss >> id_ >> first_ >> last_ >> mm >> dd >> yyyy >> workEXP_ >> salary_ >> position_;
			ss.clear();
			dob_ = yyyy + ' ' + mm + ' ' + dd;
			original.add(id_, first_, last_, dob_, workEXP_, salary_, position_);
			linkedlist.add(id_, first_, last_, dob_, workEXP_, salary_, position_);
		}
	}
	while (getline(sort_file, line)) {
		string dum, command_;
		string found = "delete"; string addb4_found = "add before"; string addafter_found = "add after";
		vector<string> temp; int temp_counter = 0; bool loop_condition = true;
		if (!line.empty()) {
			if (line.find("sort") != std::string::npos) {
				string newLine = removeSpace(line);
				cout << newLine;
				linkedlist.bubbleSort(newLine);
				linkedlist.write(output_file);
			}
			else if (line.find("add") != std::string::npos && line.find("beginning") != std::string::npos) {
				while (isdigit(sort_file.peek()) || isspace(sort_file.peek())) {
					if (isspace(sort_file.peek())) {
						getline(sort_file, line);
					}
					else {
						getline(sort_file, line);
						temp.push_back(line);
					}
				}
				for (unsigned i = temp.size(); i-- > 0; ) {
					cout << temp.at(i) << endl;
					ss.str(temp.at(i));
					ss >> id_ >> first_ >> last_ >> mm >> dd >> yyyy >> workEXP_ >> salary_ >> position_;
					ss.clear();
					dob_ = yyyy + ' ' + mm + ' ' + dd;
					if (!linkedlist.search(id_)) {
						linkedlist.addBeg(id_, first_, last_, dob_, workEXP_, salary_, position_);
					}
				}
				linkedlist.write(output_file);
				temp.clear();
			}
			else if (line.find("delete") != std::string::npos && line.find("to") != std::string::npos) { // delete from i to i
				string dummy1, id1, dummy2, id2;
				ss.str(line);
				ss >> dummy1 >> id1 >> dummy2 >> id2;
				ss.clear();
				if (stoi(id1) == 0) {
					linkedlist.deleteMultiple(0, stoi(id2));
					linkedlist.delatBeg();
				}
				else {
					linkedlist.deleteMultiple(stoi(id1), stoi(id2));
				}
				linkedlist.write(output_file);
			}
			else if (line.find("delete") != std::string::npos && CountWords(line) == 2) { //delete id
				ss.str(line); string dummy, deletetos;
				ss >> dummy >> deletetos;
				ss.clear();
				linkedlist.deleteMidbyContent(deletetos);
				linkedlist.write(output_file);
			}

			else if (line.find("add") != std::string::npos && line.find("end") != std::string::npos) {
				while (isdigit(sort_file.peek()) || isspace(sort_file.peek())) {
					if (isspace(sort_file.peek())) {
						getline(sort_file, line);
					}
					else {
						getline(sort_file, line);
						ss.str(line);
						ss >> id_ >> first_ >> last_ >> mm >> dd >> yyyy >> workEXP_ >> salary_ >> position_;
						ss.clear();
						dob_ = yyyy + ' ' + mm + ' ' + dd;
						if (!linkedlist.search(id_)) {
							linkedlist.add(id_, first_, last_, dob_, workEXP_, salary_, position_);
						}
					}
				}
				linkedlist.write(output_file);
			}
			else if (line.find("delete") != std::string::npos && line.find("end") != std::string::npos) {
				linkedlist.deleteEnd();
				linkedlist.write(output_file);
			}
			else if (line.find("delete") != std::string::npos && line.find("beginning") != std::string::npos) {
				linkedlist.delatBeg();
				linkedlist.write(output_file);
			}
			else if (line.find("output") != std::string::npos && line.find("original") != std::string::npos) {
				original.write(output_file);
			}
			else if (line.find("add") != std::string::npos && line.find("before") != std::string::npos) {
				ss.str(line); string dum, dumm; int data;
				ss >> dum >> dumm >> data;
				ss.clear();
				while (isdigit(sort_file.peek()) || isspace(sort_file.peek())) {
					if (isspace(sort_file.peek())) {
						getline(sort_file, line);
					}
					else {
						getline(sort_file, line);
						temp.push_back(line);
					}
				}

				for (unsigned i = temp.size(); i-- > 0; ) {
					cout << temp.at(i) << endl;
					ss.str(temp.at(i));
					ss >> id_ >> first_ >> last_ >> mm >> dd >> yyyy >> workEXP_ >> salary_ >> position_;
					ss.clear();
					dob_ = yyyy + ' ' + mm + ' ' + dd;
					if (!linkedlist.search(id_)) {
						linkedlist.addBefore(id_, first_, last_, dob_, workEXP_, salary_, position_, data);
					}
				}
				linkedlist.write(output_file);
				temp.clear();


			}
			else if (line.find("add") != std::string::npos && line.find("after") != std::string::npos) {
				ss.str(line); string dum, dumm; int data;
				ss >> dum >> dumm >> data;
				ss.clear();
				while (isdigit(sort_file.peek()) || isspace(sort_file.peek())) {
					if (isspace(sort_file.peek())) {
						getline(sort_file, line);
					}
					else {
						getline(sort_file, line);
						temp.push_back(line);
					}
				}
				for (unsigned i = temp.size(); i-- > 0; ) {
					cout << temp.at(i) << endl;
					ss.str(temp.at(i));
					ss >> id_ >> first_ >> last_ >> mm >> dd >> yyyy >> workEXP_ >> salary_ >> position_;
					ss.clear();
					dob_ = yyyy + ' ' + mm + ' ' + dd;
					if (!linkedlist.search(id_)) {
						linkedlist.addAfter(id_, first_, last_, dob_, workEXP_, salary_, position_, data);
					}
				}
				linkedlist.write(output_file);
				temp.clear();

			}
		}
	}
	return 0;
}