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
}