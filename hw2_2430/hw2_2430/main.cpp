#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "ArgumentManager.h"
#include "myArray.h"
using namespace std;
//sorting method by: https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/
//In collaboration with a group study that consists of Hien Nguyen, Muhammad Abbas and Jeremy B.

string removeSpace(string newString)
{
	newString.erase(remove(newString.begin(), newString.end(), ' '), newString.end());
	return newString;
} //By https://stackoverflow.com/questions/16329358/remove-spaces-from-a-string-in-c

int main(int argc, char * argv[]) {
	if (argc != 2 && argc != 4) {
		cout << "Usage: densemult \"A=<file> B=<file> C=<file>\"" << endl;
		return -1;
	}
	ArgumentManager parse(argc, argv);
	const string file1 = parse.get("input");
	const string file2 = parse.get("sort");
	const string file3 = parse.get("output");

	ifstream input_file, sort_file;
	ofstream output_file;
	input_file.open(file1);
	sort_file.open(file2);
	output_file.open(file3);

	myArray linkedlist;
	stringstream ss;
	string line;
	string dummy_id, dummy_last, dummy_first, dummy_dob, dummy_gpa;
	string actual_id; string actual_last, actual_first, actual_dob; string actual_gpa;
	string initial_record[2000]; int record_counter = 0; string command[600]; int command_counter = 0;
	int dub_detector = 0;

	if (input_file.peek() == std::ifstream::traits_type::eof())
	{
		cout << "Empty file!" << endl;
		return 0;

	}

	//read the inputfile
	string finddel = "delete";
	while (getline(input_file, line)) {
		if (line != "") {
			if (line.find(finddel) != std::string::npos) {
				initial_record[record_counter] = line;
			}
			else {
				string nospace = removeSpace(line);
				initial_record[record_counter] = nospace;
				record_counter++;
			}
		}

	}
	//read the sortfile
	/*while (getline(sort_file, line)) {
		if (line != "") {
			string nospace = removeSpace(line);
			command[command_counter] = nospace;
			command_counter++;
		}
	}*/
	string find1 = "delete"; string dummy_delete; string actual_delete;
	for (int i = 0; i < record_counter; i++) {
		if (initial_record[i].find(find1) != std::string::npos) {
			ss.str(initial_record[i]);
			ss >> dummy_delete >> actual_delete;
			ss.clear();
			linkedlist.deleteMidbyContent(actual_delete);
		}
		else {
			replace(initial_record[i].begin(), initial_record[i].end(), ',', ' ');//replace , with white space
			replace(initial_record[i].begin(), initial_record[i].end(), ':', ' ');//replace : with white space
			initial_record[i] = initial_record[i].substr(1, initial_record[i].size() - 2); //remove curly braces
			ss.str(initial_record[i]);
			ss >> dummy_id >> actual_id >> dummy_first >> actual_first >> dummy_last >> actual_last >> dummy_dob >> actual_dob >> dummy_gpa >> actual_gpa;
			ss.clear();
			linkedlist.add(actual_id, actual_first, actual_last, actual_dob, actual_gpa);
		}
	}

	if (command_counter == 0) {
		linkedlist.bubbleSort("id");
	}
	else {
		linkedlist.bubbleSort("id");
		for (int i = 0; i < command_counter; i++) {
			linkedlist.bubbleSort(command[i]);
		}
	}
	linkedlist.removeDuplicate();
	linkedlist.write(output_file);

	input_file.close();
	output_file.close();
	sort_file.close();
	return 0;

}
