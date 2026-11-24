TEST    START   1000
// --- Format 1 --- (i purposely messed woth the comments to test the parser)
        FIX
        FLOAT
        HIO
        NORM
        SIO
        TIO
.  Format 2 ---   
        CLEAR   A
        TIXR    X
        ADDR    A, B
        COMPR   A, S
        DIVR    S, T
        MULR    X, L
        RMO     A, X
        SUBR    T, B
        SHIFTL  A, 4
        SHIFTR  X, 2
        SVC     5
// - -- Format 3 --   -
        LDA     VALUE
        STA     VALUE
        LDX     #10
        COMP    VALUE
        J       SUBR
. --- Format 4 (Notice the '+') ---
        +LDA    VALUE
        +JSUB   SUBR
        +RSUB
// --  - Directives and Data ---
VALUE   WORD    5
SUBR    RESW    1
        END     TEST