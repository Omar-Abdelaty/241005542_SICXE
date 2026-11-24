#include<iostream>
#include<string>

using namespace std;

void parseline(const string& line, string& label, string& opcode, string& operand) {
	label = opcode = operand = "";

	size_t pos = 0;

	//label:
	if (line[0] != ' ' && line[0] != '\t' && line.length() > 0) {
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

	const int n = 4;
	string testcode[n];

	testcode[0] = "COPY		START	1000";
	testcode[1] = "			LDA		=C'HELLO WORLD'";
	testcode[2] = "// TEST COMMENT";
	testcode[3] = ". TEST COMMENT";


	for (int i = 0;i < n;i++) {
		string currentline = testcode[i];

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

	}
	return 0;
}