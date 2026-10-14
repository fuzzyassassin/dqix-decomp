#include <globaldefs.h>
#include "std_library_functions.h"
#include "GameState/GameState.h"

struct Sub3718_021e7890 {
    char pad[0x718];
    void* ptr;
};
struct GameRes021e7890 {
    char pad[0x3000];
    Sub3718_021e7890 sub;
};

struct Struct02070fe4 {
    unsigned int count : 12;
};
struct Element02070f98 {
    unsigned short f : 15;
    unsigned short p2 : 1;
};
struct List02070f98 {
    Struct02070fe4 head;
    struct Element02070f98* base;
};
struct SubB021e7890 {
    char pad[0x400];
    List02070f98 list;
};
struct Res021e7890 {
    char pad[0x284];
    SubB021e7890 tableB;
};

struct SubWords021e7890 {
    unsigned int w[0x70 / 4];
};
struct Sub021e7890 {
    char pad0[0x10];
    float v[3];
    unsigned char b1c;
    unsigned char b1d;
    unsigned char b1e;
    unsigned char b1f;
    int w20;
    char pad24[0x4c - 0x24];
    unsigned char b4c;
    unsigned char b4d;
    char pad4e[0x70 - 0x4e];
};
struct GameObj021e7890 {
    char pad[0x13c];
    Sub021e7890* sub;
};

struct List02160094;
struct Node02160094 {
    char pad[0x20];
    unsigned short id;
};
struct Action021e7890 {
    unsigned short id;
};

extern "C" Res021e7890* func_ov017_021b8478(void* node);
extern "C" void* _Z19GetActiveCombatWorkv(void);
extern "C" Node02160094* _Z22GetNodeAtIndex02160094P12List02160094i(List02160094* list, int index);
extern "C" int _Z23GetElementCount02070fe4P14Struct02070fe4(Struct02070fe4* p);
Element02070f98* GetElementIfInBounds(List02070f98* list, int index);
extern "C" void _Z18ClearCombatantSlotP9GameStatei(GameState* battleStruct, int id);
extern "C" void __clear(void* buf, int n);
extern "C" int func_ov025_021e771c(short* ids, int count, int a, int b);
extern "C" void func_ov000_02161c0c(void* work, int id);
extern "C" void func_ov000_021677fc(void* work);
extern "C" void _Z38RunFlaglearAndSetMode02167e6c_02167e6cPh(void* work);
extern "C" void _ZN8Vector3iaSERKS_(float* dst, float* src);

extern const unsigned short data_ov025_021eef18[5];
extern const unsigned short data_ov025_021eef30[7];

// USA: func_ov025_021e7890
extern "C" ARM int func_ov025_021e7890(int self, Action021e7890* action) {
    Sub021e7890 local;
    short ids[10];
    SubB021e7890* tb;
    int i2;
    GameRes021e7890* res;
    Res021e7890* r;
    GameState* state;
    void* work;
    Node02160094* node;
    unsigned char mode;
    unsigned char n;
    res = (GameRes021e7890*)func_ov017_0218b5b0();
    state = GameState::GetInstance();
    r = func_ov017_021b8478(res->sub.ptr);
    work = _Z19GetActiveCombatWorkv();
    node = _Z22GetNodeAtIndex02160094P12List02160094i((List02160094*)action, 0);
    if (node == 0) return 1;
    GameObj021e7890* unit = (GameObj021e7890*)state->GetCombatantByIndex(node->id);
    if (unit == 0) return 1;
    Sub021e7890* obj = unit->sub;
    if (obj == 0) return 1;
    *(SubWords021e7890*)&local = *(SubWords021e7890*)obj;
    __clear(ids, 0x14);
    if (action->id == 0x153) {
        memcpy(ids, data_ov025_021eef18, 0xa);
        mode = 1;
        n = 5;
    } else if (action->id == 0x31a) {
        memcpy(ids, data_ov025_021eef30, 0xe);
        mode = 3;
        n = 7;
    } else {
        return 1;
    }
    tb = &r->tableB;
    int count = _Z23GetElementCount02070fe4P14Struct02070fe4(&tb->list.head);
    for (int i = 0; i < count; i++) {
        Element02070f98* elem = GetElementIfInBounds(&tb->list, i);
        if (elem == 0) continue;
        int found = 1;
        short* q = ids;
        int j = 0;
        while (j < n) {
            if (elem->f == *q) {
                found = 0;
                break;
            }
            j = j + 1;
            q = q + 1;
        }
        if (found) {
            ids[n++] = elem->f;
        }
    }
    func_ov025_021e771c(ids, mode, (int)ids, n);
    func_ov000_02161c0c(work, node->id);
    for (i2 = 0; i2 < 8; i2++) {
        short id = (short)(i2 + 0xc0);
        if (node->id != id) _Z18ClearCombatantSlotP9GameStatei(state, id);
    }
    func_ov000_021677fc(work);
    _Z38RunFlaglearAndSetMode02167e6c_02167e6cPh(work);
    GameObj021e7890* unit2 = (GameObj021e7890*)state->GetCombatantByIndex(node->id);
    if (unit2 != 0) {
        Sub021e7890* obj2 = unit2->sub;
        if (obj2 != 0) {
            _ZN8Vector3iaSERKS_(obj2->v, local.v);
            obj2->b1c = local.b1c;
            obj2->b1d = local.b1d;
            obj2->b1e = local.b1e;
            obj2->b1f = local.b1f;
            obj2->w20 = local.w20;
            obj2->b4c = local.b4c;
            obj2->b4d = local.b4d;
        }
    }
    return 1;
}
