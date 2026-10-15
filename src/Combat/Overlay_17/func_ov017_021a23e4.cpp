#include <globaldefs.h>
#include "GameState/GameState.h"

struct Entry_02028bd0;
struct BinarySearchByComparatorStruct;
struct MonsterInfo021a23e4 { char field_0[0xc]; short radius; };
struct AreaEntry021a23e4 {
    short id;
    unsigned short category : 2;
    unsigned short flags : 14;
    char field_4[0x5c];
    char masks[0x298];
    char monsters[0xc];
};
struct SpawnEntry021a23e4 { unsigned short variant; };
struct SpawnState021a23e4 {
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char d;
    unsigned char e;
    int f;
    int g;
    int h;
};
struct FieldMonster021a23e4 {
    char field_0[0x130];
    int kind;
    char field_134[4];
    SpawnState021a23e4 spawn;
    char field_14c[0x1e];
    unsigned short state;
};

extern "C" void* func_0202ae18();
extern "C" int func_0202c540(void*);
GameObject* GetCombatantWithFlag0x100_0200ff1c(GameState*, int);
int GetBitflagForCombatantColor_021a26e8(int, int);
extern "C" void* func_0205ec34();
int TestBitInByteArray_0206dfb0(int unused, unsigned char* arr, int index);
Entry_02028bd0* GetEntryTableBase_02027ca4();
AreaEntry021a23e4* FindInlineEntryById(Entry_02028bd0*, int);
SpawnEntry021a23e4* FindMatchingEntryByMask02073ec4(int, void*);
int SelectWeightedEntry02073fdc(void*);
MonsterInfo021a23e4* SearchWithComparator0206f4f0(BinarySearchByComparatorStruct*, int);
int FindCombatantWithNegativeField2_021a20c0(int, int, int);
int GetField0x17dBits4To5IfFlag8_020795cc(unsigned char*);
extern "C" int func_02032370(int);
extern "C" void func_02076a8c(void*);
extern "C" int func_ov017_021a2128(int arena, int areaId, int monsterId, int variant, const Vector3fix* position, int y, int entryId, unsigned char flags);


// USA: func_ov017_021a23e4
extern "C" ARM unsigned short func_ov017_021a23e4(int arena, int combatantId, int mask, int monsterId) {
    GameState* state = GameState::GetInstance();
    if (func_0202c540(func_0202ae18()) != 0) return 0;
    Object3D* combatant = (Object3D*)GetCombatantWithFlag0x100_0200ff1c(state, combatantId);
    if (!combatant) return 0;
    if (mask == 0) mask = GetBitflagForCombatantColor_021a26e8(arena, combatantId);
    int areaId = combatant->GetField06();
    unsigned char* ctx = (unsigned char*)func_0205ec34();
    if (TestBitInByteArray_0206dfb0((int)ctx, ctx + 0x8c, 0x79a) && monsterId != 0x26 && monsterId != 0x27 && monsterId != 0x28 &&
        areaId >= 0x190 && areaId <= 0x199)
        return 0;
    AreaEntry021a23e4* area = FindInlineEntryById(GetEntryTableBase_02027ca4(), areaId);
    if (!area) return 0;
    SpawnEntry021a23e4* spawn = FindMatchingEntryByMask02073ec4(mask, area->masks);
    if (!spawn) return 0;
    if (monsterId < 0) {
        monsterId = SelectWeightedEntry02073fdc(spawn);
        if (monsterId < 0) return 0;
    }
    MonsterInfo021a23e4* info = SearchWithComparator0206f4f0((BinarySearchByComparatorStruct*)area->monsters, (short)monsterId);
    if (!info) return 0;
    int size = info->radius << 2;
    int dist = combatant->GetRadius() / 4 + size / 2;
    Vector3fix position = combatant->GetPointInFront(dist);
    Vector3fix rotation = *(Vector3fix*)((char*)combatant + 0x50);
    int angle = fix32ReduceAngle0To2Pi(rotation.y + 0x3244);
    if (FindCombatantWithNegativeField2_021a20c0(arena, area->category, 12) < 0) {
        int candidates[12];
        int count = 0;
        for (int i = 0; i < 12; i++) {
            int index = i + (area->category * 12 + 0x70);
            FieldMonster021a23e4* m = (FieldMonster021a23e4*)state->GetMaybeFieldMonsterByIndex(index);
            if (m && m->kind != 9 && GetField0x17dBits4To5IfFlag8_020795cc((unsigned char*)m) < 0)
                candidates[count++] = index;
        }
        Object3D* victim = (Object3D*)state->GetMaybeFieldMonsterByIndex(candidates[func_02032370(count)]);
        if (victim) {
            func_02076a8c(victim);
            victim->MakeHidden();
        }
    }
    int slot = func_ov017_021a2128(arena, areaId, monsterId, spawn->variant, &position, angle, 0, (combatantId << 4) | 8);
    if (!slot) return 0;
    FieldMonster021a23e4* monster = (FieldMonster021a23e4*)state->GetMaybeFieldMonsterByIndex(slot);
    if (!monster) return 0;
    SpawnState021a23e4 s;
    SpawnState021a23e4* p = &s;
    p->a = monster->spawn.a;
    p->b = monster->spawn.b;
    p->c = monster->spawn.c;
    p->d = monster->spawn.d;
    p->e = monster->spawn.e;
    p->f = monster->spawn.f;
    p->g = monster->spawn.g;
    p->h = monster->spawn.h;
    p->a = 0;
    p->c = 0;
    monster->spawn.a = p->a;
    monster->spawn.b = p->b;
    monster->spawn.c = p->c;
    monster->spawn.d = p->d;
    monster->spawn.e = p->e;
    monster->spawn.f = p->f;
    monster->spawn.g = p->g;
    monster->spawn.h = p->h;
    return monster->state;
}
