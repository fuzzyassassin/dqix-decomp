#include <globaldefs.h>
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "Memory/SafeAllocator.h"
#include "std_library_functions.h"

struct Foo0207df50;
struct List02160094;
struct S021d8a40;

struct Vec3_021dbe10 {
    int x, y, z;
};

struct Node021dbe10 {
    char pad0[0x20];
    unsigned short combatantId;
};

struct Entry021dbe10 {
    char pad0[0x18];
    unsigned int : 12;
    unsigned int kind : 4;
    unsigned int : 0;
};

struct Entry021dbe10b {
    char pad0[0x18];
    unsigned int : 5;
    unsigned int classField : 7;
};

struct FlagsByte0x951 {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char bit2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
};

struct Timer021ef974 {
    int f0;
    unsigned short timer;
    unsigned short timer2;
    int state;
    int fc;
    int count;
};

void CopyInternalFields0207df50(struct Foo0207df50*);
extern "C" void func_ov025_021dee20(void* obj);
void* GetSlotPtr02160f20(void*);
struct Node021dbe10* GetNodeAtIndex02160094(struct List02160094*, int);
extern "C" void __clear(void* dst, int size);
extern "C" void _ZN8Vector3iaSERKS_(struct Vec3_021dbe10* dst, const struct Vec3_021dbe10* src);
void UpdateFlagAndDispatch_021dc0d8(void*);
extern "C" int _Z23GetField0Result02169a58Pv(void* combatant, int id);
extern "C" int func_ov025_021dfa9c(void* obj, void* base);
int ClassifyField0x81fe(char*);
extern "C" int func_ov000_02169a58(char* node, int value);
extern "C" void func_ov025_021e88d8(void* obj);
void SetTwoFields_021e8a40(char*, int, int);
void SetField_021e8a4c(char*, int);
extern "C" void func_ov025_021e8d20(void* obj, int v);
extern "C" void func_ov025_021db8d8(void* obj);
void* GetData02108e10(void);
void* SearchBothTables02079e2c(char*, int);
void ProcessPairs_021d8a40(void*, struct S021d8a40*);
ARM void IncrementCounterAndReset_021def30(unsigned char*);

extern "C" struct Timer021ef974 _ZZ16GetTimer021ef974vE1s;
extern char data_ov025_021ef40c[];
extern char data_ov025_021ef424[];
extern char data_ov025_021ef43c[];
extern int data_ov025_021ef404;

static inline int IsPartySlot(unsigned short id) { return id <= 3; }

// USA: func_ov025_021dbe10
extern "C" ARM void func_ov025_021dbe10(char* obj) {
    GameState* gs = GameState::GetInstance();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    char* base = *(char**)(obj + 0x29c);
    ((SafeAllocator*)(obj + 0x30))->Reset();
    CopyInternalFields0207df50((struct Foo0207df50*)(obj + 0x14c));
    func_ov025_021dee20(obj);

    void* slot = GetSlotPtr02160f20(obj);
    if (slot == NULL) {
        return;
    }
    struct Node021dbe10* node = GetNodeAtIndex02160094((struct List02160094*)slot, 0);
    if (node == NULL) {
        return;
    }

    obj[0x6e4b] = 0;
    obj[0x6e4e] = 0;
    *(short*)(obj + 0x6efc) = -1;
    obj[0x6efe] = 0;
    *(short*)(obj + 0x6fd6) = -1;
    obj[0x6fd8] = 0;
    *(short*)(obj + 0x6fb8) = -1;
    obj[0x6f01] = 0;
    obj[0x6fd4] = 0;

    struct Vec3_021dbe10 zero;
    __clear(&zero, sizeof(zero));
    _ZN8Vector3iaSERKS_((struct Vec3_021dbe10*)(obj + 0x6fdc), &zero);
    obj[0x6fe8] = 0;
    _ZN8Vector3iaSERKS_((struct Vec3_021dbe10*)(obj + 0x6fec), &zero);
    obj[0x6ff8] = 0;
    obj[0x6ff9] = 0;
    ((unsigned char*)obj)[0x7744] = 0xff;
    ((unsigned char*)obj)[0x7745] = 0xff;
    ((unsigned char*)obj)[0x7746] = 0xff;
    ((struct FlagsByte0x951*)(obj + 0x5951))->bit2 = 0;
    _ZZ16GetTimer021ef974vE1s.fc = 0;
    UpdateFlagAndDispatch_021dc0d8(obj);

    int clear = 1;
    void* combatant = gs->GetCombatantByIndex(node->combatantId);
    if (combatant != NULL) {
        unsigned short id = *(unsigned short*)slot;
        if (id == 0x3ae) {
            clear = 0;
        }
        int result = _Z23GetField0Result02169a58Pv(combatant, id);
        int alt = func_ov025_021dfa9c(obj, *(void**)(obj + 0x29c));
        if (alt != 0) {
            result = alt;
        }
        if (ClassifyField0x81fe(base) != 0 && node->combatantId == 0) {
            result = func_ov000_02169a58(*(char**)(obj + 0x5724), 0xdd);
        }
        if (result != 0) {
            func_ov025_021e88d8(obj + 0x2a8);
            SetTwoFields_021e8a40(obj + 0x2a8, (int)(obj + 0x30), (int)(obj + 0x14c));
            SetField_021e8a4c(obj + 0x2a8, *(int*)(obj + 0x29c));
            func_ov025_021e8d20(obj + 0x2a8, result);
            func_ov025_021db8d8(obj);
        } else {
            void* entry = SearchBothTables02079e2c((char*)GetData02108e10(), (short)id);
            if (entry != NULL) {
                if (((struct Entry021dbe10b*)entry)->classField == 0x22) {
                    ProcessPairs_021d8a40(obj, (struct S021d8a40*)slot);
                } else {
                    char path[0x50];
                    int kind = ((struct Entry021dbe10*)entry)->kind;
                    if (kind == 2) {
                        sprintf(path, data_ov025_021ef40c);
                    } else if ((kind == 1 || kind == 4) && IsPartySlot(node->combatantId)) {
                        sprintf(path, data_ov025_021ef424);
                    } else {
                        sprintf(path, data_ov025_021ef43c);
                    }
                    data_ov025_021ef404 = loader->QueueLoadFile(path, NULL);
                    *(int*)(obj + 0xeac) = 4;
                }
            }
        }
    }
    if (clear) {
        obj[0x6fd5] = 0;
    }
    if (*(int*)(obj + 0xeac) == 1) {
        IncrementCounterAndReset_021def30((unsigned char*)obj);
    }
}
