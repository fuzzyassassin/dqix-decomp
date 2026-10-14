#include <globaldefs.h>
#include "std_library_functions.h"
#include "GameState/GameState.h"

#if defined(jpn)
enum { listOffset = 0x4ec, fiveOffset = 0x928, readyOffset = 0x1e4, serialBase = 0x120, serialPage = 0x6000 };
#else
enum { listOffset = 0x6fc, fiveOffset = 0xb48, readyOffset = 0x494, serialBase = 0x2380, serialPage = 0x4000 };
#endif

extern "C" int rand(void);

struct Vec3_0216ed9c { int x, y, z; };

class Node0216ed9c {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void SetPosition(const Vec3_0216ed9c* v);
};

struct PackedField017 {
    unsigned int low : 12;
    unsigned int f12 : 4;
    unsigned int f16 : 5;
    unsigned int f21 : 5;
    unsigned int top : 6;
};

struct Ov004Block_0216ed9c {
    unsigned int word00;
    unsigned int word04;
    unsigned int word08;
    unsigned short half0c;
    unsigned char pad0e[0x20];
    unsigned char flags2e[6];
    signed char flag34;
    PackedField017 cfg;
    unsigned char counts[12];
    int numSpawned;
};

struct Struct02171048_0216ed9c {
    unsigned char shown0;
    unsigned char shown1;
    char pad[2];
    Ov004Block_0216ed9c* ptr;
};
extern Struct02171048_0216ed9c data_ov004_02171048;

struct MonthDays_0216ed9c { unsigned int days[12]; };
extern MonthDays_0216ed9c data_ov004_0217028c;

struct QuestView0216ed9c {
    unsigned char unknown00[0x44];
    PackedField017 identifier;
};

struct TableA68;
struct StoreStruct;
struct Obj24_021b2024;
struct Obj24_021b2038;
struct Obj24_021b204c;
struct Obj24_021b1fe8;
struct Obj24_021b1ffc;

extern "C" void* func_ov004_0216ea38(void* ctx, int key);
extern "C" int _Z26GetGlobalField0x1c020421a0v(void);
int GetBattleSubField0xbcForState(void);
extern "C" void* func_ov011_021849c8(void*);
extern "C" Node0216ed9c* func_ov023_021f6880(void*, int);
extern "C" int func_ov023_021f6f10(void*);
extern "C" void func_ov023_021fb27c(void* node, unsigned short v);
extern "C" void func_ov017_021b1e24(void* a, void* b);
extern "C" int _Z34GetFieldromField_021b1fd4_021b1fd4Pv(void* obj);
extern "C" void func_ov023_021fa078(void* obj, void* ctx, unsigned short val, Vec3_0216ed9c* srcVec, int p5, int p6);
extern "C" unsigned char _Z26GetSubByteField34_021b2024P14Obj24_021b2024(Obj24_021b2024* obj);
extern "C" unsigned char _Z26GetSubByteField35_021b2038P14Obj24_021b2038(Obj24_021b2038* obj);
void* FindEntryByKey(TableA68* table, int key);
extern "C" void func_0204500c(void* field, void* buf, int p2, int p3);
extern "C" unsigned char _Z27GetSubByteField438_021b204cP14Obj24_021b204c(Obj24_021b204c* obj);
extern "C" unsigned char _Z26GetSubByteField44_021b1fe8P14Obj24_021b1fe8(Obj24_021b1fe8* obj);
extern "C" void* _Z38GetOffsetPtrromField_021b1fc0_021b1fc0Pv(void* obj);
extern "C" void func_ov011_021848a0(void* obj, int val);
extern "C" int _Z37SendBattleSaveBufferOrSetFlag020ac7b4i(int flag);
extern "C" int _Z27GetSubWordField394_021b1ffcP14Obj24_021b1ffc(Obj24_021b1ffc* obj);
extern "C" void func_02046380(void* g);
void StoreInArray0x8b0(StoreStruct* base, int index, int value);

static inline char* GetFive(char* actor) {
    return *(char**)(actor + 0x3000 + fiveOffset);
}

