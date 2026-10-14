#include <globaldefs.h>
#include "GameState/GameState.h"

extern "C" void* func_0205ec34(void);
void* GetData02105254(void);
extern "C" void* func_02012fe4(void);

struct Bcb8Params;
void ForwardParamsToB8bc(struct Bcb8Params* s, int arg1, int arg2);

struct Obj_0201bb78 { unsigned short field0; };
int LookupBitFromValueRange0201bb78(struct Obj_0201bb78* obj, unsigned int val);

void SetElementFields0202756c(void* obj, int p1, int p2, int idx,
        unsigned char p5, unsigned char p6, unsigned short p7, unsigned char p8, int p9, int p10);

int TestBitInByteArray(int unused, unsigned char* arr, int index);
void ClampPositionToBounds0202630c(void* obj, int* pos, int margin);

extern "C" int abs(int x);
extern "C" void ColorEffect_ConfigureAlphaBlend(unsigned int* out, unsigned char a, unsigned char b, int c, int d);

extern int data_020fdc4c;

struct Elem0xa9c {
    unsigned short h0;
    unsigned char b2;
    char pad3;
    int w4;
    int w8;
};

struct Vec3i { int x, y, z; };

struct G8Obj {
    char pad[0xc];
    unsigned char lowNibble : 4;
    unsigned char highNibble : 4;
};

// USA: func_02025f28
extern "C" ARM void func_02025f28(unsigned char* obj) {
    GameState* battle = GameState::GetInstance();
    unsigned char* ctx = (unsigned char*)func_0205ec34();
    GetData02105254();
    void* g = func_02012fe4();
    unsigned short g0 = *(unsigned short*)g;
    GameObject* c1;
    int i;
    int flag2;
    void* g8 = *(void**)((char*)g + 8);
    c1 = battle->GetUnknownGameObject();
    battle->GetProtagonist();
    struct Vec3i pos0 = *(struct Vec3i*)((char*)c1 + 0x44);

    if (*(unsigned char*)(obj + 0x55c) != 0) {
        *(unsigned char*)(obj + 0x55c) = 0;
        ForwardParamsToB8bc((struct Bcb8Params*)(*(char**)(obj + 0x20) + 8), 0, 0);
    }

    flag2 = 1;
    for (i = 0; i < *(unsigned char*)(obj + 0xa99); i++) {
        if (LookupBitFromValueRange0201bb78((struct Obj_0201bb78*)g, (unsigned short)((*(struct Elem0xa9c**)(obj + 0xa9c))[i].h0 * 100)) == 0) continue;
        struct Elem0xa9c* e = &(*(struct Elem0xa9c**)(obj + 0xa9c))[i];
        int x = e->w4;
        int z = e->w8;
        if ((*(struct Elem0xa9c**)(obj + 0xa9c))[i].b2 == 1) {
            SetElementFields0202756c(obj, x + 0x7d000, z + 0x5d000, 0x18,
                (i + 0x55) & 0xff, flag2, 0xff, 0xff, 0x1000, 0x1000);
        } else if ((*(struct Elem0xa9c**)(obj + 0xa9c))[i].b2 == 2) {
            SetElementFields0202756c(obj, x + 0x7d000, z + 0x5d000, 0x17,
                (i + 0x55) & 0xff, 0, 0xff, 0xff, 0x1000, 0x1000);
        }
    }

    i = 1;
    flag2 = i;
    if (g0 == 10000 || TestBitInByteArray((int)ctx, ctx + 0x8c, 0x2b) == 0) flag2 = 0;
    int posVec[3];
    if (g0 == 10000 || g0 == 10100) {
        posVec[0] = pos0.x + 0x80000;
        posVec[2] = pos0.z + 0x60000;
    } else if (((struct G8Obj*)g8)->lowNibble == 0) {
        posVec[0] = fix32_Divide((fix32_t)(pos0.x + *(int*)((char*)g + 0x44)), (fix32_t)(0x6000)) + 0x80000;
        posVec[2] = fix32_Divide((fix32_t)(pos0.z + *(int*)((char*)g + 0x48)), (fix32_t)(0x6000)) + 0x60000;
    } else if (*(int*)((char*)g + 0x44) != 0 && *(int*)((char*)g + 0x48) != 0) {
        posVec[0] = *(int*)((char*)g + 0x44) + 0x80000;
        posVec[2] = *(int*)((char*)g + 0x48) + 0x60000;
    } else {
        i = 0;
    }

    if (flag2) {
        struct Vec3i v = *(struct Vec3i*)((char*)g + 0x2774);
        v.x += 0x80000;
        v.z += 0x60000;
        ClampPositionToBounds0202630c(obj, (int*)&v, 0x7000);
        v.x -= 0x4000;
        v.z -= 0x4000;
        SetElementFields0202756c(obj, v.x, v.z, 0x19, 0x54, 0, 0xff, 0xff, 0x1000, 0x1000);
    }

    int c = (*(unsigned int*)((char*)&data_020fdc4c + 0xc) + battle->GetEffectiveDeltaTime()) % 0x560u;
    *(unsigned int*)((char*)&data_020fdc4c + 0xc) = c;
    c = abs((c - 0x2b0) / 0x2b) * 0x4b / 100 + 5;
    if (c > 0x10) c = 0x10;
    int d = 0x10 - c;
    ColorEffect_ConfigureAlphaBlend((unsigned int*)0x04001050, 0, 3, c, d);

    ClampPositionToBounds0202630c(obj, posVec, 0x5000);
    posVec[0] -= 0x4000;
    posVec[2] -= 0x4000;

    if (i) {
        short f4 = *(short*)((char*)c1 + 4);
        unsigned char p5 = (unsigned char)(f4 + 0x44);
        unsigned short p7 = (unsigned short)(f4 + 4);
        SetElementFields0202756c(obj, posVec[0], posVec[2], 5, p5, 0, p7, 0xff, 0x1000, 0x1000);
    }
}
