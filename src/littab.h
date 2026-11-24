#pragma once
#include <string>
#include <map>

using namespace std;

// LITTAB map that maps the literal to its address
extern map<string, int> LITTAB;

bool hasliteral(const string& literal);
void insertliteral(const string& literal, int address);
int getliteraladdress(const string& literal);