// USA: func_ov004_0216ed9c
extern "C" ARM int func_ov004_0216ed9c(void* self) {
    Node0216ed9c* node;
    GameState* gs = GameState::GetInstance();
    char* actor = (char*)func_ov017_0218b5b0();
    void* list = *(void**)(actor + 0x3000 + listOffset);
    char* five = GetFive(actor);
    TableA68* table = (TableA68*)func_ov004_0216ea38(self, 4);
    int g = _Z26GetGlobalField0x1c020421a0v();
    unsigned char state = data_ov004_02171048.ptr->flags2e[0];

    if (state == 2) {
        int v = GetBattleSubField0xbcForState();
        node = func_ov023_021f6880(func_ov011_021849c8(self), 0x97);
        if (node == 0 || func_ov023_021f6f10(node) != 1) {
            node = 0;
        }
        func_ov023_021fb27c(node, v + 8);
        func_ov017_021b1e24(five, list);
        {
            int slot;
            Ov004Block_0216ed9c* blk;
            Ov004Block_0216ed9c* block;
            int n;
            int i;
            Node0216ed9c* coin;
            int id;
            int total = _Z34GetFieldromField_021b1fd4_021b1fd4Pv(five) >> 12;
            int count = total - data_ov004_02171048.ptr->numSpawned;
            if (count == 0) goto spawned;

            for (i = 0; i < count; i++) {
                slot = rand() % 12;
                blk = data_ov004_02171048.ptr;
                while (blk->counts[slot] >= 10) {
                    slot = (slot + 1) % 12;
                }
                blk->counts[slot]++;

                block = data_ov004_02171048.ptr;
                n = block->counts[slot];
                id = block->numSpawned + 0x578 + i;

                coin = func_ov023_021f6880(func_ov011_021849c8(self), id);
                if (coin == 0 || func_ov023_021f6f10(coin) != 0) {
                    coin = 0;
                }
                if (!coin) goto spawned;

                Vec3_0216ed9c dst;
                Vec3_0216ed9c pos;
                pos.x = (slot * 21) << 12;
                pos.y = (n * -19) << 12;
                pos.z = 0;
                coin->SetPosition(&pos);

                dst.x = (slot * 21) << 12;
                dst.y = (0xc0 - n * 19) << 12;
                dst.z = 0;

                void* effect = func_ov023_021f6880(func_ov011_021849c8(self), 0xffff);
                if (!effect) goto spawned;
                func_ov023_021fa078(effect, self, id, &dst, 0xd000, 0xd000);
            }
            data_ov004_02171048.ptr->numSpawned = total;
        }
spawned:

        unsigned char a = _Z26GetSubByteField34_021b2024P14Obj24_021b2024((Obj24_021b2024*)five);
        unsigned char b = _Z26GetSubByteField35_021b2038P14Obj24_021b2038((Obj24_021b2038*)five);
        if (data_ov004_02171048.shown1 == 0 && a == 5 && b == 0) {
            func_0204500c((void*)g, FindEntryByKey(table, 0xcc), 0, 0xe3);
            *(int*)(g + 0x998) = 1;
            data_ov004_02171048.shown1 = 1;
        }
        if (data_ov004_02171048.shown0 == 0 && a == 5 && b == 5) {
            func_0204500c((void*)g, FindEntryByKey(table, 0xcd), 0, 0xe3);
            *(int*)(g + 0x998) = 1;
            data_ov004_02171048.shown0 = 1;
        }
        if (*(int*)(actor + 0x4000 + readyOffset) == 0) {
            data_ov004_02171048.ptr->flags2e[0]++;
            GameState::GetInstance();
        }
    } else if (state == 3) {
        if (*(int*)(g + 0x9a0) != 3) return 1;

        Node0216ed9c* node = func_ov023_021f6880(func_ov011_021849c8(self), 0x97);
        if (node) {
            *((unsigned char*)node + 0xc) |= 8;
        }
        char* buf = *(char**)(g + 0x5c);
        memset(buf, 0, 0x960);

        if (_Z27GetSubByteField438_021b204cP14Obj24_021b204c((Obj24_021b204c*)five)) {
            const char* s = (const char*)FindEntryByKey(table, 0x71);
            memcpy(buf, s, strlen(s));
        } else if (_Z26GetSubByteField44_021b1fe8P14Obj24_021b1fe8((Obj24_021b1fe8*)five) & 2) {
            _Z38GetOffsetPtrromField_021b1fc0_021b1fc0Pv(five);
            data_ov004_02171048.ptr->flags2e[1] = 1;
            const char* s = (const char*)FindEntryByKey(table, 0xca);
            int len = strlen(s);
            memcpy(buf, s, len);
            if (data_ov004_02171048.ptr->flags2e[3]) {
                const char* s2 = (const char*)FindEntryByKey(table, 0xd6);
                memcpy(buf + len, s2, strlen(s2));
            }
            func_ov011_021848a0(self, 0xca);

            Ov004Block_0216ed9c* blk = data_ov004_02171048.ptr;
            PackedField017* date = &blk->cfg;
            date->f16++;
            if (date->f16 == 0) date->f16 = 1;
            MonthDays_0216ed9c month = data_ov004_0217028c;
            if ((&month.days[-1])[date->f12] < date->f16 || date->f16 == 0) {
                date->f16 = 1;
                date->f12++;
                if (date->f12 > 12) {
                    date->f12 = 1;
                    date->low++;
                }
            }
            memcpy(&((QuestView0216ed9c*)((char*)gs + serialBase + serialPage))->identifier, &data_ov004_02171048.ptr->cfg, 4);
            if (!_Z37SendBattleSaveBufferOrSetFlag020ac7b4i(0)) return 0;
            if (!_Z37SendBattleSaveBufferOrSetFlag020ac7b4i(1)) return 0;
        } else {
            const char* s = (const char*)FindEntryByKey(table, 0xcb);
            memcpy(buf, s, strlen(s));
            int w = _Z27GetSubWordField394_021b1ffcP14Obj24_021b1ffc((Obj24_021b1ffc*)five);
            func_02046380((void*)g);
            StoreInArray0x8b0((StoreStruct*)g, 0, w);
            func_ov011_021848a0(self, 0xcb);
            data_ov004_02171048.ptr->flags2e[1] = 0;
        }

        func_0204500c((void*)g, *(char**)(g + 0x5c), 0, 0xe3);
        *(int*)(g + 0x998) = 1;
        five[1] = 1;
        data_ov004_02171048.ptr->flags2e[0] = 0;
        Ov004Block_0216ed9c* blk = data_ov004_02171048.ptr;
        memset(blk->counts, 0, 0xc);
        blk->numSpawned = 0;
        return 0;
    }
    return 1;
}
