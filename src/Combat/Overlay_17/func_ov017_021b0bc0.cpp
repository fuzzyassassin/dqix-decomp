#include <globaldefs.h>
#include "GameState/GameState.h"
#include "Resource/GameResources.h"
#include "Combat/SearchEntry.h"
#include "Filesystem/BackgroundLoader.h"
#include "Graphics/LightingManager.h"
#include "Memory/SafeAllocator.h"

struct SearchStruct0202c1a4;
struct Obj02033874;
struct Obj02053f7c;
struct StructDE1D4 { char data[0x20]; };

extern "C" void* func_0202ae18(void);
extern "C" void* func_02012fe4(void);
extern "C" GameResources* func_ov017_0218b5b0();
extern "C" void func_0202c288(void*);
extern "C" void _Z12SetByte0x1caPhh(void*, int);
int TestBitBySignedByteIndex(SearchStruct* obj, int value);
signed char GetSearchStructCurrentArrEntry(SearchStruct0202c1a4* obj);
extern "C" void func_ov017_02191108(GameResources*, int, int, int, int);
extern "C" void _Z26CallHelperWithBuf_021907dciiiii(GameResources*, int, int, int, int);
signed char GetSignedByte0x1ca(void*);
void SetVecYFromValue02033874(Obj02033874*, int);
void ClearBitsInWord(unsigned int*, unsigned int);
extern "C" void _Z29SetByte0x5cdaAndClearField0xaPhh(void*, int);
void* GetField0x74deForValidIndex(char* p, unsigned int index);
void SetWord0x71f8(void*, int);
extern "C" void _Z34SetField0x1b2IfMatchOrFlag02053f7cP11Obj02053f7csi(Obj02053f7c*, int, int);
extern "C" void* func_0205ec34(void);
extern "C" void func_0206dfe8(void*, int, int);
void CopyRegionsAndClearField0206e70c(char*);
void ApplySlotBytesToBattleStruct(unsigned char*);
float GetActiveBitIndex(GameState*);
void InitFieldsFromCombatant_0219bcac(unsigned char);
unsigned char* GetField0x3f8Address(GameState*);
void* GetGlobal02109418();
extern "C" void _Z25CallFunc0205ec34_020965f8v(void*);
void* ZeroInitReturn020de824(void*);
void ZeroInit020de848(void*);
void InitStruct020de1d4(StructDE1D4*);
extern "C" void* ExtractFileFromGP2(const char* gp2Path, const char* innerFilePath, unsigned int* outSize);
int InitAndDispatch020def44(int, int, int, short);
void InitStruct0207cbe8(char*);
extern "C" void func_0207cc18(void*, void*);
void* GetPtrField0x2a04(GameState*);
struct KeyMap020a095c;
void AddKeyValueClamped020a095c(KeyMap020a095c*, int, int);
void InitAndAppendEntry020dbc5c(char*, int);
int GetField0x397cValue(GameState*);
void EnqueueEventTag20_021cee78(int, unsigned char);
extern "C" void func_ov017_02191234(GameResources*);

extern const char* data_020f2a18;
extern const char* data_020f2a0c;

struct ZoneState021b0bc0 {
    char pad0[0x1b34];
    int f1b34;
    int f1b38;
    int f1b3c;
    char pad1b40[0x1b48 - 0x1b40];
    int f1b48;
    char pad1b4c[0x1b61 - 0x1b4c];
    unsigned char f1b61;
    char pad1b62[0x1f74 - 0x1b62];
    unsigned short f1f74;
    unsigned short f1f76;
};

struct Zone021b0bc0 {
    char pad0[0x840];
    ZoneState021b0bc0 state;
};

static inline ZoneState021b0bc0* GetZoneState(Zone021b0bc0* zone) {
    return &zone->state;
}

static inline void SetF1b34(ZoneState021b0bc0* state, int v) { state->f1b34 = v; }
static inline void SetF1b38(ZoneState021b0bc0* state, int v) { state->f1b38 = v; }
static inline void SetF1b3c(ZoneState021b0bc0* state, int v) { state->f1b3c = v; }
static inline void SetF1b48(ZoneState021b0bc0* state, int v) { state->f1b48 = v; }
static inline void SetF1b61(ZoneState021b0bc0* state, unsigned char v) { state->f1b61 = v; }

struct Snapshot021b0bc0 {
    unsigned char f0;
    char pad1[3];
    char block4[0x190];
    char block194[0x110];
    char block2a4[0x20];
    int f2c4;
    int f2c8;
    int f2cc;
    unsigned short f2d0;
    unsigned short f2d2;
    unsigned char f2d4;
    unsigned char f2d5;
    unsigned short ids[4];
};

struct Self021b0bc0 {
    char pad0;
    unsigned char done;
    char pad2[2];
    signed char* kind;
    char pad8;
    unsigned char mode;
    char padA[2];
    unsigned char leader;
    char padD[0x284 - 0xd];
    unsigned char f284;
    char pad285[3];
    Snapshot021b0bc0* snapshot;
};

struct TextContext021b0bc0 {
    SafeAllocator allocator;
    char list[0x18];
    void* containerData;
    int field30;
    int field34;
};

