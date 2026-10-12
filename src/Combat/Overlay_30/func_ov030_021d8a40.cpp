#include <globaldefs.h>
#include "Memory/SafeAllocator.h"

void* AllocateFromAllocatorUnion(AllocatorUnion* alloc, unsigned int size);
extern "C" void func_0200ee94(void* array, int count, int size, void* ctor, void* dtor);
void* ResetNameTableThenNotify(void* obj);
void* NotifyThenResetNameTable(void* obj);
extern "C" void func_ov030_021d9340(unsigned char* self);
extern "C" void _Z17EmptyStub02012de4v(AllocatorUnion* alloc);
extern "C" void* _Z29ResetHeaderAndReturn_021d9250Pv(void* p);
extern "C" void* _Z29ResetHeaderAndReturn_021d9264Pv(void* p);
extern "C" void* _Z29ResetHeaderAndReturn_021d9278Pv(void* p);
extern "C" void* _Z29ResetHeaderAndReturn_021d928cPv(void* p);
extern "C" void* _Z29ResetHeaderAndReturn_021d92a0Pv(void* p);
extern "C" void* _Z29ResetHeaderAndReturn_021d92b4Pv(void* p);
extern "C" void* _Z29ResetHeaderAndReturn_021d92c8Pv(void* p);
extern "C" void* _Z29ResetHeaderAndReturn_021d92dcPv(void* p);

enum { kSceneDataSize = 0x36c0 };

struct SceneAllocGroup {
    int unk0;
    SafeAllocator rows[10];       // 0x004
    unsigned char unkcc[0x52c - 0xcc];
    SafeAllocator a52c;           // 0x52c
    SafeAllocator a540;           // 0x540
    SafeAllocator a554;           // 0x554
    unsigned char unk568[0x5d8 - 0x568];
    SafeAllocator a5d8;           // 0x5d8
};

struct BattleScene {
    unsigned char unk0[0x38];
    SafeAllocator allocs[33];     // 0x0038
    unsigned char unk2cc[0x113c - 0x2cc];
    SafeAllocator a113c;          // 0x113c
    unsigned char unk1150[0x11c0 - 0x1150];
    SafeAllocator a11c0;          // 0x11c0
    unsigned char unk11d4[0x1244 - 0x11d4];
    SafeAllocator a1244;          // 0x1244
    unsigned char unk1258[0x12c8 - 0x1258];
    SceneAllocGroup groups[4];    // 0x12c8
    unsigned char unk2a78[0x2b0c - 0x2a78];
    SafeAllocator a2b0c;          // 0x2b0c
    unsigned char unk2b20[0x2b90 - 0x2b20];
    unsigned char nameTables[0x12][0x88]; // 0x2b90
    unsigned char nameTable3520[0x88];    // 0x3520
    unsigned char nameTable35a8[0x88];    // 0x35a8
    unsigned char unk3630[0x36c8 - 0x3630];
    void* p36c8;
    void* p36cc;
    void* p36d0;
    void* unk36d4;
    void* p36d8;
    void* unk36dc[8];
    void* p36fc[16];              // 0x36fc
    unsigned char entries373c[0xc][0x48]; // 0x373c
    unsigned char entries3a9c[4][0x18];   // 0x3a9c
    void* p3afc[51];              // 0x3afc
    unsigned char entries3bc8[3][0x14];   // 0x3bc8
    unsigned char entries3c04[4][0x28];   // 0x3c04
    void* p3ca4;
    void* p3ca8;
    void* p3cac;
    void* p3cb0;
    unsigned char unk3cb4[0x4088 - 0x3cb4];
    void* p4088;
    void* p408c;
    void* p4090;
    unsigned char unk4094[0x41c4 - 0x4094];
    void* p41c4;
    unsigned char unk41c8[0x4328 - 0x41c8];
    void* p4328;
    unsigned char unk432c[0x441c - 0x432c];
    void* p441c;
    unsigned char unk4420[0x44c4 - 0x4420];
    void* p44c4;
};

