#pragma once
#include<string>
#include<map>

using namespace std;

struct symbolinfo {
	int address;
	bool defined;
};

extern map<string, symbolinfo> SYMTAB;

bool insertsymbol(const string& symbol, int address);
bool hassymbol(const string& symbol);
int getsymboladdress(const string& symbol);
