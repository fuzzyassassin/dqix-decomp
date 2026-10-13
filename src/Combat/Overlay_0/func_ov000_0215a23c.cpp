#include <globaldefs.h>
#include "GameState/GameState.h"

struct Random;
struct S88514;

struct Ids_0215a23c {
    short v[8];
};

struct Stats_0215a23c {
    char pad[4];
    unsigned short f4;
};

struct Field_0215a23c {
    char pad[0x29c];
    unsigned int lo : 4;
    unsigned int kind : 5;
    unsigned int rest : 23;
    char pad2[0x2ac - 0x2a0];
    short f2ac;
};

struct Unit_0215a23c {
    char pad[0x138];
    Stats_0215a23c* stats;
    char pad2[0x150 - 0x13c];
    unsigned char* f150;
};

extern "C" {
extern const Ids_0215a23c data_ov000_02182b44;
extern const Ids_0215a23c data_ov000_02182b54;
void __clear(void* buf, int n);
int func_ov000_0215e9fc(void* self, short* buf, int max, int start);
int func_ov000_0215eb1c(void* self, short* buf, int max, int start);
void func_ov000_0215c758(void* self, short* targets, int count, int kind, short* results, short* applied,
                         unsigned long long* bits);
short func_ov000_0215a004(void* self, int src, int id, int value, unsigned long long* bits, int a5, int a6, int a7);
int func_ov000_02159dbc(void* self, int id);
Unit_0215a23c* _Z25GetCombatantWithFlag0x100P9GameStatei(GameState* gs, int id);
Unit_0215a23c* _Z25GetCombatantWithFlag0x400P9GameStatei(GameState* gs, int id);
Field_0215a23c* _Z15GetFieldAt0x150Ph(Unit_0215a23c* unit);
}

int ClassifyField0x81fe(char* base);
extern "C" int _Z30HasFlaggedSlotBit12Set02085230Ph(unsigned char* slots);
extern "C" int _Z28IsCombatantFlag0x80000000SetP10GameObject(GameObject* c);
extern "C" int _Z28IsCombatantFlag0x40000000SetP10GameObject(GameObject* c);
int GetTableValue(void* c);
extern "C" short _Z20ApplyHPDelta0215a16cPviiPs(void* unused, int id, int delta, short* outApplied);
extern "C" short _Z20ApplyMPDelta0215a1d4PviiPs(void* unused, int id, int delta, short* outApplied);
int TestBitInArray0x8ec(unsigned char* obj, int index);
int CheckFlag0x2AndState2(S88514* obj);
float NextRandomFloatBetween(Random* random, float minimum, float maximum);

static inline Unit_0215a23c* GetUnit(int id) {
    GameState* gs = GameState::GetInstance();
    return (Unit_0215a23c*)gs->GetCombatantByIndex(id);
}

static inline Unit_0215a23c* GetActiveUnit(int id) {
    GameState* gs = GameState::GetInstance();
    return _Z25GetCombatantWithFlag0x400P9GameStatei(gs, id);
}

