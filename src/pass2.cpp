#include "pass2.h"
#include <iostream>
#include <iomanip> // hex
#include <sstream> 

// This is the helper function we designed earlier
int getoperandaddress(string operand) {
    // check for literal
    if (operand[0] == '=') {
        if (hasliteral(operand)) {
            return getliteraladdress(operand);
        }
        return -1;
    }

    // check if its a number
    try {
        bool isHex = false;

        // HEX check
        for (size_t i = 0; i < operand.length(); i++) {
            if (operand[i] >= 'A' && operand[i] <= 'F') {
                isHex = true;
                break;
            }
        }

        if (isHex) {
            return stoi(operand, nullptr, 16);
        }
        else {
            return stoi(operand);
        }
    }
    catch (...) {
        // check SYMTAB to see if it is a symbol
        if (hassymbol(operand)) {
            return getsymboladdress(operand);
        }
    }

    return -1;
}

ObjectFile runpass2(vector<ParsedLine>& programLines, int startAddress, int programLength, string programName) {
    ObjectFile objFile;
    
    //
    //
    // placeholder for code
    // 
    // 
   
    // 1. Generate Header Record (Placeholder)
    objFile.header = "H^" + programName + "^000000^000000";

    // 2. Generate Text Records (Placeholder)
    objFile.text.push_back("T^000000^00^000000");

    // 3. Generate End Record (Placeholder)
    objFile.end = "E^000000";

    return objFile;
}