// USA: func_ov017_021b0bc0
extern "C" ARM void func_ov017_021b0bc0(Self021b0bc0* self) {
    char list[0x18];
    StructDE1D4 entry;
    TextContext021b0bc0 context;
    short ys[4];
    unsigned int size;

    GameState* gs = GameState::GetInstance();
    GameResources* res = func_ov017_0218b5b0();
    SearchStruct* search = (SearchStruct*)func_0202ae18();
    Zone021b0bc0* zone = (Zone021b0bc0*)func_02012fe4();
    func_0202c288(search);

    int show = 1;
    if (self->kind != NULL && *self->kind == 10) {
        show = 0;
    }
    GameObject* leader = gs->GetPartyMemberByIndex(self->leader);
    if (leader != NULL) {
        _Z12SetByte0x1caPhh(leader, *(short*)((char*)leader + 4));
    }
    short* y = ys;
    for (int i = 0; i < 4; i++, y++) {
        GameObject* member = gs->GetPartyMemberByIndex(i);
        if (member != NULL) {
            *y = *(short*)((char*)member + 0xae);
        }
    }

    for (int i = 0; i < 4; i++) {
        if (TestBitBySignedByteIndex(search, i) == 0) {
            continue;
        }
        if (i == GetSearchStructCurrentArrEntry((SearchStruct0202c1a4*)search)) {
            if (self->f284 == 0) {
                show = 0;
            }
            func_ov017_02191108(res, 1, show, 1, 1);
        } else {
            _Z26CallHelperWithBuf_021907dciiiii(res, i, 1, show, 1);
        }
    }

    if (self->mode == 2) {
        y = ys;
        for (int i = 0; i < 4; i++, y++) {
            GameObject* member = gs->GetPartyMemberByIndex(i);
            if (member == NULL) {
                continue;
            }
            if (i == GetSignedByte0x1ca(member)) {
                continue;
            }
            if (i != 0 && !(*(unsigned short*)member & 0x1000)) {
                continue;
            }
            SetVecYFromValue02033874((Obj02033874*)member, *y);
        }
        ClearBitsInWord((unsigned int*)res, 0x40);

        Snapshot021b0bc0* snap = self->snapshot;
        _Z29SetByte0x5cdaAndClearField0xaPhh(gs, snap->f0);
        memcpy((char*)gs + 0x5cdc, snap->block4, sizeof(snap->block4));
        memcpy((char*)gs + 0x5e6c, snap->block194, sizeof(snap->block194));
        memcpy(GetField0x74deForValidIndex((char*)gs, 0), snap->block2a4, sizeof(snap->block2a4));
        SetWord0x71f8(gs, snap->f2c4);
        SetF1b34(GetZoneState(zone), snap->f2c8);
        SetF1b48(GetZoneState(zone), snap->f2cc);
        SetF1b38(GetZoneState(zone), snap->f2d0);
        SetF1b3c(GetZoneState(zone), (unsigned char)snap->f2d2);
        SetF1b61(GetZoneState(zone), 0);
        zone->state.f1f74 = snap->f2d4;
        zone->state.f1f76 = snap->f2d5;
        for (int i = 0; i < 4; i++) {
            GameObject* member = gs->GetPartyMemberByIndex(i);
            if (member != NULL) {
                _Z34SetField0x1b2IfMatchOrFlag02053f7cP11Obj02053f7csi((Obj02053f7c*)member, snap->ids[i], 1);
            }
        }

        void* save = func_0205ec34();
        func_0206dfe8(save, 0x38e, 0x3e8);
        func_0206dfe8(save, 0x79e, 0x2bc);
        CopyRegionsAndClearField0206e70c((char*)save);
        ApplySlotBytesToBattleStruct((unsigned char*)save);
        gs->SetDayTimer(GetActiveBitIndex(gs));
        LightingManager* lighting = LightingManager::GetInstance();
        lighting->dayNightTimer_ = gs->GetDayTimer();
        lighting->timeOfDayIndex_ = gs->GetTimeOfDay();
        InitFieldsFromCombatant_0219bcac(1);
        GetField0x3f8Address(gs)[0xa] = 0;
        _Z25CallFunc0205ec34_020965f8v(GetGlobal02109418());

        ZeroInitReturn020de824(list);
        ZeroInit020de848(list);
        InitStruct020de1d4(&entry);
        BackgroundLoader::AddLockGlobal();
        void* data = ExtractFileFromGP2(data_020f2a18, data_020f2a0c, &size);
        if (data != NULL) {
            InitAndDispatch020def44((int)&entry, (int)data, size, 0x5612);
        }
        BackgroundLoader::RemoveLockGlobal();
        context.allocator.ResetAllocatorPointer();
        ZeroInitReturn020de824(context.list);
        InitStruct0207cbe8((char*)&context);
        InitStruct0207cbe8((char*)&context);
        func_0207cc18(&context, &entry);
        AddKeyValueClamped020a095c((KeyMap020a095c*)GetPtrField0x2a04(gs), 0x5612, 1);
    } else if (self->mode == 0) {
        InitAndAppendEntry020dbc5c((char*)res, self->leader);
        unsigned char* slots = (unsigned char*)GetPtrField0x2a04(gs) + 0xf78;
        for (int i = 0; i < 4; i++, slots++) {
            unsigned char id = *slots;
            if (id != GetField0x397cValue(gs)) {
                EnqueueEventTag20_021cee78(id, 0);
            }
        }
    }

    func_ov017_02191234(res);
    self->done = 1;
}
