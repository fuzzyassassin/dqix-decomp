#include <globaldefs.h>
#include "GameState/GameState.h"
#include "System/Matrix.h"

struct ArrayContainsByteStruct;

struct Val0216c42c {
    short lo : 11;
    short hi : 5;
};

struct Event0216c42c {
    unsigned char kind;
    unsigned char type;
    unsigned char sub;
    signed char f3;
    signed char ids[3];
    signed char count;
    Val0216c42c vals[3];
    signed char fe;
};

struct SrcVal0216c42c {
    unsigned char kind;
    short lo;
    short hi;
};

struct Src0216c42c {
    char pad0[3];
    unsigned char count;
    signed char ids[4];
    SrcVal0216c42c lo[4];
    SrcVal0216c42c hi[4];
};

struct Action0216c42c {
    char pad0[0x18];
    unsigned int kind : 5;
    unsigned int id : 7;
};

void* GetPtrField0x2a04(GameState* gs);
extern "C" void* memset(void* dst, int c, unsigned int n);
int ArrayContainsByte(ArrayContainsByteStruct* s, int val);

int GetField0x3acValue(GameState* gs);
extern "C" void _Z26EnqueueEventTag37_021d2cc0Pv(void* src);

// USA: func_ov002_0216c42c
extern "C" ARM void func_ov002_0216c42c(char* base, Src0216c42c* src, Action0216c42c* action) {
    if (src == NULL || action == NULL) return;
    GameState* gs = GameState::GetInstance();
    ArrayContainsByteStruct* party = (ArrayContainsByteStruct*)GetPtrField0x2a04(gs);
    Event0216c42c ev;
    memset(&ev, 0, 0x10);
    ev.kind = 1;
    switch (action->id) {
    case 7:
        ev.type = 3;
        break;
    case 0x1a:
        ev.type = 2;
        break;
    case 0x4f:
    case 0x50:
        ev.sub = 3;
    case 2:
        ev.type = 1;
        break;
    case 0x12:
        ev.type = 4;
        break;
    }
    if (action->kind == 5) ev.sub = 3;
    ev.f3 = *(signed char*)(base + 0x1c20);
    signed char n = 0;
    for (int i = 0; i < src->count; i++) {
        int id = src->ids[i];
        if (ArrayContainsByte(party, id) == 0) {
            ev.ids[n] = id;
            Val0216c42c* d = &ev.vals[n];
            SrcVal0216c42c* v = &src->lo[i];
            d->lo = v->lo;
            d->hi = src->hi[i].lo;
            if (ev.type == 4 && v->kind == 3) {
                char* c = (char*)GetCombatantWithFlag0x100(gs, id);
                if (c != NULL) {
                    *(unsigned char*)(base + 0x2522) = 1;
                    *(unsigned char*)(base + 0x2523) = 0;
                    *(Vector3i*)(base + 0x2524) = *(Vector3i*)(c + 0x44);
                }
            }
            n++;
        }
    }
    ev.count = n;
    ev.fe = GetField0x3acValue(gs);
    _Z26EnqueueEventTag37_021d2cc0Pv(&ev);
}
