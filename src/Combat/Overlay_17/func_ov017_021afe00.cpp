#include <globaldefs.h>
#include "GameState/GameState.h"
#include "Resource/GameResources.h"
#include "Combat/SearchEntry.h"
#include "System/Graphics.h"

struct AllocatorUnion;
struct S_e830;
struct SearchStruct0202c1a4;

extern "C" void* func_0202ae18(void);
int TestBitBySignedByteIndex(SearchStruct* obj, int value);
signed char GetSearchStructCurrentArrEntry(SearchStruct0202c1a4* obj);
extern "C" void* func_02012fe4(void);
int IsBrightnessTransitionActive(GameResources* resources);
int GetAxisIntValue(struct AxisFloats0203b57c* obj, int axis);
extern "C" int _Z26IsChannelValueZero0203b5e0Pvi(void* obj, int sel);
unsigned short GetFieldAt0x7e(S_e830* obj);
void Set3DClearColor(int color, int alpha, int depth, int polygonId, int fog);
int GetField4(unsigned int* obj);
void ClearBitsInField4(unsigned int* obj, unsigned int mask);
void SetBitsInField4(unsigned int* obj, unsigned int mask);
void SetMainBrightness(GameResources* resources, int brightness, int duration);
int CheckSubstructByte0x7cPositive(signed char* obj);
extern "C" void func_020531f0(GameObject* obj);
extern "C" int _Z19GetField1c_021a193cPi(int* obj);
int GetField0x3acValue(GameState* gs);
extern "C" void func_ov017_021cff8c(int a, int b);
void* AllocateAligned4(AllocatorUnion* alloc, unsigned int size);
void* GetField0x74deForValidIndex(char* p, unsigned int index);
int GetWord0x71f8(void* obj);
void ClearAllTreasureMapUnknownBits(void* obj);
extern "C" void _Z29SetCombatModeFromCase020dc2d0i(int mode);
extern "C" void func_ov017_021d0b30(int a, int b, int c);

extern AllocatorUnion data_02114e20;

struct ZoneState021afe00 {
    char pad0[0x1b34];
    int f1b34;
    int f1b38;
    int f1b3c;
    char pad1b40[0x1b48 - 0x1b40];
    int f1b48;
    char pad1b4c[0x1b62 - 0x1b4c];
    unsigned char f1b62;
    char pad1b63[0x1f74 - 0x1b63];
    unsigned short f1f74;
    unsigned short f1f76;
};

struct Zone021afe00 {
    char pad0[0x840];
    ZoneState021afe00 state;
};

static inline ZoneState021afe00* GetZoneState(Zone021afe00* zone) {
    return &zone->state;
}

static inline int GetF1b34(ZoneState021afe00* state) { return state->f1b34; }
static inline int GetF1b38(ZoneState021afe00* state) { return state->f1b38; }
static inline int GetF1b3c(ZoneState021afe00* state) { return state->f1b3c; }
static inline int GetF1b48(ZoneState021afe00* state) { return state->f1b48; }
static inline void SetF1b62(ZoneState021afe00* state, unsigned char v) { state->f1b62 = v; }

struct Snapshot021afe00 {
    unsigned char f0;
    char pad1[3];
    char block4[0x190];
    char block194[0x110];
    char block2a4[0x20];
    int f2c4;
    int f2c8;
    int f2cc;
    short f2d0;
    short f2d2;
    unsigned char f2d4;
    unsigned char f2d5;
    unsigned short ids[4];
};

struct Self021afe00 {
    char pad0[4];
    signed char* kind;
    char pad8;
    unsigned char mode;
    unsigned char result;
    unsigned char started;
    unsigned char leader;
    char padD[0x1b - 0xd];
    unsigned char slots[4];
    char pad1f[0x38 - 0x1f];
    int field4;
    int brightness;
    unsigned short clearColor;
    unsigned char faded;
    char pad43[0x288 - 0x43];
    Snapshot021afe00* snapshot;
};

static inline void GX_SetVisiblePlane(int plane) {
    DISPCNT = (DISPCNT & ~0x1f00) | (plane << 8);
}

