#include <globaldefs.h>
#include "GameState/GameState.h"
#include "Graphics/Vector.h"
#include "World/Object3D.h"
#include "World/ZoneFeatures.h"

struct List02160094;
struct List021600f8;
struct ActorNode021db458 { char pad0[0x20]; unsigned short id; char pad22[0xe]; ActorNode021db458* next; };
struct TargetNode021db458 { char pad0[0xe]; short ids[4]; char pad16; unsigned char count; char pad18[8]; TargetNode021db458* next; };
struct Body021db458 { char pad0[4]; short id; char pad6[0x3e]; WrappedVector3fix position; };

struct Work021db458 {
    char pad0[0x29c];
    void* field29c;
    char pad2a0[0xe94 - 0x2a0];
    void* list;
    char padE98[0x5951 - 0xe98];
    unsigned char mode : 2;
    unsigned char flags : 6;
};

extern "C" void* _Z18GetSlotPtr02160f20Pv(void*);
extern "C" int func_ov000_0215e9fc(void* obj, short* buf, int max, int start);
extern "C" int func_ov000_0215ec1c(void* obj, short* buf, int max, int start);
extern "C" int _Z35IsSubstructByte0x4fNonZero_02049afcPh(unsigned char* obj);
extern "C" void* __clear(void* dst, int count);
extern "C" ActorNode021db458* _Z22GetNodeAtIndex02160094P12List02160094i(List02160094*, int);
extern "C" TargetNode021db458* _Z22GetNodeAtIndex021600f8P12List021600f8i(List021600f8*, int);

// USA: func_ov025_021db458
extern "C" ARM void func_ov025_021db458(Work021db458* work) {
    int reach;
    int j;
    _Z18GetSlotPtr02160f20Pv(work);
    GameState* game = GameState::GetInstance();
    if (work->mode != 2) return;
    void* list;
    short ids[16];
    int count = 0;
    count = count + func_ov000_0215e9fc(work->field29c, ids, 0x10, count);
    count = count + func_ov000_0215ec1c(work->field29c, ids + count, 0x10 - count, 0);
    for (int i = 0; i < count; i++) {
        GameObject* obj = game->GetCombatantByIndex(ids[i]);
        if (!obj) continue;
        if (!_Z35IsSubstructByte0x4fNonZero_02049afcPh((unsigned char*)obj) || (list = work->list) == 0) continue;
        WrappedVector3fix dir;
        WrappedVector3fix otherPos;
        WrappedVector3fix pos;
        WrappedVector3fix push;
        ActorNode021db458* actors;
        GameState* state = GameState::GetInstance();
        __clear(&push.vec, sizeof(push));
        Body021db458* body = (Body021db458*)obj;
        int k;
        short* id = ids;
        pos = body->position;
        pos.vec.y = 0xcc;
        actors = _Z22GetNodeAtIndex02160094P12List02160094i((List02160094*)list, 0);
        TargetNode021db458* targets = _Z22GetNodeAtIndex021600f8P12List021600f8i((List021600f8*)list, 0);
        ActorNode021db458* a = actors;
        int self = body->id;
        for (; a; a = a->next) {
            if (a->id == body->id) goto next;
        }
        for (TargetNode021db458* t = targets; t; t = t->next) {
            short* p = t->ids;
            for (j = 0; j < t->count; j++, p++) {
                if (*p == self) goto next;
            }
        }
        for (k = 0; k < (short)count; id++, k++) {
            ActorNode021db458* b;
            int unique = 1;
            for (b = actors; b; b = b->next) {
                if (b->id == *id) { unique = 0; break; }
            }
            if (!unique || *id == body->id) continue;
            GameObject* other = state->GetGameObjectByIndex(*id);
            if (!other) continue;
            reach = obj->obj3D_.GetRadius();
            reach += other->obj3D_.GetRadius();
            otherPos = ((Body021db458*)other)->position;
            otherPos.vec.y = 0xcc;
            int dist = Vector3fix_Distance(&pos.vec, &otherPos.vec);
            if (dist <= 0 || dist >= (reach >> 1)) continue;
            Vector3fix_Subtract(&pos.vec, &otherPos.vec, &dir.vec);
            Vector3fixMultiplyScalar(&dir.vec, fix32_Divide(((reach >> 1) - dist) >> 2, dist), &dir.vec);
            Vector3fix_Add(&push.vec, &dir.vec, &push.vec);
        }
        Vector3fix_Add(&pos.vec, &push.vec, &pos.vec);
        body->position.vec = pos.vec;
    next:;
    }
}
