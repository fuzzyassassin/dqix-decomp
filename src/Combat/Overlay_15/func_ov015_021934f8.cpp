#include <globaldefs.h>
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "Memory/SafeAllocator.h"

#include "System/Graphics.h"
static inline void GX_SetBGCharOffset(int o) { DISPCNT = (DISPCNT & ~0x7000000) | (o << 24); }
static inline void GX_SetBGScrOffset(int o) { DISPCNT = (DISPCNT & ~0x38000000) | (o << 27); }
static inline void GX_SetVisiblePlane(int p) { DISPCNT = (DISPCNT & ~0x1f00) | (p << 8); }

struct AllocatorUnion;
struct Struct020A2CF0;
struct S_02010124;
struct Foo0207df50;
struct Obj0203bdb0;
struct Obj02192600;
struct Struct0218b810;

void SetWord0x0(int*, int);
void* GetGlobal02109400();
extern "C" void _Z21BlankFunction02094b3cv();
extern "C" void _Z21BlankFunction02094b34v();
extern "C" void _Z21BlankFunction02094b38v();
extern "C" void _Z18AlwaysTrue02094b4cv();
void EncodeSignFlaggedHalfword(short*, int);
extern "C" void* func_0203bd08();
extern "C" void _Z25InitBattleContext0203bd24Pc(char*);
void LockStagedTextureVRAMCopying();
extern "C" unsigned int MapVRAMBanksToLCDC(int);
extern "C" void func_020ca458(int, void*, unsigned int);
extern "C" unsigned int DisableLCDCMappedVRAMBanks();
extern "C" unsigned int ReleaseTextureImageVRAMBanks();
extern "C" unsigned int MapVRAMBanksToTextureImage(int);
extern "C" unsigned int ReleaseTexturePaletteVRAMBanks();
extern "C" unsigned int MapVRAMBanksToTexturePalette(int);
extern "C" void _Z30SetDispcntModeAndFlags020c391ciii(int, int, int);
void SetSubBgMode(unsigned int);
extern "C" unsigned int ReleaseSubBGVRAMBanks();
extern "C" unsigned int MapVRAMBanksToSubBG(int);
extern "C" unsigned int ReleaseSubObjVRAMBanks();
extern "C" unsigned int MapVRAMBanksToSubObj(int);
void UpdateVRAMStagingVRAMBanks();
void UnlockStagedTextureVRAMCopying();
void Finish3DRendering();
extern "C" void func_020c51dc();
extern "C" void _Z25ResetMatrixStacks020c537cv();
void* AllocateAligned4(AllocatorUnion*, unsigned int);
extern "C" void _Z17SetBuffer02028ddcPv(void*);
extern "C" void _Z31SetStructFieldsFromCode02028d68i(int);
extern "C" void _Z28UploadPendingPalette02028deci(int);
extern "C" void _Z25ConfigurePairMode020bb48cji(unsigned int, int);
extern "C" void _Z41InitGlobalStateAndInstallHandlers020bb780Pvi(void*, int);
extern "C" void _Z12Init02192600P11Obj02192600(Obj02192600*);
void Set3DClearColor(int, int, int, int, int);
extern "C" void _Z22ZeroFourFields0218b810P14Struct0218b810(Struct0218b810*);
extern "C" void func_ov015_0218ba44(void*, int);
extern "C" void _Z16ZeroInit020de848Pv(void*);
extern "C" void* ExtractFileFromGP2(const char*, const char*, unsigned int*);
extern "C" void func_020dea64(void*, SafeAllocator*, void*, unsigned int, const char*, int);
extern "C" void _Z20Clear12Bytes0206efc4Pv(void*);
extern "C" void _Z28LockedLookupDispatch0206efd8PvS_(void*, void*);
extern "C" void _Z19ClearStruct020709d8Pv(void*);
extern "C" void _Z28LockedLookupDispatch020709ecPvS_(void*, void*);
extern "C" void func_0202df68(void*);
extern "C" void _Z18ResetState020a2cf0P14Struct020A2CF0(Struct020A2CF0*);
extern "C" void _Z28InitCombatController020a2010Pv(void*);
void SetField0x238False(void*);
extern "C" void _Z18SetField0x3b0ValueP9GameStatei(GameState*, int);
extern "C" void func_ov015_02192544(void*);
extern "C" void _Z27SetupContextForMode0205ea20Pvi(void*, int);
void DelayThenSyncBit0();
void RestoreDisplayMode();
extern "C" void _Z18InitFields02010124P10S_02010124(S_02010124*);
extern "C" void _Z27SetActiveDmaChannel020c3a0ci(int);
unsigned long long GetCurrentTimestamp();
extern "C" void* _Z26GetGlobalField0x1c020421a0v();
void SetField0x1e28(void*, void*);
extern "C" void _Z26CopyInternalFields0207df50P11Foo0207df50(Foo0207df50*);
extern "C" void _Z25RestorePairTables0207df90Pc(char*);
extern "C" void func_020432c4(void*);
extern "C" void _Z24BackupPairTables0207dfacPc(char*);
extern "C" void func_0204500c(void*, const char*, int, int);
extern "C" void _Z15Forward0204359cPvi(void*, int);
extern "C" void func_020439b0(void*, int);
extern "C" void func_ov015_02192700(void*);
extern "C" void _Z17EmptyStub02012de4v();
extern "C" void _Z28InitCombatSubsystems02012efcv();
int TestFlagMask(unsigned short*, int);
int TestFlag0SetAndFlag1Clear(unsigned short*, int);
extern "C" void _Z31DispatchToActiveEntries020bc028i(int);
extern "C" void func_ov015_02190e88(void*);
extern "C" void func_ov015_02191294(void*);
extern "C" void func_ov015_02191668(void*);
extern "C" void func_ov015_02190d7c(void*);
extern "C" void func_ov015_021901c8(void*);
extern "C" void _Z33CleanInvalidateOamBuffers0203bd88v();
extern "C" void _Z20ResetXYField0203aa08Pv(void*);
extern "C" void func_020bbd9c();
extern "C" float func_0200c76c(unsigned long long);
extern "C" int _Z22GetSignedField020c39c8PVt(volatile unsigned short*);
extern "C" void _Z22SyncMainSubOam0203bdb0P11Obj0203bdb0(Obj0203bdb0*);
extern "C" void _Z26FlushOrClearBuffer020290aci(int);
extern "C" void func_02094ab0(void*);

