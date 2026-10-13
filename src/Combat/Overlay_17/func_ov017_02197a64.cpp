#if defined(jpn)
enum { RegionOffset6c = 0x8c };
#else
enum { RegionOffset6c = 0x6c };
#endif

#include <globaldefs.h>
#include "GameState/GameState.h"
#include "Resource/GameResources.h"
#include "Graphics/Vector.h"

struct Obj020968d0;

struct GroupNode02197a64 {
    unsigned char pad0[0x8];
    Vector3fix position;
    unsigned char pad14[0x20 - 0x14];
    short angle;
    unsigned char pad22[0x2e - 0x22];
    unsigned short low : 4;
    unsigned short flags : 12;
    unsigned char pad30[0x70 - 0x30];
    struct GroupNode02197a64* next;
};

struct Leader02197a64 {
    unsigned char pad0[0x44];
    Vector3fix position;
    unsigned char pad50[0x54 - 0x50];
    int rotationY;
    unsigned char pad58[0xbe - 0x58];
    unsigned char mode;
};

struct Resources02197a64 {
    unsigned char pad0[0x4438];
    Vector3fix heading;
};

struct Self02197a64 {
    unsigned char pad0[0x42ec];
    short strayCount;
};

struct GroupEvent02197a64 {
    unsigned char tag;
    unsigned char pad1[3];
    unsigned char count;
    unsigned char pad5[3];
    struct GroupNode02197a64* nodes[2];
    short angle;
    short pad12;
};

extern "C" void* func_02012fe4(void);
void* GetPointerFromArray0x3c(unsigned char* obj, unsigned int index);
extern "C" Obj020968d0* _Z21GetField4328_0218d268Pv(void* res);
extern "C" void _Z15InitObj0219a674Ph(unsigned char* self);
extern "C" int func_02094b9c(void* a, void* b);
extern "C" int _Z27BuildAndForwardVec_0218da48Pviiih(void* obj, int angle, int c, int d, unsigned char e);
extern "C" int _Z31CheckAndComputeDistance020968d0P11Obj020968d0Pi(Obj020968d0* obj, int* outDist);
int TestFlagMask(unsigned short* flags, int mask);
extern "C" void __clear(void* buf, int count);
extern "C" short _Z32GetAbsAngleDeltaBetween_021a4754P4Vec3iS0_(Vector3fix* from, int baseAngle, Vector3fix* to);
extern "C" void func_ov017_0219b33c(Self02197a64* self, GroupEvent02197a64* event);
extern "C" void func_ov017_02198f84(Self02197a64* self);

extern unsigned short data_02114e30;

#define FACING_LIMIT ((int)(0.8f * 4096.0f))

// USA: func_ov017_02197a64
extern "C" ARM void func_ov017_02197a64(Self02197a64* self) {
    GameState* gs = GameState::GetInstance();
    Resources02197a64* res = (Resources02197a64*)func_ov017_0218b5b0();
    void* cache = func_02012fe4();
    Leader02197a64* leader = (Leader02197a64*)gs->GetUnknownGameObject();
    Vector3fix filter = leader->position;
    GroupNode02197a64* node = (GroupNode02197a64*)GetPointerFromArray0x3c((unsigned char*)cache + RegionOffset6c, 2);
    Obj020968d0* field = _Z21GetField4328_0218d268Pv(res);
    int notify = 0;
    GroupEvent02197a64 event;
    _Z15InitObj0219a674Ph((unsigned char*)&event);
    int counted = 0;
    int built = 0;

    while (node != NULL && event.count < 2) {
        if (!(node->flags & 1) && !(node->flags & 4) && func_02094b9c(node, &filter)) {
            if (!built) {
                built = _Z27BuildAndForwardVec_0218da48Pviiih(self, node->angle, FACING_LIMIT, FACING_LIMIT >> 3, 0);
            }
            Vector3fix dir;
            int c = fix32cos(node->angle);
            dir.x = fix32sin(node->angle);
            dir.y = 0;
            dir.z = c;
            Vector3fix_Normalize(&dir, &dir);
            Vector3fix fwd;
            c = fix32cos(leader->rotationY);
            fwd.x = fix32sin(leader->rotationY);
            fwd.y = 0;
            fwd.z = c;
            Vector3fix_Normalize(&fwd, &fwd);
            Vector3fix heading = res->heading;
            int facing = Vector3fix_InnerProduct(&dir, &fwd);
            int along = Vector3fix_InnerProduct(&dir, &heading);
            if ((heading.x != 0 || heading.z != 0) &&
                (_Z31CheckAndComputeDistance020968d0P11Obj020968d0Pi(field, NULL) != 0 || TestFlagMask(&data_02114e30, 0xf0) != 0)) {
                facing = along;
            }
            if (node->flags & 0x10) {
                Vector3fix toNode;
                Vector3fix_Subtract(&filter, &node->position, &toNode);
                toNode.y = 0;
                Vector3fix_Normalize(&toNode, &toNode);
                if (Vector3fix_InnerProduct(&dir, &toNode) > 0) {
                    if (facing >= 0) {
                        node = node->next;
                        continue;
                    }
                } else {
                    if (facing <= 0) {
                        node = node->next;
                        continue;
                    }
                }
            } else {
                if (facing > 0) {
                    node = node->next;
                    continue;
                }
            }
            event.nodes[event.count++] = node;
            if (self->strayCount <= 2) {
                if (leader->mode == 1 &&
                    (along < 0x170 - FACING_LIMIT || along > FACING_LIMIT - 0x170 ||
                     facing < 0x170 - FACING_LIMIT || facing > FACING_LIMIT - 0x170)) {
                    if (!counted) {
                        counted = 1;
                        self->strayCount++;
                    }
                } else {
                    self->strayCount = 0;
                }
            } else if (self->strayCount > 2) {
                if (!counted) notify = 1;
            }
        }
        node = node->next;
    }

    if (event.count != 0) {
        Vector3fix center;
        __clear(&center, sizeof(center));
        for (int i = 0; i < event.count; i++) {
            Vector3fix_Add(&center, &event.nodes[i]->position, &center);
        }
        Vector3fixDivideScalar(&center, event.count << 12, &center);
        event.angle = _Z32GetAbsAngleDeltaBetween_021a4754P4Vec3iS0_(&leader->position, (short)leader->rotationY, &center);
        event.tag = 4;
        func_ov017_0219b33c(self, &event);
    }
    if (notify) {
        func_ov017_02198f84(self);
    }
}