// USA: func_ov000_0215a23c
extern "C" ARM void func_ov000_0215a23c(void* self) {
    if (ClassifyField0x81fe((char*)self) != 0) {
        return;
    }
    GameState* gs = GameState::GetInstance();
    Ids_0215a23c targets = data_ov000_02182b44;
    short results[8];
    short applied[8];
    unsigned long long bits[8];
    __clear(results, sizeof(results));
    __clear(applied, sizeof(applied));
    __clear(bits, sizeof(bits));
    short* res = results;
    short* tgt = targets.v;
    short* app = applied;
    unsigned long long* bp = bits;
    short n = 0;
    Ids_0215a23c idBuf = data_ov000_02182b54;
    short* ids = idBuf.v;
    int count = func_ov000_0215e9fc(self, ids, 8, 1);


    for (int i = 0; i < count; i++) {
        Unit_0215a23c* c = _Z25GetCombatantWithFlag0x100P9GameStatei(gs, ids[i]);
        if (c != 0) {
            int amount = 0;
            if (_Z30HasFlaggedSlotBit12Set02085230Ph(c->f150)) {
                amount += 0x19;
            }
            if (_Z28IsCombatantFlag0x80000000SetP10GameObject((GameObject*)c)) {
                int bonus = 10;
                int half = GetTableValue(c) >> 1;
                if (half > 10) {
                    bonus = half;
                }
                amount += bonus;
            }
            if (amount > 0) {
                res[n] = _Z20ApplyHPDelta0215a16cPviiPs(self, ids[i], amount, &applied[n]);
                tgt[n] = ids[i];
                bits[n] = 0;
                bits[n] |= 0x4000000000ULL;
                if (applied[n] > 0) {
                    n++;
                }
            }
        }
    }
    if (n > 0) {
        func_ov000_0215c758(self, tgt, n, 0, res, app, bp);
    }

    n = 0;
    for (int i = 0; i < count; i++) {
        Unit_0215a23c* c = _Z25GetCombatantWithFlag0x100P9GameStatei(gs, ids[i]);
        if (c == 0) {
            continue;
        }
        Field_0215a23c* f = _Z15GetFieldAt0x150Ph(c);
        if (f == 0) {
            continue;
        }
        int amount = 0;
        if (_Z28IsCombatantFlag0x40000000SetP10GameObject((GameObject*)c)) {
            amount = GetTableValue(c) / 10;
            if (amount < 3) {
                amount = 3;
            }
        }
        if (TestBitInArray0x8ec(c->f150, 0x3f) && f->f2ac > 0 && f->kind == 3) {
            float range = (float)(unsigned int)GetTableValue(c) / 10.0f;
            amount += (int)(1.0f + NextRandomFloatBetween((Random*)self, 0.0f, range));
        }
        if (amount > 0) {
            res[n] = _Z20ApplyMPDelta0215a1d4PviiPs(self, ids[i], amount, &applied[n]);
            tgt[n] = ids[i];
            bits[n] |= 0x800000000ULL;
            if (applied[n] > 0) {
                n++;
            }
        }
    }
    if (n > 0) {
        func_ov000_0215c758(self, tgt, n, 1, res, app, bp);
    }

    n = 0;
    for (int i = 0; i < count; i++) {
        Unit_0215a23c* c = GetUnit(ids[i]);
        if (c != 0 && CheckFlag0x2AndState2((S88514*)c->stats)) {
            int value = c->stats->f4 >> 4;
            if (value > 999) {
                value = 999;
            }
            if (value <= 0) {
                value = 1;
            }
            if (value > 0) {
                bits[n] |= 2;
                res[n] = func_ov000_0215a004(self, ids[i], ids[i], value, &bits[n], 0, 0, 1);
                applied[n] = value;
                tgt[n] = ids[i];
                n++;
            }
        }
    }
    if (n > 0) {
        func_ov000_0215c758(self, tgt, n, 2, res, app, bp);
    }

    count = func_ov000_0215eb1c(self, idBuf.v, 0x10, 1);
    for (int i = 0; i < count; i++) {
        Unit_0215a23c* c = GetActiveUnit(ids[i]);
        if (c != 0) {
            int amount = 0;
            short mp = 0;
            if (_Z28IsCombatantFlag0x40000000SetP10GameObject((GameObject*)c)) {
                amount = func_ov000_02159dbc(self, ids[i]);
                if (amount < 3) {
                    amount = 3;
                }
            }
            _Z20ApplyMPDelta0215a1d4PviiPs(self, ids[i], amount, &mp);
        }
    }

    n = 0;
    for (int i = 0; i < count; i++) {
        Unit_0215a23c* c = GetUnit(ids[i]);
        if (c != 0 && CheckFlag0x2AndState2((S88514*)c->stats)) {
            int value = c->stats->f4 >> 4;
            if (value > 999) {
                value = 999;
            }
            if (value <= 0) {
                value = 1;
            }
            if (value > 0) {
                bits[n] |= 2;
                res[n] = func_ov000_0215a004(self, ids[i], ids[i], value, &bits[n], 0, 0, 1);
                applied[n] = value;
                tgt[n] = ids[i];
                n++;
            }
        }
    }
    if (n > 0) {
        func_ov000_0215c758(self, tgt, n, 2, res, app, bp);
    }
}
