#include <globaldefs.h>
#include "GameState/GameState.h"

void* GetPtrField0x2a04(GameState* battleStruct);
GameObject* GetCombatantWithFlag0x400(GameState* battleStruct, int combatantId);
GameObject* GetCombatantWithFlag0x100(GameState* battleStruct, int combatantId);
int IsFlag0x18Bit0x1000Set(GameObject* combatant);
struct ArrayContainsByteStruct;
int ArrayContainsByte(struct ArrayContainsByteStruct* s, int val);
extern "C" void _Z39IncrementByteCounterCapped0x63_0215a8d4Phi(unsigned char* obj, int idx);
extern "C" float func_ov000_02155a04(GameObject* obj);
struct Outer_02054000;
extern "C" void* _Z21GetActiveSub_02054000P14Outer_02054000(struct Outer_02054000* p);
struct Field150Holder02052df8;
int GetHalfwordEntryFromField150(struct Field150Holder02052df8* obj, int index);
extern "C" int _Z23LoadBattleBlock020ac4c0Pv(void* dst);
struct S_a0840;
void AddSaturateField0x44(struct S_a0840* p, unsigned int amount);
struct S_a02d0;
void AddClamped24BitFieldAt0x20(struct S_a02d0* p, unsigned int amount);
int GetField0x3acValue(GameState* battleStruct);
struct S_a0644;
void AddClamped16BitHighAt0x24(struct S_a0644* p, unsigned int amount);
int CopyInBattleField0x7540(void* src);

extern signed char data_ov000_02182a7c[];

struct StatBits22 {
    unsigned short b0 : 2;
    unsigned short b2 : 4;
    unsigned short b6 : 3;
    unsigned short b9 : 3;
    unsigned short rest : 4;
};

struct StatBits58 {
    unsigned int lo : 9;
    int kind : 3;
    unsigned int rest : 20;
};

struct Stats021554f4 {
    unsigned short f0;
    char unk2[0x14 - 0x2];
    unsigned int f14;
    unsigned int f18;
    char unk1c[0x21 - 0x1c];
    unsigned char f21;
    struct StatBits22 f22;
    unsigned char f24;
    char unk25[0x2e - 0x25];
    short f2e;
    char unk30[0x58 - 0x30];
    union {
        unsigned int raw;
        struct StatBits58 bits;
    } f58;
};

struct Action021554f4 {
    char unk0[8];
    short id;
};

struct Combatant021554f4 {
    char unk0[0x138];
    struct Stats021554f4* stats;
    char unk13c[0x144 - 0x13c];
    struct Action021554f4* action;
    char unk148[0x181 - 0x148];
    unsigned char f181;
    unsigned char f182;
};

struct EntryBits1c {
    unsigned char lo : 4;
    unsigned char hi : 4;
};

struct Entry021554f4 {
    unsigned int a14;
    unsigned int a18;
    unsigned int t14;
    unsigned int t18;
    short actionId;
    short target;
    unsigned short f14;
    short f16;
    struct StatBits22 aBits;
    struct StatBits22 tBits;
    struct EntryBits1c aNib;
    struct EntryBits1c tNib;
    unsigned char flags;
    unsigned char arg;
    float ratio;
    unsigned char f24;
    unsigned char f25;
    unsigned char f26;
    unsigned char pad27;
    unsigned int a58;
    unsigned int t58;
    unsigned short h30[8];
};

struct Arg3_021554f4 {
    unsigned int unk0;
    unsigned int f4 : 12;
    unsigned int rest : 20;
};

struct SubBits {
    char unk0[8];
    unsigned int lo : 4;
    unsigned int f : 5;
    unsigned int rest : 23;
};

struct Info8e18 {
    char unk0[0x24];
    unsigned char f24;
    unsigned char f25;
};

struct Battle021554f4 {
    char unk0[0x5c60];
    struct Entry021554f4 entries[0x10];
    char unk6060[0x8e04 - 0x6060];
    short curIdx;
    signed char curSlot;
    unsigned char count;
    char unk8e08[0x8e18 - 0x8e08];
    struct Info8e18* info;
    char unk8e1c[0x8e20 - 0x8e1c];
    int f8e20;
};

static inline int IsPartyIndex(int i) {
    return (i >= 0 && i <= 3) ? 1 : 0;
}

