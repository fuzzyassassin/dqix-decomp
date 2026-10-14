#include <globaldefs.h>
#include <GameState/GameState.h>
#include "GameState/Field3b0.h"
#include <Filesystem/BackgroundLoader.h>
extern unsigned char data_0211e33c[0x30000] __attribute__((aligned(4)));
void* LoadFileIntoMemory(const char* path, void* buffer, unsigned int* outLength);
#include <Filesystem/GPC.h>
#include <Memory/SafeAllocator.h>
#include <System/Matrix.h>
#include <World/Object3D.h>
#include <std_library_functions.h>

#if defined(jpn)
struct BattleWork { char pad0[0x7902]; signed char animationState; };
#else
struct BattleWork { char pad0[0x7712]; signed char animationState; };
#endif

void ZeroInitGPCPointer(GPCFile**);
void ZeroDestroyGPCPointer(GPCFile**);
struct Struct_203dafc;
void ClearEightWords(struct Struct_203dafc* obj);
struct Obj0204a120;
extern "C" void _Z17InitState0204a120P11Obj0204a120(struct Obj0204a120* obj);
struct Owner0204a3f0;
struct Holder0204a3f0;
extern "C" void _Z28SetHolderAndMarkNode0204a3f0P13Owner0204a3f0P14Holder0204a3f0(struct Owner0204a3f0* owner, struct Holder0204a3f0* h);
extern "C" void _Z15SetName0204a440PcPKc(char* obj, const char* src);
void SetStringField0234(char* obj, const char* src);
void SetField0x3b0Value(GameState*, int);
void RegisterCombatantSlot(GameState*, int, GameObject*);
int TestBitAt0x34(unsigned char*, unsigned int);
int CountSetBitsAt0x34(unsigned char*);
extern "C" void _Z25FormatEffectStats02072c9ciPc(int, char*);
struct Fields020407b4;
void SetFields0x44(struct Fields020407b4*, int, int, int);
struct GameResources;
void SetBrightness(struct GameResources*, int, int);
void SetMainBrightness(struct GameResources*, int, int);
extern "C" {
struct GameResources* func_ov017_0218b5b0();
void func_ov000_021626a0(BattleWork*, int, int);
void func_ov000_021637fc(BattleWork*, int);
void _Z38RunFlaglearAndSetMode02167e6c_02167e6cPh(BattleWork*);
int func_02032370(int);
}

extern const char data_ov026_021dee5c[];
extern const char data_ov026_021dee77[];
extern const char data_ov026_021dee84[];
extern const char data_ov026_021dee88[];
struct LabelData { unsigned char a[4]; unsigned char b0; unsigned char b1; };
extern const LabelData data_ov026_021de6a0;
struct Table4 { int v[4]; };
struct AnimLabels { signed char letters[2]; };
extern const Table4 data_ov026_021de6e8;
extern const char data_ov026_021dee8f[];
struct RowLabels {
    char names[8][3];
    int loadTask;
    const char* order[8];
};
extern "C" RowLabels _ZZ12GetRowLabelsvE1s;
extern const char data_ov026_021dee9c[];
extern const char data_ov026_021deeb5[];

