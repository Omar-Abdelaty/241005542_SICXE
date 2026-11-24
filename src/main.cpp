#include<iostream>
#include<string>
#include<fstream>
#include"optab.h"

using namespace std;


void parseline(const string& line, string& label, string& opcode, string& operand) {
	label = opcode = operand = "";

	size_t pos = 0;

	//label:
	// length check first
	if (line.length() > 0 && line[0] != ' ' && line[0] != '\t') {
		size_t spacepos = line.find_first_of(" \t");
		if (spacepos == string::npos) {
			label = line;
			return;
		}
		else {
			label = line.substr(0, spacepos);
			pos = spacepos;
		}
	}

	//opcode:
	//skip spaces
	/*start of field*/ pos = line.find_first_not_of(" \t", pos);
	if (pos == string::npos) {
		return;
	}

	/*end of field*/ size_t spacepos = line.find_first_of(" \t", pos);
	if (spacepos == string::npos) {
		opcode = line.substr(pos);
		return;
	}
	else {
		opcode = line.substr(pos, spacepos - pos);
		pos = spacepos;
	}

	//operand
	pos = line.find_first_not_of(" \t", pos);
	if (pos == string::npos) {
		return;
	}

	bool inquotes = false;
	size_t i = pos;
	while (i < line.length()) {
		char c = line[i];

		if (c == '\'') {
			inquotes = !inquotes; //toggle
		}

		if (inquotes == false && (c == ' ' || c == '\t')) {
			break;
		}

		operand = operand + c;
		i++;
	}
}

int main() {

	//run optab
	initializeOPTAB();

	// open file (this is a test file)
	ifstream inputFile("test/format_test1&2.asm");

	if (!inputFile.is_open()) {
		cout << "Error: Could not open format_test1&2" << endl;
		return 1;
	}

	string currentline;

	// read file
	while (getline(inputFile, currentline)) {

		if (currentline.empty()) {
			continue;
		}
		if (currentline[0] == '.') {
			continue;
		}
		if (currentline.length() >= 2 && currentline[0] == '/' && currentline[1] == '/') {
			continue;
		}

		string label, opcode, operand;

		parseline(currentline, label, opcode, operand);

		cout << "Input:		[" << currentline << "]" << endl;
		cout << "LABEL:		[" << label << "]" << endl;
		cout << "OPCODE:	[" << opcode << "]" << endl;

		// Test the lookup for optab
		if (OPTAB.find(opcode) != OPTAB.end()) {
			cout << " -> Found in OPTAB, Format: " << OPTAB[opcode].format << endl;
		}
		else {
			cout << " -> Not an instruction (might be a directive)" << endl;
		}

		cout << "OPERAND:	[" << operand << "]" << endl;
		cout << "____________________________________________________" << endl;
	}

	inputFile.close(); //close file
	return 0;
}