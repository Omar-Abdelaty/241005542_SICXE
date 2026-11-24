#pragma once
#include <string>
#include <map>

using namespace std;

// one row struct for optab table
struct opcodeinfo {
    int hexCode;
    int format;
};

extern map<string, opcodeinfo> OPTAB;


void initializeOPTAB();