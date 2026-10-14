#include <globaldefs.h>
#include "std_library_functions.h"
#include "GameState/GameState.h"

struct Container02080cc0;
struct Container02080f8c;
struct Container02080fa8;
struct Container020e0310 { char pad[4]; };
struct StatusOwner02081198;
struct StatusOwner02081164;
struct Struct020865b0;
struct S0215f56c;
struct Outer02166164;

int SetSublistEntriesFlag1(void* obj, int id);
extern "C" void* _Z17GetPtrField0x2a04P9GameState(GameState*);
void SetOrClearFlags464_02166164(Outer02166164*, int, int);
extern "C" void func_02042764(void* src, void* dst, int flag);
int GetFieldAt0x50(Struct020865b0*);
int ClassifyRatio_0215f56c(S0215f56c*);
int SetEntryFlagById02080b40(void* obj, int id);
void SetEntryHighNibble0x13(struct Container02080cc0* obj, int id, int value);
// short-id views of the same two entry points, used by the per-cell loop
extern "C" int _Z24SetEntryFlagById02080b40Pvi(void* obj, short id);
extern "C" void _Z22SetEntryHighNibble0x13P17Container02080cc0ii(struct Container02080cc0* obj, short id, int value);
extern "C" void _Z26SetEntryFirstField02080f8cP17Container02080f8cii(struct Container02080f8c*, int, char*);
extern "C" void _Z30ResolveEntryValueByKey02080fe0Pvii(void*, int, int);
extern "C" void _Z26SetEntryFirstField02080fa8P17Container02080fa8ii(struct Container02080fa8*, int, int);
extern "C" void _Z19SetEntryHalfword0xePvii(void*, int, int);
extern "C" void _Z27GetEntryFieldsAt0x602080828PviPsS0_(void*, short, short*, short*);
extern "C" void _Z23GetEntryOutputs020808c8PviPsS0_(void*, short, short*, short*);
extern "C" void _Z27SetEntryFieldsAt0x602080854Pviii(void*, int, int, int);
extern "C" int _Z21GetFieldByKey020e0434P17Container020e0310i(struct Container020e0310*, int);
extern "C" void func_ov003_0215f5e8(void* menu, int page, int count);
extern "C" void func_ov003_02160c58(void* self, short* outHigh, short* outLow);
void SetEntryNibbleByShortId(struct StatusOwner02081198* owner, int id, int enable);
void SetEntryFlag0x2ByShortId(struct StatusOwner02081164* obj, int id, int value);
extern "C" int func_020813ec(void* obj, int id);
extern "C" void func_ov003_02160678(void* self);
extern "C" void func_ov003_02160794(void* self);


struct MemberEntry02166220 {
    char pad0[2];
    unsigned char unk2[0xd];
    unsigned char unkF[0x140 - 0xf];
    char name[0x34];
    unsigned char bit0 : 1;
    char pad175[0x23c - 0x175];
};

struct Party02166220 {
    char pad0[0xf7c];
    unsigned char countF7c;
    char padF7d[0xf80 - 0xf7d];
    MemberEntry02166220 members[(0x2c8c - 0xf80) / 0x23c];
    char pad[0x2c8c - 0xf80 - ((0x2c8c - 0xf80) / 0x23c) * 0x23c];
    unsigned char count;
};

struct ShortPair02166220 {
    short v[2];
};

struct Table0217f3ec {
    char pad[0x20];
    ShortPair02166220 ids;
};

extern Table0217f3ec data_ov003_0217f3ec;

struct StatusPanel02166220 {
    char pad[0x2dc];
    Container020e0310 cont2dc;
    char pad2e0[0x324 - 0x2e0];
    struct Container02080cc0* elementObj;
    char pad328[0x39c - 0x328];
    char names[4][0x30];
    char pad45c[0x468 - 0x45c];
    unsigned char counters[4];
    char pad46c[0x49f - 0x46c];
    signed char page;
    char pad4a0[0x4bd - 0x4a0];
    unsigned char flag4bd;
};

struct EntryList02166220 {
    char pad[0x36];
    short field36;
};

