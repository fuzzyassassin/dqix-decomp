#include <globaldefs.h>
#include "Filesystem/GPC.h"
#include "Filesystem/BackgroundLoader.h"
#include "World/Object3D.h"
#include "Graphics/VRAMStaging.h"
#include "System/Cache.h"
#include "System/LoadToVRAM.h"

static inline int FxMul(int a, int b) { return (int)(((long long)a * b + 0x800) >> 12); }

struct Elem0218d50c {
    int head[2];
    unsigned int lo : 4;
    unsigned int kind : 5;
};

struct PalState0218d50c {
    char pad0[0x148];
    unsigned int palette;
};

struct CharacterColors {
    unsigned short hair_[10][2];
    unsigned short colors2_[8][2];
    unsigned short colors4_[8][4];
    unsigned short colors8_[8][8];
    unsigned short skin_[8][2];
    unsigned short edge_;
};

struct Obj0218d50c {
    void* container;
    PalState0218d50c** pairsRoot;
    SafeAllocator* allocs;
    void* pathStr;
    char pad10[0x20 - 0x10];
    int* ids;
    Object3D* ents;
    char pad28[4];
    unsigned char state;
    char pad2d[0x3c - 0x2d];
    unsigned char hairColor;
    unsigned char skinColor;
    unsigned char eyeColor;
    char pad3f;
    short s40;
    short s42;
    char pad44[0x58 - 0x44];
    int f58;
    Object3D* GetEnt(int i) { return &ents[i]; }
};

extern "C" void _Z17DelayThenSyncBit0v();
extern "C" void _Z24ResetObjectState02079a3cPv(void*);
extern "C" void _Z26CopyInternalFields0207df50P11Foo0207df50(char*);
extern "C" void _Z25RestorePairTables0207df90Pc(char*);
extern "C" void _Z24BackupPairTables0207dfacPc(char*);
extern "C" void* _Z24FindElementByKey020dedd0P17Container020dedd0i(void*, int);
extern "C" int func_ov015_0218c03c(void* self, char* buf, int i, int one);
extern "C" void func_ov015_0218c920(void* self, int zero);
extern "C" void func_ov015_0218c3a4(void* self, int v);
extern "C" void _ZN7Model3D22ApplyTexturesFromModelEPS_(void*, void*);
extern "C" int fix32_Divide(int, int);
CharacterColors* GetVariantShortTable02109928();

extern int data_0211e33c __attribute__((aligned(4)));
extern char data_ov015_02194094;
extern int data_ov015_02193d64[];
extern char data_ov015_021940f0;

