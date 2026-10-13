#include <globaldefs.h>
#include "GameState/GameState.h"

struct List02160094;
struct ListNode02160094 { char pad[0x20]; unsigned short id; };
struct List021600f8 { char pad[9]; unsigned char count; };
struct ListNode021600f8 { char pad[0xe]; short id; };

struct CameraCmd021e3c80 {
    char pad[8];
    unsigned short type;
    unsigned char mode;
    float x;
    float y;
    float z;
};

struct Holder021e3c80 {
    char pad[0xc];
    char* ctx;
    char pad10[0x1c - 0x10];
    unsigned int flags;
};
extern Holder021e3c80 data_ov025_021ef988;

void* GetActiveCombatWork();
extern "C" char* func_ov000_02160f14(void* work);
extern "C" ListNode02160094* _Z22GetNodeAtIndex02160094P12List02160094i(List02160094* list, int index);
extern "C" ListNode021600f8* _Z22GetNodeAtIndex021600f8P12List021600f8i(List021600f8* list, int index);
extern "C" void func_ov000_021626a0(void* work, int index, int show);
extern "C" void func_ov025_021eb8e8(char* ctx);
extern "C" void func_ov000_0216d600(char* camera, int side, int close, int mode, float x, float y, float z, unsigned char overridePosition);
extern "C" void func_ov000_0216d90c(char* camera, int index);
extern "C" void _Z24CheckAndSetFlag_021eba60Pc(char* obj);
extern "C" void func_ov000_0216da34(char* camera, int idxA, int idxB);
extern "C" struct Random* _Z24GetRandomFromObj02160ef8Ph(unsigned char* obj);
extern "C" int _Z23DispatchByIndex021820bcPviii(void* obj, int unused, int index, int arg);
extern "C" void func_ov000_0216dbf0(char* camera, int* ids, int count, short flag);
extern "C" void func_ov000_0216de00(char* camera, int idxA, int idxB);
extern "C" void func_ov000_0216df00(char* camera, int id, int force, float offset, float factor);
extern "C" short func_ov000_0215ffa0(void* node);
extern "C" void func_ov000_0216e250(char* camera, int* ids, int count);
extern "C" void func_ov000_0216d370(char* camera, int flagA, int flagB, int flagC);
extern "C" void func_ov000_0216f2b8(char* camera);

// USA: func_ov025_021e3c80
extern "C" ARM int func_ov025_021e3c80(CameraCmd021e3c80* cmd, List02160094* list) {
    int buf[12];
    int ids[8];
    unsigned char* work = (unsigned char*)GetActiveCombatWork();
    char* camera = func_ov000_02160f14(work);
    char* ctx = data_ov025_021ef988.ctx;
    ListNode02160094* actor = _Z22GetNodeAtIndex02160094P12List02160094i(list, 0);
    ListNode021600f8* target = _Z22GetNodeAtIndex021600f8P12List021600f8i((List021600f8*)list, 0);
    if (*(unsigned int*)(ctx + 0x1c4) & 0x40) {
        func_ov000_021626a0(work, 4, 1);
        *(unsigned int*)(ctx + 0x1c4) &= ~0x40;
    }
    camera[0x221] = 1;
    int moved = 0;
    func_ov025_021eb8e8(ctx);
    switch (cmd->type) {
    case 0:
        moved = 1;
        func_ov000_0216d600(camera, 1, 0, 0, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 15:
        moved = 1;
        func_ov000_0216d600(camera, 1, 1, 0, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 1:
        if (actor == 0) return 1;
        func_ov000_0216d90c(camera, actor->id);
        _Z24CheckAndSetFlag_021eba60Pc(ctx);
        break;
    case 2:
        if (actor == 0 || target == 0) return 1;
        func_ov000_0216da34(camera, actor->id, target->id);
        break;
    case 3:
    case 11: {
        struct Random* rnd = _Z24GetRandomFromObj02160ef8Ph(work);
        int count = _Z23DispatchByIndex021820bcPviii(rnd, (int)list, 0x33, (int)buf);
        func_ov000_0216dbf0(camera, buf, count, cmd->type == 11);
        moved = 1;
        break;
    }
    case 4:
        if (actor == 0 || target == 0) return 1;
        func_ov000_0216de00(camera, actor->id, target->id);
        moved = 1;
        break;
    case 5:
    case 13: {
        if (actor == 0) return 1;
        if (cmd->type == 13) moved = 1;
        float factor = cmd->z;
        float offset = cmd->y;
        func_ov000_0216df00(camera, actor->id, moved, offset, factor);
        _Z24CheckAndSetFlag_021eba60Pc(ctx);
        moved = 1;
        break;
    }
    case 6:
    case 14: {
        if (target == 0) return 1;
        if (cmd->type == 14) moved = 1;
        float factor = cmd->z;
        float offset = cmd->y;
        func_ov000_0216df00(camera, target->id, moved, offset, factor);
        _Z24CheckAndSetFlag_021eba60Pc(ctx);
        moved = 1;
        break;
    }
    case 12: {
        if (target == 0) return 1;
        short id = func_ov000_0215ffa0(target);
        void* other = GetActiveCombatWork();
        if (other != 0) {
            func_ov000_021626a0(other, 4, 0);
        }
        GameObject* obj = GameState::GetInstance()->GetCombatantByIndex(id);
        if (obj != 0) {
            obj->obj3D_.MakeVisible();
        }
        func_ov000_0216df00(camera, id, 0, 0.0f, 1.8f);
        moved = 1;
        break;
    }
    case 7: {
        int count = ((List021600f8*)list)->count;
        for (int i = 0; i < count; i++) {
            ListNode021600f8* node = _Z22GetNodeAtIndex021600f8P12List021600f8i((List021600f8*)list, i);
            if (node != 0) {
                ids[i] = node->id;
            }
        }
        func_ov000_0216e250(camera, ids, count);
        moved = 1;
        break;
    }
    case 8: {
        if (actor == 0) return 1;
        int isMonster = actor->id > 3 ? 1 : 0;
        unsigned char side = isMonster ? 1 : 0;
        func_ov000_0216d600(camera, side, 0, cmd->mode, cmd->x, cmd->y, cmd->z, 0);
        moved = 1;
        break;
    }
    case 9: {
        if (target == 0) return 1;
        int isParty = 0;
        if (target->id >= 0 && target->id <= 3) isParty = 1;
        unsigned char side = isParty ? 0 : 1;
        func_ov000_0216d600(camera, side, 0, cmd->mode, cmd->x, cmd->y, cmd->z, 0);
        moved = 1;
        break;
    }
    case 10:
        func_ov000_0216d370(camera, 0, 0, 0);
        break;
    }
    if (work != 0 && moved) {
        work[0x6fd5] = 1;
    }
    data_ov025_021ef988.flags |= 8;
    *(int*)(data_ov025_021ef988.ctx + 0x224) = 0;
    func_ov000_0216f2b8(camera);
    return 1;
}