// USA: func_ov003_02166220
extern "C" ARM void func_ov003_02166220(StatusPanel02166220* self) {
    struct Container02080cc0* elementObj = self->elementObj;
    Party02166220* party;
    short count;
    MemberEntry02166220* entry;
    short idB;
    int v;
    int k;
    short row;
    int idA;
    int color;
    int idC;
    short i;
    int off;
    short j;
    int key;
    unsigned char kind;
    short t22, t20, t1e, t1c;
    short outHigh, outLow;
    ShortPair02166220 ids;

    SetSublistEntriesFlag1(elementObj, 6);
    party = (Party02166220*)_Z17GetPtrField0x2a04P9GameState(GameState::GetInstance());
    count = party->count;
    idA = 0x15;
    idB = 100;
    row = self->page * 4;
    self->flag4bd = (unsigned char)idA;
    v = -1;
    idC = 0xcb;
    memset(self->counters, 0, 4);
    SetOrClearFlags464_02166164((Outer02166164*)self, count > 4, 1);
    memset(self->names, 0, sizeof(self->names));

    for (i = 0; i < 4; i++) {
        entry = &party->members[row];
        off = i * 0x30;
        func_02042764(entry->name, (char*)self->names + off, 1);
        _Z26SetEntryFirstField02080f8cP17Container02080f8cii((struct Container02080f8c*)elementObj, idA, &self->names[0][off]);
        if (GetFieldAt0x50((Struct020865b0*)entry) != 0) {
            v = (short)(GetFieldAt0x50((Struct020865b0*)entry) + 0x11);
        }
        _Z30ResolveEntryValueByKey02080fe0Pvii(elementObj, (short)(idA + 4), v);
        _Z26SetEntryFirstField02080fa8P17Container02080fa8ii((struct Container02080fa8*)elementObj, (short)(idA + 8),
                                                             entry->unk2[GetFieldAt0x50((Struct020865b0*)entry)]);
        color = ClassifyRatio_0215f56c((S0215f56c*)entry);
        if (idA == ((struct EntryList02166220*)elementObj)->field36 && color == 0xf) {
            color = 0xa;
        }
        if (row < count) {
            for (j = 0; j < 3; j++) {
                k = idA + j * 4;
                _Z22SetEntryHighNibble0x13P17Container02080cc0ii(elementObj, k, color);
                _Z24SetEntryFlagById02080b40Pvi(elementObj, k);
            }
            SetEntryHighNibble0x13(elementObj, idB, color);
            SetEntryFlagById02080b40(elementObj, idB);
            self->counters[i] = entry->bit0 + 1;
            kind = entry->unkF[GetFieldAt0x50((Struct020865b0*)entry)];
            _Z19SetEntryHalfword0xePvii(elementObj, idC, (short)(kind + 100));
            if (kind != 0) {
                color = 5;
                if (kind == 0xa) {
                    color = 0xd;
                }
                key = i + 0x19;
                _Z27GetEntryFieldsAt0x602080828PviPsS0_(elementObj, key, &t22, &t20);
                _Z23GetEntryOutputs020808c8PviPsS0_(elementObj, key, &t1e, &t1c);
                _Z27SetEntryFieldsAt0x602080854Pviii(elementObj, idC, (short)(t22 + t1e + 1), t20);
                SetEntryHighNibble0x13(elementObj, idC, color);
                SetEntryFlagById02080b40(elementObj, idC);
            }
        } else {
            SetEntryHighNibble0x13(elementObj, idA, color);
            SetEntryFlagById02080b40(elementObj, idA);
            _Z26SetEntryFirstField02080f8cP17Container02080f8cii(
                (struct Container02080f8c*)elementObj, idA,
                (char*)_Z21GetFieldByKey020e0434P17Container020e0310i(&self->cont2dc, 0x7530));
        }
        row++;
        idA = (short)(idA + 1);
        idC = (short)(idC + 1);
        idB++;
    }

    func_ov003_0215f5e8(elementObj, self->page, count);
    func_ov003_02160c58(self, &outHigh, &outLow);
    party = (Party02166220*)_Z17GetPtrField0x2a04P9GameState(GameState::GetInstance());
    outLow = outLow - (party->countF7c - 1);
    _Z26SetEntryFirstField02080fa8P17Container02080fa8ii((struct Container02080fa8*)elementObj, 0x23, outLow);
    _Z26SetEntryFirstField02080fa8P17Container02080fa8ii((struct Container02080fa8*)elementObj, 0x24, outHigh);

    ids = data_ov003_0217f3ec.ids;
    for (int n = 0; n < 2; n++) {
        short id = ids.v[n];
        SetEntryNibbleByShortId((struct StatusOwner02081198*)elementObj, id, 1);
        SetEntryFlag0x2ByShortId((struct StatusOwner02081164*)elementObj, id, 1);
        func_020813ec(elementObj, id);
    }
    func_ov003_02160678(self);
    func_ov003_02160794(self);
}
