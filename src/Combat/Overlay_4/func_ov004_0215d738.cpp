#include <globaldefs.h>
#include "GameState/GameState.h"

extern "C" int _Z28DispatchNodeIfType7_02156e2cPvi(void* a, int key);
extern "C" void* _Z20GetEntryFor_021570a4Pvi(void* obj, int index);
extern "C" void* func_ov004_02156fd4(void* a, int key);
struct Container020dedd0;
extern "C" struct Element020de650* _Z24FindElementByKey020dedd0P17Container020dedd0i(struct Container020dedd0* c, int key);
extern "C" int func_020dcc98(int combatantId);
extern "C" int _Z26DispatchBySelector02086c4cPhii(unsigned char* obj, int id, int key);
extern "C" short _Z23SumKeyedLookups02086bf4Pci(char* obj, int key);
extern "C" void func_ov023_021f65d4(void* obj, int id, int mask);
extern "C" void _Z26ClearNodeMaskById_021f6600Pvii(void* obj, int id, int mask);
extern "C" void* func_ov004_02156f6c(void* a, int key);
extern "C" void func_ov023_021f809c(void* obj, void* param2);

class VObj0215d738 {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53();
    virtual void MethodD8(int arg);
    virtual void v55();
    virtual void MethodE0(int arg);
};

struct Node0215d738 { void* vtbl; char pad[0x1c]; int f20; };
extern "C" Node0215d738* func_ov004_02156f04(void* a, int key);
extern "C" VObj0215d738* func_ov004_02156f38(void* a, int key);

struct Party0215d738 { char pad[0x32]; short ids[4]; short count; };
struct Struct021707d8_0215d738 { char pad[8]; Party0215d738* ptr; };
extern Struct021707d8_0215d738 data_ov004_021707d8[];

struct Slots0215d738 { int id[4]; };
extern const Slots0215d738 data_ov004_0216fb80;

// USA: func_ov004_0215d738
extern "C" ARM int func_ov004_0215d738(void* a) {
    GameState* bs = GameState::GetInstance();
    unsigned char* p = (unsigned char*)GetPtrField0x2a04(bs);
    int idx = _Z28DispatchNodeIfType7_02156e2cPvi(a, 0x5b);
    if (idx < 0) return 0;
    short* entry = (short*)_Z20GetEntryFor_021570a4Pvi(a, idx & 0xff);
    if (!entry) return 0;
    void* container = func_ov004_02156fd4(a, 5);
    if (!container) return 0;
    if (!_Z24FindElementByKey020dedd0P17Container020dedd0i((struct Container020dedd0*)container, *entry)) return 0;

    int ids[4];
    *(Slots0215d738*)ids = data_ov004_0216fb80;
    Struct021707d8_0215d738* data = data_ov004_021707d8;
    int count;
    int j;
    Party0215d738* party = data->ptr;
    count = party->count;
    for (j = 0; j < count; j++) {
        ids[j] = party->ids[j];
    }

    for (unsigned char i = 0; i < 5; i++) {
        int id = ids[i];
        GameObject* member = bs->GetPartyMemberByIndex(id);
        if (member) {
            Node0215d738* node = func_ov004_02156f04(a, i + 0x1df);
            if (!node) return 0;
            node->f20 = *(int*)((char*)member + 0x134);
            id = ids[i];
            ((VObj0215d738*)node)->MethodD8(func_020dcc98((signed char)id));
            int r = _Z26DispatchBySelector02086c4cPhii(p, id, *entry);
            if (r == 0) {
                func_ov023_021f65d4(a, i + 0x1e4, 8);
                func_ov023_021f65d4(a, i + 0x1ee, 8);
                _Z26ClearNodeMaskById_021f6600Pvii(a, i + 0x1e9, 8);
            } else {
                _Z26ClearNodeMaskById_021f6600Pvii(a, i + 0x1e4, 8);
                _Z26ClearNodeMaskById_021f6600Pvii(a, i + 0x1ee, 8);
                func_ov023_021f65d4(a, i + 0x1e9, 8);
                VObj0215d738* n = func_ov004_02156f38(a, i + 0x1e4);
                if (n) n->MethodE0(r);
            }
        } else if (i == count) {
            _Z26ClearNodeMaskById_021f6600Pvii(a, i + 0x1df, 8);
            _Z26ClearNodeMaskById_021f6600Pvii(a, i + 0x1e4, 8);
            _Z26ClearNodeMaskById_021f6600Pvii(a, i + 0x1ee, 8);
            func_ov023_021f65d4(a, i + 0x1e9, 8);
            int sum = _Z23SumKeyedLookups02086bf4Pci((char*)p, *entry);
            VObj0215d738* n = func_ov004_02156f38(a, i + 0x1e4);
            if (n) n->MethodE0(sum);
        } else {
            func_ov023_021f65d4(a, i + 0x1df, 8);
            func_ov023_021f65d4(a, i + 0x1e4, 8);
            func_ov023_021f65d4(a, i + 0x1ee, 8);
            func_ov023_021f65d4(a, i + 0x1e9, 8);
        }
    }

    void* n = func_ov004_02156f6c(a, 0x1c);
    if (n) func_ov023_021f809c(n, a);
    return 0;
}
