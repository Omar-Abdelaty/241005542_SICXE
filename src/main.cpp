#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"optab.h"
#include"symtab.h"
#include"littab.h"

struct parsedline {
	string label;
	string opcode;
	string operand;
	int address;
};

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
	ifstream inputFile("test/LOCCTR&format4_test.asm");

	if (!inputFile.is_open()) {
		cout << "Error: Could not open LOCCTR&format4_test" << endl;
		return 1;
	}

	int locctr = 0;
	string currentline;

	vector<parsedline> programlines;

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

		//checks if the current line is the start
		if (opcode == "START") {
			locctr = stoi(operand, nullptr, 16); //string to integer and 16 means HEX so from string to hex

			//checks for label for start (program name) and inserts it into SYMTAB
			if (!label.empty()) {
				insertsymbol(label, locctr);
			}

			cout << "LOCCTR initialized to: 0x" << hex << locctr << dec << endl;
			continue;
		}

		parsedline currentparsedline;
		currentparsedline.label = label;
		currentparsedline.opcode = opcode;
		currentparsedline.operand = operand;
		currentparsedline.address = locctr;

		programlines.push_back(currentparsedline);

		//add literals to LITTAB
		if (!operand.empty() && operand[0] == '=') {
			if (!hasliteral(operand)) {
				insertliteral(operand, 0);
			}
		}

		//checks for label to insert
		if (!label.empty()) {
			bool inserted = insertsymbol(label, locctr);
			if (!inserted) {
				cout << "Error: Duplicate symbol [" << label << "] at 0x" << hex << locctr << dec << endl;
			}
		}

		bool isxe = false; // format 4 flag
		string searchopcode = opcode;

		//check for format 4
		if (!searchopcode.empty() && searchopcode[0] == '+') {
			isxe = true;
			searchopcode = searchopcode.substr(1);
		}

		int instsize = 0; //instruction size in bytes
		if (OPTAB.find(searchopcode) != OPTAB.end()) {
			int baseformat = OPTAB[searchopcode].format;

			if (isxe && baseformat == 3) {
				instsize = 4;
			}
			else {
				instsize = baseformat;
			}
		}

		//LOCCTR counter
		if (instsize > 0) {
			cout << "ADDR: 0x" << hex << locctr << dec << " | Opcode: [" << opcode << "]" << " | Length: " << instsize << " Byte(s)" << endl;
			locctr = locctr + instsize;
		}

		// directives

		// WORD
		else if (opcode == "WORD") {
			instsize = 3;
			cout << "ADDR: 0x" << hex << locctr << dec << " | WORD | Length: 3 Bytes" << endl;
			locctr = locctr + instsize;
		}

		// RESW
		else if (opcode == "RESW") {
			int count = stoi(operand); //string to integer conversion
			instsize = 3 * count;
			cout << "ADDR: 0x" << hex << locctr << dec << " | RESW | Reserving: " << instsize << " Bytes" << endl;
			locctr = locctr + instsize;
		}

		// RESB
		else if (opcode == "RESB") {
			int count = stoi(operand);
			instsize = count;
			cout << "ADDR: 0x" << hex << locctr << dec << " | RESB | Reserving: " << instsize << " Bytes" << endl;
			locctr = locctr + instsize;
		}

		// BYTE
		else if (opcode == "BYTE") {

			// Check for character string
			if (operand[0] == 'C') {
				instsize = (int)operand.length() - 3;
			}

			// Check for hex string
			else if (operand[0] == 'X') {
				instsize = ((int)operand.length() - 3) / 2;
			}

			cout << "ADDR: 0x" << hex << locctr << dec << " | BYTE | Length: " << instsize << " Bytes" << endl;
			locctr = locctr + instsize;
		}

		//END
		else if (opcode == "END") {
			cout << "Reached END directive, Pass 1 Complete." << endl;
			break;
		}

		// LTORG
		else if (opcode == "LTORG") {
			cout << "LTORG found. Allocating literals..." << endl;
			// loop through the LITTAB map to find any literal with address 0 and assign it the current locctr, then locctr++
			// (i will complete this loops logic later).
		}

		else {
			cout << "Error: [" << opcode << "]" << " is an invalid OPCODE or Directive" << endl;
		}
	}

		inputFile.close(); //close file
		return 0;
}