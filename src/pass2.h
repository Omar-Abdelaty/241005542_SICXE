#pragma once
#include <string>
#include <vector>
#include <map>
#include "optab.h"
#include "symtab.h"
#include "littab.h"

using namespace std;

// pass 1 struct
struct ParsedLine {
	string label;
	string opcode;
	string operand;
	int address;
};

// record struct
struct ObjectFile {
	string header;
	vector<string> text;
	vector<string> modification;
	string end;
};

// pass two function
ObjectFile runpass2(vector<ParsedLine>& programlines, int startaddress, int programlength, string programname);