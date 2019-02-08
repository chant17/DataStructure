#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;


string removeSpace(string newString)
{
	newString.erase(remove(newString.begin(), newString.end(), ' '), newString.end());
	return newString;
} //By https://stackoverflow.com/questions/16329358/remove-spaces-from-a-string-in-c

  //determine row
int mat_row(istream &file) {
	string line;
	int row = 0;

	while (getline(file, line)) {
		if (isdigit(line[0]) || line[0] == '-' || line[0] == '+') {
			++row;
		}
	}
	file.clear();
	file.seekg(0, ios::beg);
	return row;
}
//determine column 
int mat_col(istream &file) {
	string line = "";
	int column = 0;
	string num;
	if (file.good()) {
		while (line == "") {
			getline(file, line);
		}
	}
	istringstream iss(line);
	while (iss >> num)
	{
		column++;

	}
	file.clear();
	file.seekg(0, ios::beg);

	return column;
}

bool check(string checkStr)
{
	for (int i = 0; i < checkStr.length(); i++) {
		if (isalpha(checkStr[i])) {
			return false;
		}
		else if (checkStr[i] == '-' && i < checkStr.length()) {
			if (checkStr[i + 1] == '-') {
				return false;
			}
		}
	}
	return true;
}

int main(int argc, char* argv[]) {

	ArgumentManager parse(argc, argv);

	const string fileinput1 = parse.get("A");
	const string fileinput2 = parse.get("B");
	const string fileoutput = parse.get("C");
	//getting names and open the file for modification
	ifstream file1, file2; ofstream outputfile;

	file1.open(fileinput1);
	file2.open(fileinput2);
	outputfile.open(fileoutput);

	/*if (file1.fail) {
	outputfile
	}*/
	if (file1.peek() == std::ifstream::traits_type::eof())
	{
		cout << "Empty file!" << endl;
		outputfile << "error";
		return 0;

	} //Checking empty file by https://stackoverflow.com/questions/26228424/how-to-detect-an-empty-file-in-c
	if (file2.peek() == std::ifstream::traits_type::eof())
	{
		cout << "Empty file!" << endl;
		outputfile << "error";
		return 0;
	}

	int matA_row = mat_row(file1);
	int matA_col = mat_col(file1);
	int matB_row = mat_row(file2);
	int matB_col = mat_col(file2);

	//Array Initialization
	double matrixA[20][20];
	double matrixB[20][20];

	string line;
	stringstream ss;

	//File1

	while (getline(file1, line)) {
		string line1 = removeSpace(line);
		if (!check(line1)) {
			cout << "error. Invalid character";
			outputfile << "error";
			return 0;
		}

	}
	file1.clear();
	file1.seekg(0, ios::beg);

	for (int x = 0; x < matA_row; x++)
	{
		for (int y = 0; y < matA_col; y++)
		{
			file1 >> matrixA[x][y];
		}
	}

	//file 2
	while (getline(file2, line)) {
		string line1 = removeSpace(line);
		if (!check(line1)) {
			cout << "error. Invalid character";
			outputfile << "error";
			return 0;
		}

	}
	file2.clear();
	file2.seekg(0, ios::beg);

	for (int x = 0; x < matB_row; x++)
	{
		for (int y = 0; y < matB_col; y++)
		{
			file2 >> matrixB[x][y];
		}
	}

	//Output file
	double matrixC[20][20];

	if (matA_col != matB_row) {

		cout << "ERROR. Incompatible dimension" << endl;
		outputfile << "error";
	}
	else {
		/////////////////////////////////////////////////////

		for (int i = 0; i < matA_row; i++)
		{
			for (int j = 0; j < matB_col; j++)
			{
				matrixC[i][j] = 0;
				for (int k = 0; k < matB_row; k++)
				{
					matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
				}
			}
		}
		//Inspired by http://www.cplusplus.com/forum/beginner/158107/

		outputfile.precision(2);
		outputfile.setf(ios::fixed);
		for (int i = 0; i < matA_row; i++) {
			outputfile << matrixC[i][0];
			for (int j = 1; j < matB_col; j++) {
				outputfile << " " << matrixC[i][j];
			}
			outputfile << "\n";
		}
	}
	file1.close();
	file2.close();
	outputfile.close();
	return 0;
}