extern unsigned short data_02114e30;
extern char data_02114e20;
extern char data_02108760;
extern char* data_020f2a38;
extern char* data_020f2a30;
extern char data_ov015_02193cdc[];
extern char data_ov015_02194528[];

struct Combat015 {
    char pad0[0x3c];
    char data3c[0x4c - 0x3c];
    char data4c[0x64 - 0x4c];
    char data64[0x70 - 0x64];
    char data70[0x84 - 0x70];
    void* buf84;
    SafeAllocator alloc88;
    char pad9c[0x9c - 0x88 - sizeof(SafeAllocator)];
    SafeAllocator alloc9c;
    char padb0[0xb0 - 0x9c - sizeof(SafeAllocator)];
    SafeAllocator allocb0;
    char pad124[0x124 - 0xb0 - sizeof(SafeAllocator)];
    char data124[0x194 - 0x124];
    int state194;
    int word198;
    char pad19c[0x1a4 - 0x19c];
    int word1a4;
    char pad1a8[0x22c - 0x1a8];
    unsigned long long acc22c;
    unsigned long long time234;
    unsigned long long time23c;
    unsigned long long avg244;
    float rate24c;
    char pad250[0x268 - 0x250];
    char data268[0x52];
};

// USA: func_ov015_021934f8
extern "C" ARM void func_ov015_021934f8(Combat015* self) {
    char ctl[0x2c8];

    GameState* gs = GameState::GetInstance();
    if (gs != 0) {
        SetWord0x0((int*)gs, (int)self);
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        loader->MaybeReset();
        void* g = GetGlobal02109400();
        ((void (*)(void*, int))_Z21BlankFunction02094b3cv)(g, 10);
        ((void (*)(void*, int))_Z21BlankFunction02094b3cv)(g, 0xc);
        ((void (*)(void*, int, int, int, int))_Z21BlankFunction02094b34v)(g, 0x69, 0, 0, 0);
        ((void (*)(void*, int))_Z21BlankFunction02094b38v)(g, 0x69);
        ((void (*)(void*, int))_Z21BlankFunction02094b38v)(g, 0);
        while (((int (*)(void*))_Z18AlwaysTrue02094b4cv)(g) == 0) {
            loader->RemoveAllLocks();
        }
        EncodeSignFlaggedHalfword((short*)0x400006c, -16);
        EncodeSignFlaggedHalfword((short*)0x400106c, -16);
        void* oam = func_0203bd08();
        _Z25InitBattleContext0203bd24Pc((char*)oam);
        LockStagedTextureVRAMCopying();
        MapVRAMBanksToLCDC(0x1ff);
        func_020ca458(0, (void*)0x6800000, 0xa4000);
        DisableLCDCMappedVRAMBanks();
        ReleaseTextureImageVRAMBanks();
        MapVRAMBanksToTextureImage(0xb);
        ReleaseTexturePaletteVRAMBanks();
        MapVRAMBanksToTexturePalette(0x60);
        GX_SetBGCharOffset(0);
        GX_SetBGScrOffset(0);
        GX_SetVisiblePlane(1);
        _Z30SetDispcntModeAndFlags020c391ciii(1, 0, 1);
        SetSubBgMode(0);
        *(volatile unsigned int*)0x4001000 = (*(volatile unsigned int*)0x4001000 & ~0x1f00) | 0x1100;
        ReleaseSubBGVRAMBanks();
        MapVRAMBanksToSubBG(4);
        ReleaseSubObjVRAMBanks();
        MapVRAMBanksToSubObj(0x100);
        *(volatile unsigned int*)0x4001000 = (*(volatile unsigned int*)0x4001000 & 0xffcfffef) | 0x10;
        UpdateVRAMStagingVRAMBanks();
        UnlockStagedTextureVRAMCopying();
        EncodeSignFlaggedHalfword((short*)0x400006c, 0);
        EncodeSignFlaggedHalfword((short*)0x400106c, 0);
        *(unsigned short*)0x4000304 &= ~0x8000;
        Finish3DRendering();
        func_020c51dc();
        _Z25ResetMatrixStacks020c537cv();
        *(unsigned short*)0x400000a &= ~3;
        *(unsigned short*)0x4000008 = (*(unsigned short*)0x4000008 & ~3) | 1;
        *(unsigned short*)0x4001008 &= ~3;
        *(unsigned int*)0x4001010 = 0;
        self->buf84 = AllocateAligned4((AllocatorUnion*)&data_02114e20, 0x6000);
        _Z17SetBuffer02028ddcPv(self->buf84);
        _Z31SetStructFieldsFromCode02028d68i(4);
        _Z28UploadPendingPalette02028deci(1);
        _Z25ConfigurePairMode020bb48cji(3, 1);
        _Z41InitGlobalStateAndInstallHandlers020bb780Pvi((void*)0x8000, 1);
        _Z12Init02192600P11Obj02192600((Obj02192600*)self);
        Set3DClearColor(0x594a, 0x10, 0x7fff, 0, 0);
        _Z22ZeroFourFields0218b810P14Struct0218b810((Struct0218b810*)self->data3c);
        func_ov015_0218ba44(self->data3c, 0);
        memset(self->data268, 0, 0x52);
        self->alloc88.ResetAllocatorPointer();
        self->alloc88.CreateTypeA(AllocateAligned4((AllocatorUnion*)&data_02114e20, 0x17600), 0x17600);
        self->alloc88.Reset();
        _Z16ZeroInit020de848Pv(self->data4c);
        BackgroundLoader::AddLockGlobal();
        unsigned int outSize = 0;
        void* file = ExtractFileFromGP2(data_020f2a38, data_020f2a30, &outSize);
        if (file != 0) {
            func_020dea64(self->data4c, &self->alloc88, file, outSize, data_ov015_02193cdc, 9);
        }
        BackgroundLoader::RemoveLockGlobal();
        self->alloc9c.ResetAllocatorPointer();
        self->alloc9c.CreateTypeA(AllocateAligned4((AllocatorUnion*)&data_02114e20, 0x20000), 0x20000);
        self->alloc9c.Reset();
        _Z20Clear12Bytes0206efc4Pv(self->data64);
        _Z28LockedLookupDispatch0206efd8PvS_(self->data64, &self->alloc9c);
        self->allocb0.ResetAllocatorPointer();
        self->allocb0.CreateTypeA(AllocateAligned4((AllocatorUnion*)&data_02114e20, 0x20000), 0x20000);
        self->allocb0.Reset();
        _Z19ClearStruct020709d8Pv(self->data70);
        _Z28LockedLookupDispatch020709ecPvS_(self->data70, &self->allocb0);
        func_0202df68(ctl);
        _Z18ResetState020a2cf0P14Struct020A2CF0((Struct020A2CF0*)ctl);
        _Z28InitCombatController020a2010Pv(ctl);
        SetField0x238False(ctl);
        _Z18SetField0x3b0ValueP9GameStatei(gs, (int)ctl);
        func_ov015_02192544(self);
        _Z27SetupContextForMode0205ea20Pvi(&data_02108760, 0x65);
        DelayThenSyncBit0();
        RestoreDisplayMode();
        *(volatile unsigned int*)0x4001000 |= 0x10000;
        _Z18InitFields02010124P10S_02010124((S_02010124*)gs);
        _Z27SetActiveDmaChannel020c3a0ci(0);
        GetCurrentTimestamp();
        void* ctrl = _Z26GetGlobalField0x1c020421a0v();
        SetField0x1e28(ctrl, self->data124);
        _Z26CopyInternalFields0207df50P11Foo0207df50((Foo0207df50*)self->data124);
        _Z25RestorePairTables0207df90Pc(self->data124);
        func_020432c4(ctrl);
        _Z24BackupPairTables0207dfacPc(self->data124);
        func_0204500c(ctrl, data_ov015_02194528, 0, 0xe3);
        *((char*)ctrl + 0x195a) = 8;
        for (unsigned int i = 0; i < 0x10; i++) {
            _Z15Forward0204359cPvi(ctrl, 0x10);
            func_020439b0(ctrl, 0);
        }
        self->state194 = 0;
        self->word198 = 2;
        self->word1a4 = 0;
        func_ov015_02192700(self);
        ((void (*)(void*))_Z17EmptyStub02012de4v)(&data_02114e20);
        unsigned long long last = GetCurrentTimestamp();
        for (;;) {
            _Z28InitCombatSubsystems02012efcv();
            int quit;
            if (TestFlagMask(&data_02114e30, 4) != 0 && TestFlagMask(&data_02114e30, 8) != 0) {
                quit = 1;
            } else if (self->word1a4 == 0 && TestFlag0SetAndFlag1Clear(&data_02114e30, 2) != 0) {
                quit = 1;
            } else {
                quit = 0;
            }
            if (quit != 0) {
                _Z31DispatchToActiveEntries020bc028i(0);
                break;
            }
            if (TestFlag0SetAndFlag1Clear(&data_02114e30, 8) != 0) {
                func_ov015_02192544(self);
            }
            switch (self->state194) {
            case 0:
                func_ov015_02190e88(self);
                break;
            case 1:
                func_ov015_02191294(self);
                break;
            case 2:
                func_ov015_02191668(self);
                break;
            }
            func_ov015_02190d7c(self);
            func_ov015_021901c8(self);
            ((void (*)(void*))_Z33CleanInvalidateOamBuffers0203bd88v)(oam);
            _Z20ResetXYField0203aa08Pv(&data_02108760);
            func_020bbd9c();
            unsigned long long prev = self->time23c;
            self->time23c = (GetCurrentTimestamp() * 64000) / 33514;
            if (self->time234 < self->time23c) {
                unsigned long long d = self->time23c - self->time234;
                self->avg244 = (d + self->avg244) >> 1;
            }
            if (prev < self->time23c) {
                self->acc22c += (self->time23c - prev) / 1000;
                if (self->acc22c > 1000) {
                    self->acc22c = 0;
                    self->rate24c = 1000000.0f / func_0200c76c(self->avg244);
                }
            }
            loader->RemoveAllLocks();
            self->time234 = (GetCurrentTimestamp() * 64000) / 33514;
            if (_Z22GetSignedField020c39c8PVt((volatile unsigned short*)0x400006c) > -16) {
                DelayThenSyncBit0();
            }
            GetCurrentTimestamp();
            _Z22SyncMainSubOam0203bdb0P11Obj0203bdb0((Obj0203bdb0*)oam);
            _Z26FlushOrClearBuffer020290aci(1);
            gs->CalculateDeltaTime(((GetCurrentTimestamp() - last) * 64000) / 33514);
            last = GetCurrentTimestamp();
        }
        ((void (*)(void*, int))_Z21BlankFunction02094b38v)(g, 0x69);
        func_02094ab0(g);
        _Z27SetupContextForMode0205ea20Pvi(&data_02108760, 0x64);
        _Z28InitCombatController020a2010Pv(ctl);
        _Z18ResetState020a2cf0P14Struct020A2CF0((Struct020A2CF0*)ctl);
        func_0202df68(ctl);
    }
}
