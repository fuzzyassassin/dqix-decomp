#include <globaldefs.h>
#include "GameState/GameState.h"

struct Obj02049c08;
struct Obj02033874;
struct Node021df5cc;

struct Node021df568 {
    int key;
    struct Node021df568* prev;
    struct Node021df568* next;
    GameObject* obj;
};

extern "C" int _Z23DispatchByIndex021820bcPviii(void* obj, int unused, int index, int arg);
extern "C" Vector3fix _Z20GetSubTriple02049c08P11Obj02049c08(struct Obj02049c08* obj);
extern "C" void _Z24SetVecYFromValue02033874P11Obj02033874i(struct Obj02033874* obj, int arg);
extern "C" void _Z20ResetFields_021df554Pv(void* obj);
extern "C" struct Node021df568* _Z21InsertSorted_021df568P12Node021df568S0_(struct Node021df568* head, struct Node021df568* newNode);
extern "C" struct Node021df5cc* _Z20FindLastNode021df5ccP12Node021df5cc(struct Node021df5cc* node);
extern "C" fix32_t fix32_Divide(fix32_t a, fix32_t b);

static inline int FxMul(int a, int b) { return (int)(((long long)a * b + 0x800) >> 12); }

struct Obj021def64 {
    char pad[0x29c];
    void* list;
};

