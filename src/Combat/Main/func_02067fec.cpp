#include <globaldefs.h>

struct Entry0204254c {
    int val;
    char pad4;
    signed char length : 6;
    signed char flag : 1;
    signed char unused : 1;
};

struct FlagHolder02067fec {
    int pad0;
    int pad4;
    unsigned int pad8_0 : 28;
    unsigned int bit28 : 1;
    unsigned int pad8_29 : 1;
    unsigned int bit30 : 1;
    unsigned int pad8_31 : 1;
};

extern "C" Entry0204254c* _Z22FindEntryByKey0204254cii(int key, int tableIdx);
extern "C" int func_02067f9c(FlagHolder02067fec* a, const char* b, int c);

// USA: func_02067fec
extern "C" ARM int func_02067fec(FlagHolder02067fec* self, const char* text, int table) {
    if (self != 0 && self->bit30 == 0) {
        return self->bit28;
    }
    Entry0204254c* e = _Z22FindEntryByKey0204254cii((int)text, table);
    if (e != 0) {
        if (e->flag != 0) {
            return 1;
        }
        char c = *text;
        const char* next = text + e->length;
        if (c == 'h') {
            e = _Z22FindEntryByKey0204254cii((int)next, table);
            if (e != 0 && e->flag != 0) {
                return func_02067f9c(self, next + e->length, table) == 0;
            }
        } else if (c == 'y') {
            return func_02067f9c(self, next, table) == 0;
        }
    }
    return 0;
}