// USA: func_ov030_021d8a40
extern "C" ARM BattleScene* func_ov030_021d8a40(AllocatorUnion* alloc, unsigned char** dataOut) {
    *dataOut = (unsigned char*)AllocateFromAllocatorUnion(alloc, kSceneDataSize);
    if (*dataOut == NULL) {
        return NULL;
    }

    BattleScene* scene = (BattleScene*)AllocateFromAllocatorUnion(alloc, sizeof(BattleScene));
    if (scene != NULL) {
        unsigned char* d = *dataOut;
        void *q36c8, *q36cc, *q36d0, *q36d8, *q36fc, *q3700, *q3704, *q3708;
        void *q370c, *q3710, *q3714, *q3718, *q371c, *q3720, *q3724, *q3728;
        void *q372c, *q3730, *q3734, *q3738, *q3afc, *q3b00, *q3b04, *q3b08;
        void *q3b0c, *q3b10, *q3b14, *q3b18, *q3b1c, *q3b20, *q3b24, *q3b28;
        void *q3b2c, *q3b30, *q3b34, *q3b38, *q3b3c, *q3b40, *q3b44, *q3b48;
        void *q3b4c, *q3b50, *q3b54, *q3b58, *q3b5c, *q3b60, *q3b64, *q3b68;
        void *q3b6c, *q3b70, *q3b74, *q3b78, *q3b7c, *q3b80, *q3b84, *q3b88;
        void *q3b8c, *q3b90, *q3b94, *q3b98, *q3b9c, *q3ba0, *q3ba4, *q3ba8;
        void *q3bac, *q3bb0, *q3bb4, *q3bb8, *q3bbc, *q3bc0, *q3bc4;
        void *q3ca8, *q3cac, *q3cb0, *q4088, *q408c, *q4090, *q41c4, *q4328;
        void *q441c, *q44c4, *q3ca4;
        q3ca4 = d + 0x3674;
        q44c4 = d + 0x3571;
        q441c = d + 0x3560;
        q4328 = d + 0x332c;
        q41c4 = d + 0x32d8;
        q4090 = d + 0x313c;
        q408c = d + 0x313a;
        q4088 = d + 0x3138;
        q3cb0 = d + 0x307c;
        q3cac = d + 0x307a;
        q3ca8 = d + 0x3078;
        q3bc4 = d + 0x304c;
        q3bc0 = d + 0x2fe0;
        q3bbc = d + 0x2fcc;
        q3bb8 = d + 0x2fc0;
        q3bb4 = d + 0x2fb4;
        q3bb0 = d + 0x2f14;
        q3bac = d + 0x2ef8;
        q3ba8 = d + 0x2ee8;
        q3ba4 = d + 0x2ebc;
        q3ba0 = d + 0x2eb0;
        q3b9c = d + 0x2e60;
        q3b98 = d + 0x2e3c;
        q3b94 = d + 0x2bb4;
        q3b90 = d + 0x2b6c;
        q3b8c = d + 0x2b18;
        q3b88 = d + 0x2b04;
        q3b84 = d + 0x2aac;
        q3b80 = d + 0x2a98;
        q3b7c = d + 0x2808;
        q3b78 = d + 0x27f8;
        q3b74 = d + 0x27e8;
        q3b70 = d + 0x27bc;
        q3b6c = d + 0x274c;
        q3b68 = d + 0x24d8;
        q3b64 = d + 0x24c8;
        q3b60 = d + 0x24b4;
        q3b5c = d + 0x23b0;
        q3b58 = d + 0x23a4;
        q3b54 = d + 0x2380;
        q3b50 = d + 0x2360;
        q3b4c = d + 0x2310;
        q3b48 = d + 0x22b4;
        q3b44 = d + 0x2268;
        q3b40 = d + 0x222c;
        q3b3c = d + 0x216c;
        q3b38 = d + 0x2144;
        q3b34 = d + 0x2134;
        q3b30 = d + 0x1ea8;
        q3b2c = d + 0x1e94;
        q3b28 = d + 0x1e54;
        q3b24 = d + 0x1e14;
        q3b20 = d + 0x1b90;
        q3b1c = d + 0x1b6c;
        q3b18 = d + 0x1b40;
        q3b14 = d + 0x1b18;
        q3b10 = d + 0x1af8;
        q3b0c = d + 0x1a90;
        q3b08 = d + 0x1a80;
        q3b04 = d + 0x19c8;
        q3b00 = d + 0x19a0;
        q3afc = d + 0x1934;
        q3738 = d + 0x1910;
        q3734 = d + 0x1748;
        q3730 = d + 0x1720;
        q372c = d + 0x16fc;
        q3728 = d + 0x16d4;
        q3724 = d + 0x16c8;
        q3720 = d + 0x1668;
        q371c = d + 0x1638;
        q3718 = d + 0xf6c;
        q3714 = d + 0xf60;
        q3710 = d + 0xe24;
        q370c = d + 0xdf8;
        q3708 = d + 0xdd4;
        q3704 = d + 0xdcc;
        q3700 = d + 0xdc4;
        q36fc = d + 0xdbc;
        q36d8 = d + 0xd9c;
        q36d0 = d + 0x16c;
        q36cc = d + 0xc0;
        q36c8 = d + 0x14;

        SafeAllocator* a = scene->allocs;
        do {
            a->ResetAllocatorPointer();
            a++;
        } while (a < scene->allocs + 33);
        scene->a113c.ResetAllocatorPointer();
        scene->a11c0.ResetAllocatorPointer();
        scene->a1244.ResetAllocatorPointer();
        SafeAllocator* row;
        SceneAllocGroup* g = scene->groups;
        do {
            row = g->rows;
            do {
                row->ResetAllocatorPointer();
                row++;
            } while (row < g->rows + 10);
            g->a52c.ResetAllocatorPointer();
            g->a540.ResetAllocatorPointer();
            g->a554.ResetAllocatorPointer();
            g->a5d8.ResetAllocatorPointer();
            g++;
        } while (g < scene->groups + 4);
        scene->a2b0c.ResetAllocatorPointer();
        func_0200ee94(scene->nameTables, 0x12, 0x88, (void*)ResetNameTableThenNotify, (void*)NotifyThenResetNameTable);
        ResetNameTableThenNotify(scene->nameTable3520);
        ResetNameTableThenNotify(scene->nameTable35a8);

        scene->p36c8 = q36c8;
        scene->p36cc = q36cc;
        scene->p36d0 = q36d0;
        scene->p36d8 = q36d8;
        scene->p36fc[0] = q36fc;
        scene->p36fc[1] = q3700;
        scene->p36fc[2] = q3704;
        scene->p36fc[3] = q3708;
        scene->p36fc[4] = q370c;
        scene->p36fc[5] = q3710;
        scene->p36fc[6] = q3714;
        scene->p36fc[7] = q3718;
        scene->p36fc[8] = q371c;
        scene->p36fc[9] = q3720;
        scene->p36fc[10] = q3724;
        scene->p36fc[11] = q3728;
        scene->p36fc[12] = q372c;
        scene->p36fc[13] = q3730;
        scene->p36fc[14] = q3734;
        scene->p36fc[15] = q3738;
        func_0200ee94(scene->entries373c, 0xc, 0x48, (void*)_Z29ResetHeaderAndReturn_021d9250Pv, (void*)_Z29ResetHeaderAndReturn_021d9264Pv);
        func_0200ee94(scene->entries3a9c, 4, 0x18, (void*)_Z29ResetHeaderAndReturn_021d9278Pv, (void*)_Z29ResetHeaderAndReturn_021d928cPv);

        scene->p3afc[0] = q3afc;
        scene->p3afc[1] = q3b00;
        scene->p3afc[2] = q3b04;
        scene->p3afc[3] = q3b08;
        scene->p3afc[4] = q3b0c;
        scene->p3afc[5] = q3b10;
        scene->p3afc[6] = q3b14;
        scene->p3afc[7] = q3b18;
        scene->p3afc[8] = q3b1c;
        scene->p3afc[9] = q3b20;
        scene->p3afc[10] = q3b24;
        scene->p3afc[11] = q3b28;
        scene->p3afc[12] = q3b2c;
        scene->p3afc[13] = q3b30;
        scene->p3afc[14] = q3b34;
        scene->p3afc[15] = q3b38;
        scene->p3afc[16] = q3b3c;
        scene->p3afc[17] = q3b40;
        scene->p3afc[18] = q3b44;
        scene->p3afc[19] = q3b48;
        scene->p3afc[20] = q3b4c;
        scene->p3afc[21] = q3b50;
        scene->p3afc[22] = q3b54;
        scene->p3afc[23] = q3b58;
        scene->p3afc[24] = q3b5c;
        scene->p3afc[25] = q3b60;
        scene->p3afc[26] = q3b64;
        scene->p3afc[27] = q3b68;
        scene->p3afc[28] = q3b6c;
        scene->p3afc[29] = q3b70;
        scene->p3afc[30] = q3b74;
        scene->p3afc[31] = q3b78;
        scene->p3afc[32] = q3b7c;
        scene->p3afc[33] = q3b80;
        scene->p3afc[34] = q3b84;
        scene->p3afc[35] = q3b88;
        scene->p3afc[36] = q3b8c;
        scene->p3afc[37] = q3b90;
        scene->p3afc[38] = q3b94;
        scene->p3afc[39] = q3b98;
        scene->p3afc[40] = q3b9c;
        scene->p3afc[41] = q3ba0;
        scene->p3afc[42] = q3ba4;
        scene->p3afc[43] = q3ba8;
        scene->p3afc[44] = q3bac;
        scene->p3afc[45] = q3bb0;
        scene->p3afc[46] = q3bb4;
        scene->p3afc[47] = q3bb8;
        scene->p3afc[48] = q3bbc;
        scene->p3afc[49] = q3bc0;
        scene->p3afc[50] = q3bc4;
        func_0200ee94(scene->entries3bc8, 3, 0x14, (void*)_Z29ResetHeaderAndReturn_021d92a0Pv, (void*)_Z29ResetHeaderAndReturn_021d92b4Pv);
        func_0200ee94(scene->entries3c04, 4, 0x28, (void*)_Z29ResetHeaderAndReturn_021d92c8Pv, (void*)_Z29ResetHeaderAndReturn_021d92dcPv);

        scene->p3ca4 = q3ca4;
        scene->p3ca8 = q3ca8;
        scene->p3cac = q3cac;
        scene->p3cb0 = q3cb0;
        scene->p4088 = q4088;
        scene->p408c = q408c;
        scene->p4090 = q4090;
        scene->p41c4 = q41c4;
        scene->p4328 = q4328;
        scene->p441c = q441c;
        scene->p44c4 = q44c4;
    }

    func_ov030_021d9340((unsigned char*)scene);
    _Z17EmptyStub02012de4v(alloc);
    return scene;
}
