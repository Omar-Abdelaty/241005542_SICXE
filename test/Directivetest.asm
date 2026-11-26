TEST    START   1000
. --- Format 1 ---
        FIX
        FLOAT
. --- Format 2 ---
        CLEAR   A
        CLEAR   X
        COMPR   A, S
        TIXR    B
        ADDR    X, L
        SHIFTL  A, 4
        SVC     5
. --- Data Directives ---
VAL1    WORD    1000
CHAR1   BYTE    C'EOF'
CHAR2   BYTE    X'F1'
        END     TEST