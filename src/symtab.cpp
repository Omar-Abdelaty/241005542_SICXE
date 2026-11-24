#include"symtab.h"

map<string, symbolinfo> SYMTAB;

//checks if symbol is already in SYMTAB
bool hassymbol(const string& symbol) {
	return SYMTAB.find(symbol) != SYMTAB.end();
}

//adds symbol to SYMTAB
bool insertsymbol(const string& symbol, int address) {

	//checks for label
	if (symbol.empty()) {
		return false;
	}

	//checks if the symbol already exits
	if (hassymbol(symbol)) {
		return false;
	}

	//creates symbol
	symbolinfo info;
	info.address = address;
	info.defined = true;
	SYMTAB[symbol] = info;
	return true;
}

//searches for symbols in SYMTAB
int getsymboladdress(const string& symbol) {
	if (hassymbol(symbol)) {
		return SYMTAB[symbol].address;
	}
	return -1;
}