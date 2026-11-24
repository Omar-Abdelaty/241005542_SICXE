#include<iostream>
#include<string>
#include<fstream>

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
	// open file (this is a test file)
	ifstream inputFile("test/test1.asm");

	if (!inputFile.is_open()) {
		cout << "Error: Could not open test1.asm" << endl;
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
		cout << "OPERAND:	[" << operand << "]" << endl;
		cout << "OPCODE:	[" << opcode << "]" << endl;
		cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl;
	}

	inputFile.close(); //close file
	return 0;
}