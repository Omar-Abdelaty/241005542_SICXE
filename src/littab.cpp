#include "littab.h"

map<string, int> LITTAB;

bool hasliteral(const string& literal) {
	return LITTAB.find(literal) != LITTAB.end();
}

void insertliteral(const string& literal, int address) {
	LITTAB[literal] = address;
}

int getliteraladdress(const string& literal) {
	if (hasliteral(literal)) {
		return LITTAB[literal];
	}
	return -1;
}