// USA: func_ov000_021554f4
extern "C" ARM void func_ov000_021554f4(struct Battle021554f4* self, int idx, int target, struct Arg3_021554f4* arg3, unsigned char arg4, int flags) {
    char buf[0xb0];
    unsigned short v;
    unsigned int x;
    GameState* gs = GameState::GetInstance();
    struct ArrayContainsByteStruct* list = (struct ArrayContainsByteStruct*)GetPtrField0x2a04(GameState::GetInstance());
    struct Combatant021554f4* c = (struct Combatant021554f4*)GetCombatantWithFlag0x400(gs, idx);
    if (c == 0) return;

    if (c->stats->f0 == 0 && flags == 8) {
        if (self->curSlot < 0) return;
        if (self->curIdx == idx) {
            *((unsigned char*)&self->entries[self->curSlot] + 0x1e) = flags;
        }
        return;
    }

    if (c->action != 0 && c->action->id == 0xf5 && IsFlag0x18Bit0x1000Set((GameObject*)c)
        && ArrayContainsByte(list, c->stats->f2e)
        && !(IsFlag0x18Bit0x1000Set((GameObject*)c) && c->f181 != 0)
        && c->f182 != 0 && ArrayContainsByte(list, target)) {
        struct Combatant021554f4* t = (struct Combatant021554f4*)GameState::GetInstance()->GetCombatantByIndex(target);
        if (t != 0 && t->stats->f58.bits.kind == 2) {
            _Z39IncrementByteCounterCapped0x63_0215a8d4Phi((unsigned char*)self, 8);
        }
    }

    self->curIdx = -1;
    self->curSlot = -1;
    if (self->count >= 0x10) return;
    if (IsPartyIndex(idx)) return;

    self->curIdx = idx;
    self->curSlot = self->count;
    struct Action021554f4* action = c->action;
    struct Entry021554f4* e;
    struct Combatant021554f4* t = (struct Combatant021554f4*)GameState::GetInstance()->GetCombatantByIndex(target);
    e = &self->entries[self->count++];
    memset(e, 0, sizeof(*e));

    unsigned int w = c->stats->f18;
    if (c->f181 != 0) w &= ~0x1000;
    x = c->stats->f14;
    e->a14 = x;
    e->a18 = w;
    v = c->stats->f22.b0;
    e->aBits.b0 = v;
    v = c->stats->f22.b2;
    e->aBits.b2 = v;
    v = c->stats->f22.b6;
    e->aBits.b6 = v;
    v = c->stats->f21;
    e->aNib.lo = v;
    v = c->stats->f24;
    e->aNib.hi = v;
    v = c->stats->f22.b9;
    e->aBits.b9 = v;
    x = c->stats->f58.raw;
    e->a58 = x;

    x = t->stats->f14;
    e->t14 = x;
    x = t->stats->f18;
    e->t18 = x;
    v = t->stats->f22.b0;
    e->tBits.b0 = v;
    v = t->stats->f22.b2;
    e->tBits.b2 = v;
    v = t->stats->f22.b6;
    e->tBits.b6 = v;
    v = t->stats->f21;
    e->tNib.lo = v;
    v = t->stats->f24;
    e->tNib.hi = v;
    v = t->stats->f22.b9;
    e->tBits.b9 = v;
    x = t->stats->f58.raw;
    e->t58 = x;

    v = action->id;
    e->actionId = v;
    e->target = target;
    e->flags = flags;
    e->arg = arg4;
    e->f16 = self->f8e20;
    e->ratio = func_ov000_02155a04((GameObject*)c);
    e->f24 = 0;
    e->f25 = self->info->f24;
    e->f26 = self->info->f25;
    if (arg3 != 0) {
        e->f14 = arg3->f4;
    }

    if (IsPartyIndex(target)) {
        GameObject* o = GetCombatantWithFlag0x100(gs, target);
        if (o == 0) return;
        struct SubBits* sub = (struct SubBits*)_Z21GetActiveSub_02054000P14Outer_02054000((struct Outer_02054000*)o);
        if (sub != 0) {
            e->f24 = sub->f;
        }
        for (int i = 0; data_ov000_02182a7c[i] != -1; i++) {
            e->h30[i] = GetHalfwordEntryFromField150((struct Field150Holder02052df8*)o, data_ov000_02182a7c[i]);
        }
    }

    if (!ArrayContainsByte(list, target)) return;
    if (flags & 1) return;
    if (flags & 2) return;
    if (flags & 4) return;
    if (flags & 0x10) return;
    if (flags & 0x20) return;

    _Z23LoadBattleBlock020ac4c0Pv(buf);
    AddSaturateField0x44((struct S_a0840*)buf, 1);
    AddClamped24BitFieldAt0x20((struct S_a02d0*)(buf + 0x68), 1);
    if (target == GetField0x3acValue(gs)) {
        AddClamped16BitHighAt0x24((struct S_a0644*)buf, 1);
    }
    CopyInBattleField0x7540(buf);
}
