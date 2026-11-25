#include "pass2.h"
#include <iostream>
#include <iomanip> // hex
#include <sstream> 

// helper function converts integers to 2 character HEX string
string hex(int value, int width = 2) {
    stringstream ss;
    ss << hex << setfill('0') << setw(width) << value;
    return ss.str();
}

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
    ObjectFile obj;

    // 1. Generate Header Record
    obj.header = "H^" + programName + "^" + hex(startAddress, 6) + "^" + hex(programLength, 6);

    // We will accumulate our T record bytes in this string
    string currenttextrecord = "";
    int currenttextaddress = startAddress;

    // 2. Loop through every line from Pass 1
    for (size_t i = 0; i < programLines.size(); i++) {
        string opcode = programLines[i].opcode;
        string operand = programLines[i].operand;
        int address = programLines[i].address;

        // Check if it is a directive or an instruction
        if (opcode == "WORD" || opcode == "BYTE" || opcode == "RESW" || opcode == "RESB") {
            // We will handle data generation in the next step
        }
        else {
            // It's an instruction from the OPTAB
            string searchopcode = opcode;
            bool isformat4 = false;
            
            if (!searchopcode.empty() && searchopcode[0] == '+') {
                isformat4 = true;
                searchopcode = searchopcode.substr(1);
            }

            if (OPTAB.find(searchopcode) != OPTAB.end()) {
                int format = OPTAB[searchopcode].format;
                if (isformat4) format = 4;

                // format 1
                if (format == 1) {
                    // just the opcode
                    currenttextrecord += hex(OPTAB[searchopcode].hexCode);
                }
                // format 2
                else if (format == 2) {
                    // placeholder
                }
                // format 3 and 4
                else if (format == 3 || format == 4) {
                    // placeholder
                }
            }
        }
    }

    // end record
    obj.end = "E^" + hex(startAddress, 6);

    // save text record
    obj.text.push_back("T^" + hex(startAddress, 6) + "^" + hex(currenttextrecord.length() / 2) + "^" + currenttextrecord);

    return obj;
}