// USA: func_ov025_021def64
extern "C" ARM void func_ov025_021def64(struct Obj021def64* self, int slot, int index) {
    struct Node021df568 nodesX[16];
    struct Node021df568 nodesZ[16];
    int ids[16];
    GameObject* objs[16];
    GameState* gs = GameState::GetInstance();
    int count = _Z23DispatchByIndex021820bcPviii(self->list, slot, index, (int)ids);
    if (count == 0) return;

    int n = 0;
    int i;
    for (i = 0; i < count; i++) {
        objs[n] = gs->GetCombatantByIndex(ids[i]);
        if (objs[n] == NULL) continue;
        GameObject* o = objs[i];
        o->obj3D_.position_ = _Z20GetSubTriple02049c08P11Obj02049c08((struct Obj02049c08*)o);
        _Z24SetVecYFromValue02033874P11Obj02033874i((struct Obj02033874*)o, 0);
        n++;
    }
    count = n;

    // Spread the combatants along x so their radii do not overlap.
    {
        int k;
        int gapSum;
        int radSum;
        struct Node021df568* head;
        struct Node021df568* next;
        fix32_t scale;
        int pos;
        int r;
        int gap;
        struct Node021df568* cur;
        struct Node021df568* last;
        int span;
        int i2;
        for (i = 0; i < count; i++) {
            _Z20ResetFields_021df554Pv(&nodesX[i]);
            GameObject* o = objs[i];
            nodesX[i].key = _Z20GetSubTriple02049c08P11Obj02049c08((struct Obj02049c08*)o).x;
            nodesX[i].obj = o;
        }
        head = &nodesX[0];
        for (i2 = 1; i2 < count; i2++) {
            head = _Z21InsertSorted_021df568P12Node021df568S0_(head, &nodesX[i2]);
        }
        last = (struct Node021df568*)_Z20FindLastNode021df5ccP12Node021df5cc((struct Node021df5cc*)head);
        span = (last->key + last->obj->obj3D_.GetRadius() / 2) - (head->key - head->obj->obj3D_.GetRadius() / 2);
        if (span > 0x4000 && n > 1) {
            int gaps[16];
            gapSum = 0;
            radSum = 0;
            cur = head;
            k = 0;
            for (; (next = cur->next) != NULL; cur = cur->next) {
                r = cur->obj->obj3D_.GetRadius();
                gap = (next->key - cur->key) - (next->obj->obj3D_.GetRadius() / 2 + r / 2);
                gaps[k] = gap;
                gapSum += gap;
                k++;
            }
            for (cur = head; cur != NULL; cur = cur->next) {
                radSum += cur->obj->obj3D_.GetRadius();
            }
            scale = 0;
            if (radSum < 0x4000 && gapSum != 0) {
                scale = fix32_Divide(0x4000 - radSum, gapSum);
            }
            k = 0;
            cur = head;
            gapSum = 0;
            while ((cur = cur->next) != NULL) {
                gaps[k] = FxMul(gaps[k], scale);
                gapSum += gaps[k];
                k++;
            }
            pos = -((radSum + gapSum) / 2);
            k = 0;
            for (cur = head; cur != NULL; cur = cur->next, k++) {
                pos += cur->obj->obj3D_.GetRadius() / 2;
                Vector3fix p = cur->obj->obj3D_.position_;
                p.x = pos;
                cur->key = pos;
                cur->obj->obj3D_.position_ = p;
                pos += cur->obj->obj3D_.GetRadius() / 2;
                pos += gaps[k];
            }
        } else {
            int off = -((head->key - head->obj->obj3D_.GetRadius() / 2) + span / 2);
            for (; head != NULL; head = head->next) {
                Vector3fix p = head->obj->obj3D_.position_;
                p.x += off;
                head->obj->obj3D_.position_ = p;
            }
        }
    }

    // Same again along z.
    {
        int k;
        int gapSum;
        int radSum;
        struct Node021df568* head;
        struct Node021df568* last;
        int span;
        struct Node021df568* next;
        fix32_t scale;
        int pos;
        int r;
        int gap;
        struct Node021df568* cur;
        int i2;
        for (i = 0; i < count; i++) {
            _Z20ResetFields_021df554Pv(&nodesZ[i]);
            GameObject* o = objs[i];
            nodesZ[i].key = _Z20GetSubTriple02049c08P11Obj02049c08((struct Obj02049c08*)o).z;
            nodesZ[i].obj = o;
        }
        head = &nodesZ[0];
        for (i2 = 1; i2 < count; i2++) {
            head = _Z21InsertSorted_021df568P12Node021df568S0_(head, &nodesZ[i2]);
            for (struct Node021df568* p = head; p != NULL; p = p->next) {
            }
        }
        last = (struct Node021df568*)_Z20FindLastNode021df5ccP12Node021df5cc((struct Node021df5cc*)head);
        span = (last->key + last->obj->obj3D_.GetRadius() / 2) - (head->key - head->obj->obj3D_.GetRadius() / 2);
        if (span > 0x4000 && n > 1) {
            int gaps[16];
            gapSum = 0;
            radSum = 0;
            cur = head;
            k = 0;
            for (; (next = cur->next) != NULL; cur = cur->next) {
                r = cur->obj->obj3D_.GetRadius();
                gap = (next->key - cur->key) - (next->obj->obj3D_.GetRadius() / 2 + r / 2);
                gaps[k] = gap;
                gapSum += gap;
                k++;
            }
            for (cur = head; cur != NULL; cur = cur->next) {
                radSum += cur->obj->obj3D_.GetRadius();
            }
            scale = 0;
            if (radSum < 0x4000 && gapSum != 0) {
                scale = fix32_Divide(0x4000 - radSum, gapSum);
            }
            k = 0;
            cur = head;
            gapSum = 0;
            while ((cur = cur->next) != NULL) {
                gaps[k] = FxMul(gaps[k], scale);
                gapSum += gaps[k];
                k++;
            }
            pos = -((radSum + gapSum) / 2);
            k = 0;
            for (cur = head; cur != NULL; cur = cur->next) {
                pos += cur->obj->obj3D_.GetRadius() / 2;
                Vector3fix p = cur->obj->obj3D_.position_;
                p.z = pos;
                cur->key = pos;
                cur->obj->obj3D_.position_ = p;
                pos += cur->obj->obj3D_.GetRadius() / 2;
                pos += gaps[k];
                k++;
            }
        } else {
            int off = -((head->key - head->obj->obj3D_.GetRadius() / 2) + span / 2);
            for (; head != NULL; head = head->next) {
                Vector3fix p = head->obj->obj3D_.position_;
                p.z += off;
                head->obj->obj3D_.position_ = p;
            }
        }
    }
}
