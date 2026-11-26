#include "pass2.h"
#include <iostream>
#include <iomanip> // hex
#include <sstream> 

// helper function converts integers to 2 character HEX string
string tohex(int value, int width = 2) {
    stringstream ss;
    ss << hex << setfill('0') << setw(width) << value;
    return ss.str();
}

// helper function that maps register names to their SIC/XE numbers
int getRegCode(string reg) {

    if (reg == "A") return 0;
    if (reg == "X") return 1;
    if (reg == "L") return 2;
    if (reg == "B") return 3;
    if (reg == "S") return 4;
    if (reg == "T") return 5;
    if (reg == "F") return 6;
    if (reg == "PC") return 8;
    if (reg == "SW") return 9;
    
    return -1;
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

    // Header record
    obj.header = "H^" + programName + "^" + tohex(startAddress, 6) + "^" + tohex(programLength, 6);

    // T record bytes are accumulated in this string
    string currenttextrecord = "";
    int currenttextaddress = startAddress;

    // loops through everyline in pass 1
    for (size_t i = 0; i < programLines.size(); i++) {
        cout << "DEBUG: Processing line " << i << ": [" << programLines[i].opcode << "] [" << programLines[i].operand << "]" << endl;
        string opcode = programLines[i].opcode;
        string operand = programLines[i].operand;
        int address = programLines[i].address;

        // Check if it is a directive or an instruction
        if (opcode == "WORD" || opcode == "BYTE" || opcode == "RESW" || opcode == "RESB") {

            // WORD (3 bytes)
            if (opcode == "WORD") {
                int value = stoi(operand);
                currenttextrecord += tohex(value, 6); // 3 bytes = 6 hex chars
            }

            // BYTE (Character or Hex string)
            else if (opcode == "BYTE") {

                // Check if it is a character string 
                if (operand[0] == 'C') {

                    // Extract the characters inside the quotes 
                    string chars = operand.substr(2, operand.length() - 3);

                    for (size_t j = 0; j < chars.length(); j++) {

                        // Cast the character to an int to get its ASCII value, then to hex
                        int asciiVal = (int)chars[j];
                        currenttextrecord += tohex(asciiVal, 2);
                    }
                }

                // Check if it is a hex string
                else if (operand[0] == 'X') {

                    // Extract the hex characters inside the quotes
                    string hexChars = operand.substr(2, operand.length() - 3);
                    currenttextrecord += hexChars;
                }
            }

            // RESW and RESB
            // RESW and RESB don't generate object code
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
                    currenttextrecord += tohex(OPTAB[searchopcode].hexCode);
                }
                
                // format 2
       
                else if (format == 2) {
                    int opcodehex = OPTAB[searchopcode].hexCode;
                    int r1 = 0;
                    int r2 = 0;

                    // SHIFTL & SHIFTR
                    if (searchopcode == "SHIFTL" || searchopcode == "SHIFTR") {
                        size_t comma = operand.find(',');
                        string reg = operand.substr(0, comma);
                        string countStr = operand.substr(comma + 1);

                        r1 = getRegCode(reg);
                        int count = stoi(countStr);
                        r2 = count - 1; // Encode count minus 1 in the second field
                    }
                    // SVC 
                    else if (searchopcode == "SVC") {
                        r1 = stoi(operand);
                        r2 = 0;
                    }
                    // CLEAR & TIXR
                    else if (searchopcode == "CLEAR" || searchopcode == "TIXR") {
                        r1 = getRegCode(operand);
                        r2 = 0;
                    }
                    // Two registers 
                    else {
                        size_t comma = operand.find(',');
                        string reg1 = operand.substr(0, comma);
                        string reg2 = operand.substr(comma + 1);

                        r1 = getRegCode(reg1);
                        r2 = getRegCode(reg2);
                    }

                    // Combine opcode, r1, and r2 into 2 bytes (4 hex characters)
                    int fullByte = (opcodehex << 8) | (r1 << 4) | r2;
                    currenttextrecord += tohex(fullByte, 4);
                }
                
                // format 3 and 4
                else if (format == 3 || format == 4) {
                    // placeholder
                }
            }
        }
    }

    // end record
    obj.end = "E^" + tohex(startAddress, 6);

    // save text record
    obj.text.push_back("T^" + tohex(startAddress, 6) + "^" + tohex((int)currenttextrecord.length() / 2) + "^" + currenttextrecord);

    return obj;
}