// USA: func_ov017_021afe00
extern "C" ARM unsigned char func_ov017_021afe00(Self021afe00* self) {
    GameState* gs = GameState::GetInstance();
    SearchStruct* search = (SearchStruct*)func_0202ae18();
    for (int i = 0; i < 4; i++) {
        if (TestBitBySignedByteIndex(search, i) == 0) {
            continue;
        }
        if (i == GetSearchStructCurrentArrEntry((SearchStruct0202c1a4*)search)) {
            continue;
        }
        SearchEntry0202c178* entry = GetEntryBySignedByteIndex(search, i);
        if (entry == NULL) {
            continue;
        }
        if (entry->active == 0) {
            return self->result;
        }
    }

    self->started = 1;
    Zone021afe00* zone = (Zone021afe00*)func_02012fe4();
    if (self->mode != 2) {
        GameResources* res = func_ov017_0218b5b0();
        if (IsBrightnessTransitionActive(res)) {
            return 1;
        }
        self->brightness = GetAxisIntValue((struct AxisFloats0203b57c*)res, 0);
        if (_Z26IsChannelValueZero0203b5e0Pvi(res, 0) != 0) {
            self->faded = 1;
            GX_SetVisiblePlane(1);
            char* global = (char*)func_02012fe4();
            if (global != NULL) {
                S_e830* color = (S_e830*)(global + 0x6c);
                if (color != NULL) {
                    self->clearColor = GetFieldAt0x7e(color);
                }
            }
            int color = 0;
            if (self->brightness == 0x10) {
                color = 0x7fff;
            }
            Set3DClearColor(color, 0x1f, 0x7fff, 0, 0);
            self->field4 = GetField4((unsigned int*)res);
            ClearBitsInField4((unsigned int*)res, -1);
            SetBitsInField4((unsigned int*)res, 0x8de);
            SetMainBrightness(res, 0, 2);
        }
        for (int i = 0; i < 4; i++) {
            GameObject* member = gs->GetPartyMemberByIndex(i);
            if (member != NULL && CheckSubstructByte0x7cPositive((signed char*)member) != 0) {
                func_020531f0(member);
            }
        }
        if (self->kind != NULL) {
            if (*self->kind == 2) {
                GameResources* r = func_ov017_0218b5b0();
                if (_Z19GetField1c_021a193cPi((int*)r->unknown_ptr_array_36fc[3]) != 0) {
                    GX_SetVisiblePlane(7);
                }
            } else {
                GX_SetVisiblePlane(1);
            }
        } else {
            GX_SetVisiblePlane(1);
        }
    }

    if (self->mode == 1) {
        func_ov017_021cff8c(GetField0x3acValue(gs), 0);
    }
    if (self->mode == 2 || self->mode == 0) {
        self->snapshot = (Snapshot021afe00*)AllocateAligned4(&data_02114e20, sizeof(Snapshot021afe00));
    }
    if (self->mode == 0) {
        int i;
        Snapshot021afe00* snap = self->snapshot;
        if (snap != NULL) {
            snap->f0 = *((unsigned char*)gs + 0x5cda);
            memcpy(snap->block4, (char*)gs + 0x5cdc, sizeof(snap->block4));
            memcpy(snap->block194, (char*)gs + 0x5e6c, sizeof(snap->block194));
            memcpy(snap->block2a4, GetField0x74deForValidIndex((char*)gs, 0), sizeof(snap->block2a4));
            snap->f2c4 = GetWord0x71f8(gs);
            snap->f2c8 = GetF1b34(GetZoneState(zone));
            snap->f2d0 = GetF1b38(GetZoneState(zone));
            snap->f2d2 = GetF1b3c(GetZoneState(zone));
            snap->f2cc = GetF1b48(GetZoneState(zone));
            snap->f2d4 = zone->state.f1f74;
            snap->f2d5 = zone->state.f1f76;
            for (i = 0; i < 4; i++) {
                GameObject* member = gs->GetPartyMemberByIndex(i);
                if (member != NULL) {
                    snap->ids[i] = *(unsigned short*)((char*)member + 0x1b2);
                } else {
                    snap->ids[i] = 0;
                }
            }
        }
    }

    if (self->mode == 0) {
        memset(self->slots, 0, sizeof(self->slots));
        for (int i = 0; i < 4; i++) {
            unsigned short* obj = (unsigned short*)gs->GetGameObjectByIndex(i);
            if (obj != NULL) {
                if (*obj & 0x200) {
                    self->slots[i] = 1;
                } else {
                    self->slots[i] = 2;
                }
            }
        }
        self->slots[self->leader] = 1;
        return 2;
    }

    if (self->mode == 2) {
        SetF1b62(GetZoneState(zone), 0);
    }
    if (*(unsigned char*)gs->GetGrottoStruct() != 0 && self->mode == 2) {
        ClearAllTreasureMapUnknownBits(gs);
        _Z29SetCombatModeFromCase020dc2d0i(0);
    }
    func_ov017_021d0b30(1, 0, 0);
    return 3;
}