// USA: func_ov015_0218d50c
extern "C" ARM int func_ov015_0218d50c(Obj0218d50c* self) {
    int off70;
    char* pairs;
    int off14;
    SafeAllocator* alloc;
    short id;
    bool changed;

    BackgroundLoader::AddLockGlobal();
    BackgroundLoader::FreeAllocationsGlobal();
    _Z17DelayThenSyncBit0v();
    id = self->GetEnt(7)->unknown_2_;
    if (self->ids[7] != id) {
        self->GetEnt(3)->unknown_2_ = -1;
        self->GetEnt(4)->unknown_2_ = -1;
    }
    id = self->GetEnt(1)->unknown_2_;
    if (self->ids[1] != id) {
        self->GetEnt(0)->unknown_2_ = -1;
    }
    changed = false;
    id = self->GetEnt(8)->unknown_2_;
    if (self->ids[8] != id ||
        self->ids[1] != (id = self->GetEnt(1)->unknown_2_)) {
        changed = true;
    }

    unsigned int size = 0;
    char* buf = (char*)&data_0211e33c;
    unsigned int room = 0x30000;
    GPCReadPair pair;
    char name[0x80];
    _Z24ResetObjectState02079a3cPv(&pair);
    if (LoadAndDecompressGPCHeaderAndInnerFileInfo(&pair.pGPCFile, pair.machine, &data_ov015_02194094,
                                                   buf, size, room, false, 0)) {
        buf += size;
        room -= size;
        for (int i = 0; i < 10; i++) {
            if (self->state != 2 && self->ids[i] == (id = self->ents[i].unknown_2_)) {
                continue;
            }
            off70 = i * 0x70;
            alloc = self->allocs;
            pairs = (char*)*self->pairsRoot;
            off14 = i * 0x14;
            ((SafeAllocator*)((char*)alloc + off14))->Reset();
            _Z26CopyInternalFields0207df50P11Foo0207df50(pairs + off70);
            Vector3fix savedPos = self->GetEnt(i)->position_;
            self->GetEnt(i)->Initialize();
            self->ents[i].position_ = savedPos;
            self->ents[i].unknown_2_ = self->ids[i];
            if (self->ids[i] < 0) {
                continue;
            }
            Elem0218d50c* elem = (Elem0218d50c*)_Z24FindElementByKey020dedd0P17Container020dedd0i(
                (char*)self->container + 0x4c, (short)self->ids[i]);
            if (elem == 0) {
                continue;
            }
            if (func_ov015_0218c03c(self, name, i, 0) == 0) {
                self->ents[i].Initialize();
                self->ents[i].unknown_2_ = -1;
                continue;
            }
            self->ents[i].Destroy();
            if (i == 0) {
                int a = FxMul(self->s40, self->s42);
                short sx = (int)(0.065f * (float)a);
                short sy = (int)(0.065f * (float)self->s40);
                self->ents[i].SetScale(sx, sy, sx);
                changed = true;
            } else if (!(i != 2 && i != 3 && i != 7 && i != 8 && i != 9)) {
                int sx = fix32_Divide(0x1000, FxMul(self->s40, self->s42));
                int sy = fix32_Divide(0x1000, self->s40);
                int sz = sx;
                if (!(i != 2 && i != 3 && i != 7)) {
                    sx = (int)(((long long)sx * (int)((float)self->s40 - 0.5f * (float)(self->s40 - 0x1000)) + 0x800) >> 12);
                    sy = (int)(((long long)sy * (int)((float)self->s40 - 0.5f * (float)(self->s40 - 0x1000)) + 0x800) >> 12);
                    sz = (int)(((long long)sz * (int)((float)self->s40 - 0.5f * (float)(self->s40 - 0x1000)) + 0x800) >> 12);
                }
                self->ents[i].SetScale(sx, sy, sz);
            } else if (!(i != 6 && i != 5 && i != 1)) {
                int a = FxMul(self->s40, self->s42);
                short sx = (int)(0.065f * (float)a);
                short sy = (int)(0.065f * (float)self->s40);
                self->ents[i].SetScale(sx, sy, sx);
            }
            if (i == 8 || i == 1) {
                changed = true;
                if (elem->kind == 6) {
                    self->f58 = 1;
                } else {
                    self->f58 = 0;
                }
            }
            _Z25RestorePairTables0207df90Pc(pairs + off70);
            DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buf, size, room, name);
            self->ents[i].SetModelFromFileCopy((SafeAllocator*)((char*)alloc + off14), buf, size, Model3D::TextureStagingMode_Normal);
            buf += size;
            room -= size;
            _Z24BackupPairTables0207dfacPc(pairs + off70);
            if (i == 4 && self->GetEnt(3)->pModel_ != 0) {
                _ZN7Model3D22ApplyTexturesFromModelEPS_(self->GetEnt(3)->pModel_, self->ents[i].pModel_);
            }
        }
        pair.Reset();
    }
    CharacterColors* colors = GetVariantShortTable02109928();
    unsigned int offset = ((*self->pairsRoot)->palette & 0xffff) << 3;
    if (offset != 0) {
        CleanInvalidateCacheRange(colors->hair_[self->hairColor], 4);
        CleanInvalidateCacheRange(colors->skin_[self->skinColor], 4);
        CleanInvalidateCacheRange(colors->colors8_[self->eyeColor], 0x10);
        _Z17DelayThenSyncBit0v();
        LockStagedTextureVRAMCopying();
        MemoryMapTexturePalette();
        LoadToTexturePalette(colors->hair_[self->hairColor], offset + 0x24, 4);
        LoadToTexturePalette(colors->skin_[self->skinColor], offset + 0x28, 4);
        LoadToTexturePalette(colors->colors8_[self->eyeColor], offset + 0x30, 0x10);
        MemoryUnmapTexturePalette();
        UnlockStagedTextureVRAMCopying();
    }
    for (int k = 0; data_ov015_02193d64[k] >= 0; k++) {
        func_ov015_0218c3a4(self, data_ov015_02193d64[k]);
    }
    if (changed) {
        func_ov015_0218c920(self, 0);
    }
    self->state = 0;
    self->pathStr = &data_ov015_021940f0;
    BackgroundLoader::RemoveLockGlobal();
    int result = 1;
    pair.Reset();
    ZeroDestroyGPCPointer(&pair.pGPCFile);
    return result;
}