// USA: func_ov026_021dc440
extern "C" ARM void func_ov026_021dc440(SafeAllocator* allocator, BattleWork* self, void* unused, unsigned char* party, const char* animName) {
    GPCReadPair pair;
    unsigned int size;
    char name[0x50];
    GameState* game = GameState::GetInstance();
    GameResources* resources = func_ov017_0218b5b0();
    int mode = self->animationState;
    func_ov000_021626a0(self, 0x26, 1);
    func_ov000_021626a0(self, 0x27, 0);
    _Z38RunFlaglearAndSetMode02167e6c_02167e6cPh(self);
    if (mode != 5) allocator->Reset();
    BackgroundLoader::AddLockGlobal();
    BackgroundLoader::FreeAllocationsGlobal();

    GPCReadPair* rp = &pair;
    unsigned char* buffer = data_0211e33c;
    unsigned int room = 0x30000;
    ZeroInitGPCPointer(&rp->pGPCFile);
    rp->ZeroInitializeMachine();
    if (LoadAndDecompressGPCHeaderAndInnerFileInfo(&pair.pGPCFile, pair.machine, data_ov026_021dee5c, buffer, size, room, false, 0)) {
        buffer += size;
        room -= size;
        if (DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buffer, size, room, data_ov026_021dee77)) {
            Object3D* obj = (Object3D*)allocator->Allocate(0xac);
            if (obj) {
                obj->Initialize();
                ObjectArchiveLoadInfo info;
                ClearEightWords((Struct_203dafc*)&info);
                info.unk_8 = size;
                info.unk_10 = 1;
                info.allocator = allocator;
                info.fileData = buffer;
                obj->LoadFromCHRArchive(&info);
                char* holder = (char*)allocator->Allocate(0x268);
                if (holder) {
                    _Z17InitState0204a120P11Obj0204a120((Obj0204a120*)holder);
                    _Z28SetHolderAndMarkNode0204a3f0P13Owner0204a3f0P14Holder0204a3f0((Owner0204a3f0*)holder, (Holder0204a3f0*)obj);
                    _Z15SetName0204a440PcPKc(holder, data_ov026_021dee84);
                    SetStringField0234(holder, data_ov026_021dee88);
                    SetField0x3b0Value(game, (int)holder);
                    AnimLabels labels;
                    labels.letters[0] = data_ov026_021de6a0.b0;
                    labels.letters[1] = data_ov026_021de6a0.b1;
                    if (!animName) {
                        labels.letters[0] += func_02032370(3);
                        animName = (const char*)labels.letters;
                    }
                    obj->MaybeSetRegularAnimation(animName, 1);
                    Table4 table = data_ov026_021de6e8;
                    int k = 0x10a;
                    int s = table.v[CountSetBitsAt0x34(party) - 1];
                    int a = FIX32_MULTIPLY(k, s);
                    obj->SetScale(a, k, a);
                    int b = FIX32_MULTIPLY(s, s);
                    int c = FIX32_MULTIPLY(b, s);
                    SetFields0x44((Fields020407b4*)obj, 0, 0xcc, -c);
                }
            }
        }
        if (DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buffer, size, room, data_ov026_021dee8f)) {
            Object3D* obj = (Object3D*)allocator->Allocate(0xac);
            if (obj) {
                obj->Initialize();
                ObjectArchiveLoadInfo info;
                ClearEightWords((Struct_203dafc*)&info);
                info.unk_8 = size;
                info.unk_10 = 1;
                info.allocator = allocator;
                info.fileData = buffer;
                obj->LoadFromCHRArchive(&info);
                SetFields0x44((Fields020407b4*)obj, 0, 0xcc, 0);
                obj->SetScale(0x10a, 0x10a, 0x10a);
                Model3D* model = obj->pModel_;
                Object3D::TrackedBoneMatrix* bones = (Object3D::TrackedBoneMatrix*)allocator->Allocate(0x1c0);
                if (bones && model) {
                    for (int i = 0; i < 8; ++i) {
                        int index = model->GetBoneIndex(_ZZ12GetRowLabelsvE1s.order[i]);
                        bones[i].boneIndex = index;
                        obj->TrackBone(&bones[i]);
                    }
                }
                obj->EnableBoneTracking();
                RegisterCombatantSlot(game, 0xcf, (GameObject*)obj);
            }
        }
        for (int i = 0; i < 4; ++i) {
            if (TestBitAt0x34(party, (unsigned char)i)) {
                GameObject* member = GetCombatantWithFlag0x100(game, i);
                if (member) {
                    char tmp[0x14];
                    _Z25FormatEffectStats02072c9ciPc(i, tmp);
                    if (*(int*)((char*)member + 0x1c4)) {
                        sprintf(name, data_ov026_021dee9c);
                        LoadFileIntoMemory(name, data_0211e33c, &size);
                        buffer = data_0211e33c;
                    } else {
                        sprintf(name, data_ov026_021deeb5, tmp);
                        DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buffer, size, room, name);
                    }
                    if (size) {
                        ObjectArchiveLoadInfo info;
                        ClearEightWords((Struct_203dafc*)&info);
                        info.unk_10 = 1;
                        info.packageID = 3;
                        info.unk_8 = size;
                        info.allocator = allocator;
                        info.fileData = buffer;
                        member->obj3D_.LoadFromCCHROrCMOTArchive(&info, 0);
                        func_ov000_021637fc(self, i);
                    }
                }
            }
        }
        pair.Reset();
    }
    BackgroundLoader::RemoveLockGlobal();
    if (mode == 5) SetBrightness(resources, 0, 0xf);
    else SetMainBrightness(resources, 0, 0xf);
    pair.Reset();
    ZeroDestroyGPCPointer(&pair.pGPCFile);
}
