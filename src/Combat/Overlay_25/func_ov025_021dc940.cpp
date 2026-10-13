#include <globaldefs.h>
#include "GameState/GameState.h"
#include "System/Matrix.h"

struct Battle_021dc940 {
    char pad0[0x8e14];
    signed char f8e14;
    char pad8e15[0x8e24 - 0x8e15];
    int f8e24;
};

struct Entry_021dc940 {
    char pad0[0x20];
    unsigned short id;
};

struct Slot_021dc940 {
    char pad0[0xb];
    unsigned char lo : 2;
    unsigned char disabled : 1;
    char padc[4];
    Entry_021dc940* entry;
};

struct Obj_021dc940 {
    char pad0[0x29c];
    Battle_021dc940* battle;
    char pad2a0[0x4d4 - 0x2a0];
    char sub4d4[0x890 - 0x4d4];
    char msg890[0xc18 - 0x890];
    char cameraBase[0xc88 - 0xc18];
    int cameraPos[3];
    char padc94[0x3760 - 0xc94];
    char entryList[0x55d8 - 0x3760];
    int f55d8;
    char pad55dc[0x6e4b - 0x55dc];
    unsigned char state;
    unsigned char subState;
    char pad6e4d[0x6efc - 0x6e4d];
    short f6efc;
    unsigned char f6efe;
    char pad6eff[0x6fd4 - 0x6eff];
    unsigned char f6fd4;
    char pad6fd5[3];
    unsigned char f6fd8;
    char pad6fd9[3];
    Vector3i shake;
    unsigned char f6fe8;
    char pad6fe9[0x6ff8 - 0x6fe9];
    unsigned char f6ff8;
    unsigned char f6ff9;
    char pad6ffa[0x7747 - 0x6ffa];
    unsigned char started;
};

struct Actor0209c73c;

extern "C" void* func_02057924(void);
extern "C" int func_ov000_0215e9fc(void* party, short* buf, int max, int start);
extern "C" int func_ov000_0215ec1c(void* party, short* buf, int max, int start);
extern "C" int _Z28CountValidCombatants02058618v(void* mgr);
extern "C" unsigned char* _Z15GetData02104b6cv(void);
extern "C" int _Z25CheckFields6d0And6d4EqualPh(unsigned char* data);
extern "C" int _Z13Check021ed2f4Pv(void* obj);
extern "C" int _Z24IsByteFieldZero_021ed0fcPv(void* obj);
extern "C" int _Z25IsAnimationActive0209ca2cPv(void* obj);
extern "C" void _Z20SetByte0xbeShiftPrevP13Bytes02033b88i(GameObject* obj, int value);
extern "C" void __clear(void* dst, int size);
extern "C" Slot_021dc940* _Z18GetSlotPtr02160f20Pv(void* obj);
extern "C" void _Z19SetFlag0x2_021754e0ii(void* list, int id);
extern "C" void func_ov000_0218142c(void* list, int id);
extern "C" void _Z23SetPosAndFields0216f1e4PvPiii(void* obj, int* pos, int a, int b);
extern "C" void* _Z26GetGlobalField0x1c020421a0v(void);
extern "C" void func_02043124(void* obj);
extern "C" void _Z20StopAndReset0209c7fcPv(void* obj);
extern "C" void _Z26DispatchActorState0209c73cP13Actor0209c73c(Actor0209c73c* actor);
extern "C" void _Z25ClearGlobalBuffer02107850v(void);

extern int data_02109bf4;

static inline unsigned char GetMotion_021dc940(GameObject* c) {
    return *((unsigned char*)c + 0xbe);
}

static inline int IsPartyIndex_021dc940(int id) {
    return id >= 0 && id <= 3;
}

struct TurnBlock_021dc940 { char pad[0x5d8]; int turn; };

// USA: func_ov025_021dc940
extern "C" ARM int func_ov025_021dc940(Obj_021dc940* obj) {
    GameState* gs = GameState::GetInstance();
    Battle_021dc940* party = obj->battle;
    void* mgr = func_02057924();

    unsigned char state = obj->state;
    if (state != 0) {
        if (state == 3) {
            obj->state = 4;
            obj->subState = 0;
        }
        return 0;
    }
    if ((int)obj->f6efe > 0) {
        return 0;
    }

    short buf[16];
    int n = 0;
    n = n + func_ov000_0215e9fc(party, buf, 0x10, n);
    n = n + func_ov000_0215ec1c(party, buf + n, 0x10 - n, 0);

    for (int i = 0; i < n; i++) {
        GameObject* c = gs->GetCombatantByIndex(buf[i]);
        if (c != NULL && (GetMotion_021dc940(c) == 4 || GetMotion_021dc940(c) == 3)) {
            return 0;
        }
    }

    if (_Z28CountValidCombatants02058618v(mgr) > 0) {
        return 0;
    }
    if (_Z25CheckFields6d0And6d4EqualPh(_Z15GetData02104b6cv()) == 0) {
        return 0;
    }
    if (_Z13Check021ed2f4Pv(obj->msg890) == 0) {
        return 0;
    }
    if (_Z24IsByteFieldZero_021ed0fcPv(obj->sub4d4) == 0) {
        return 0;
    }
    if (_Z25IsAnimationActive0209ca2cPv(&data_02109bf4) != 0) {
        return 0;
    }

    int busy = 0;
    for (int i = 0; i < n; i++) {
        GameObject* c = gs->GetCombatantByIndex(buf[i]);
        if (c == NULL) {
            continue;
        }
        c->obj3D_.SetAnimationPlaybackSpeed(0x1000, 0);
        if (obj->started == 0) {
            unsigned char motion = GetMotion_021dc940(c);
            if (motion != 4 && motion != 6) {
                _Z20SetByte0xbeShiftPrevP13Bytes02033b88i(c, 0);
            }
        }
        if (c->obj3D_.IsVisible() && c->obj3D_.IsTransitioningAnimations()) {
            busy = 1;
        }
    }
    obj->started = 1;
    if (busy) {
        return 0;
    }
    obj->started = 0;

    Vector3i zero;
    __clear(&zero, sizeof(zero));
    obj->shake = zero;
    obj->f6fe8 = 0;
    obj->f6fd8 = 0;
    obj->f6ff9 = 0;
    obj->f6efc = -1;
    obj->f6ff8 = 0;
    obj->f6fd4 = 0;

    Slot_021dc940* slot = _Z18GetSlotPtr02160f20Pv(obj);
    Entry_021dc940* entry;
    if (slot != NULL && (entry = slot->entry) != NULL && !slot->disabled) {
        int id = entry->id;
        if (IsPartyIndex_021dc940(id)) {
            _Z19SetFlag0x2_021754e0ii(obj->entryList, id);
            func_ov000_0218142c(obj->entryList, id);
        }
    }
    _Z23SetPosAndFields0216f1e4PvPiii(obj->cameraBase, obj->cameraPos, 0, 0);
    func_02043124(_Z26GetGlobalField0x1c020421a0v());

    Battle_021dc940* battle = obj->battle;
    if (((TurnBlock_021dc940*)((int)obj + 0x5000))->turn == battle->f8e24 - 1 && battle->f8e14 != 0) {
        _Z20StopAndReset0209c7fcPv(&data_02109bf4);
    } else {
        _Z26DispatchActorState0209c73cP13Actor0209c73c((Actor0209c73c*)&data_02109bf4);
    }
    _Z25ClearGlobalBuffer02107850v();
    return 1;
}
