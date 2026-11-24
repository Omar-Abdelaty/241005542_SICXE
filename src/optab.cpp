#include "optab.h"


map<string, opcodeinfo> OPTAB;

void initializeOPTAB() {
    //0x prefix for HEX
    // Format 1 (no operands)
    OPTAB["FIX"] = { 0xC4, 1 };
    OPTAB["FLOAT"] = { 0xC0, 1 };
    OPTAB["HIO"] = { 0xF4, 1 };
    OPTAB["NORM"] = { 0xC8, 1 };
    OPTAB["SIO"] = { 0xF0, 1 };
    OPTAB["TIO"] = { 0xF8, 1 };

    // Format 2 (register to register)
    OPTAB["ADDR"] = { 0x90, 2 };
    OPTAB["COMPR"] = { 0xA0, 2 };
    OPTAB["DIVR"] = { 0x9C, 2 };
    OPTAB["MULR"] = { 0x98, 2 };
    OPTAB["RMO"] = { 0xAC, 2 };
    OPTAB["SUBR"] = { 0x94, 2 };
    OPTAB["SHIFTL"] = { 0xA4, 2 };
    OPTAB["SHIFTR"] = { 0xA8, 2 };
    OPTAB["SVC"] = { 0xB0, 2 };
    OPTAB["CLEAR"] = { 0xB4, 2 };
    OPTAB["TIXR"] = { 0xB8, 2 };

    // Format 3 & 4 (default is 3 and i will add detection for + in pass 1 for format 4)
    OPTAB["ADD"] = { 0x18, 3 };
    OPTAB["ADDF"] = { 0x58, 3 };
    OPTAB["AND"] = { 0x40, 3 };
    OPTAB["COMP"] = { 0x28, 3 };
    OPTAB["COMPF"] = { 0x88, 3 };
    OPTAB["DIV"] = { 0x24, 3 };
    OPTAB["DIVF"] = { 0x64, 3 };
    OPTAB["J"] = { 0x3C, 3 };
    OPTAB["JEQ"] = { 0x30, 3 };
    OPTAB["JGT"] = { 0x34, 3 };
    OPTAB["JLT"] = { 0x38, 3 };
    OPTAB["JSUB"] = { 0x48, 3 };
    OPTAB["LDA"] = { 0x00, 3 };
    OPTAB["LDB"] = { 0x68, 3 };
    OPTAB["LDCH"] = { 0x50, 3 };
    OPTAB["LDF"] = { 0x70, 3 };
    OPTAB["LDL"] = { 0x08, 3 };
    OPTAB["LDS"] = { 0x6C, 3 };
    OPTAB["LDT"] = { 0x74, 3 };
    OPTAB["LDX"] = { 0x04, 3 };
    OPTAB["LPS"] = { 0xD0, 3 };
    OPTAB["MUL"] = { 0x20, 3 };
    OPTAB["MULF"] = { 0x60, 3 };
    OPTAB["OR"] = { 0x44, 3 };
    OPTAB["RD"] = { 0xD8, 3 };
    OPTAB["RSUB"] = { 0x4C, 3 };
    OPTAB["SSK"] = { 0xEC, 3 };
    OPTAB["STA"] = { 0x0C, 3 };
    OPTAB["STB"] = { 0x78, 3 };
    OPTAB["STCH"] = { 0x54, 3 };
    OPTAB["STF"] = { 0x80, 3 };
    OPTAB["STI"] = { 0xD4, 3 };
    OPTAB["STL"] = { 0x14, 3 };
    OPTAB["STS"] = { 0x7C, 3 };
    OPTAB["STSW"] = { 0xE8, 3 };
    OPTAB["STT"] = { 0x84, 3 };
    OPTAB["STX"] = { 0x10, 3 };
    OPTAB["SUB"] = { 0x1C, 3 };
    OPTAB["SUBF"] = { 0x5C, 3 };
    OPTAB["TD"] = { 0xE0, 3 };
    OPTAB["TIX"] = { 0x2C, 3 };
    OPTAB["WD"] = { 0xDC, 3 };

    //RSUB is a special case because it takes no operands
    OPTAB["RSUB"] = { 0x4C, 3 };
}