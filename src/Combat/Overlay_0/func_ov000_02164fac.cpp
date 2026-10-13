#include <globaldefs.h>
extern unsigned char data_0211e33c[0x30000] __attribute__((aligned(4)));
#include "std_library_functions.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "Filesystem/GPC.h"
#include "GameState/GameState.h"

struct StreamHeader;
struct Foo0207df50;
struct Obj02061bd8;
struct Struct_203dafc;
struct State0207dfc8;

extern "C" GameResources* func_ov017_0218b5b0();
extern "C" void* func_0202ae18(void);
extern "C" void func_02012de8(void);
void* GetData02108e10(void);
extern "C" void func_02079cf8(void* obj, void* a1, void* a2);
extern "C" void _Z24RunOverlayScript0216d1c4iP12StreamHeaderiPi(int, StreamHeader*, int, int*);
int CheckField0NonZero(int* obj);
extern "C" void _Z21BlankFunction020d84f4v(void);
extern "C" void* _Z24ResetObjectState02079a3cPv(void* obj);
int TestBitAt0x34(unsigned char* obj, unsigned int index);
int CheckField0x56bLowNibble(Obj02061bd8* obj);
extern "C" void _Z26CopyInternalFields0207df50P11Foo0207df50(Foo0207df50* p);
extern "C" void _Z25RestorePairTables0207df90Pc(char* obj);
extern "C" void _Z24BackupPairTables0207dfacPc(char* obj);
extern "C" void _Z25FormatEffectStats02072c9ciPc(int combatantId, char* buf);
void ClearEightWords(Struct_203dafc* obj);
extern "C" void func_02049c88(void* obj, void* state);
void SetPtrFieldIfNonNull0x13c(void*, int);
struct CombatantData02164fac;
CombatantData02164fac* GetFieldAt0x150(unsigned char* obj);
extern "C" void func_ov000_02166a94(void* work);
extern "C" int _Z20GetFieldB08_0219e008Pv(void* ov);
extern "C" void _Z17CopyState0207dfc8P13State0207dfc8S0_(State0207dfc8* src, State0207dfc8* dst);

extern const char data_ov000_02183960[];
extern const char data_ov000_02183976[];
extern const char data_ov000_02183983[];
extern const char data_ov000_0218399e[];
extern const char data_ov000_021839b8[];
extern const char data_ov000_021839c0[];
extern const char data_ov000_021839da[];
extern const char data_ov000_021839e2[];
extern const char data_ov000_021839e8[];

struct ModelState02164fac { char data[0x70]; };
struct Slot70 { char data[0x70]; };
static inline SafeAllocator* GetAllocator38(GameResources* res, int i) { return &res->allocator_array_38[i]; }

struct BattleWork02164fac {
    char pad_0[4];
    int scriptOwner;
    char pad_8[0x44 - 0x8];
    SafeAllocator effectAllocator;
    SafeAllocator tableAllocator;
    char pad_6c[0x1bc - 0x6c];
    char state[0x2a0 - 0x1bc];
    unsigned char* roster;
    char pad_2a4[0x5724 - 0x2a4];
    int scriptState;
    char pad_5728[0x5c3c - 0x5728];
    ModelState02164fac models[4];
};

struct CombatantFlags02164fac {
    unsigned char male : 1;
    unsigned char rest : 7;
};

struct CombatantData02164fac {
    char pad_0[0x49c];
    CombatantFlags02164fac flags;
    char pad_49d[0x94c - 0x49d];
    int phase;
};

struct Combatant02164fac {
    Object3D object;
    char pad_ac[0xc2 - 0xac];
    unsigned char flags;
    char pad_c3[0x150 - 0xc3];
    CombatantData02164fac* data;
    unsigned char* model;
    char pad_158[0x1c4 - 0x158];
    unsigned char* info;
};

// USA: func_ov000_02164fac
extern "C" ARM void func_ov000_02164fac(BattleWork02164fac* work) {
    GPCReadPair pair;
    char name[0x50];
    ObjectArchiveLoadInfo info;
    ObjectArchiveLoadInfo info2;
    unsigned int size;
    const void* script;
    unsigned int scriptSize;
    char statsName[8];
    const void* script2;
    unsigned int scriptSize2;
    int scriptState;
    Slot70* blocks;

    GameState* game = GameState::GetInstance();
    GameResources* res = func_ov017_0218b5b0();
    int* search = (int*)func_0202ae18();
    SafeAllocator* allocator = GetAllocator38(res, 7);
    blocks = (Slot70*)res->unknown_2cc;
    allocator->Reset();
    _Z26CopyInternalFields0207df50P11Foo0207df50((Foo0207df50*)&blocks[7]);
    BackgroundLoader::AddLockGlobal();
    func_02012de8();
    void* table = GetData02108e10();
    work->tableAllocator.Reset();
    func_02079cf8(table, allocator, &work->tableAllocator);
    func_02012de8();

    if (LoadFileIntoMemory(data_ov000_02183960, data_0211e33c, &size)) {
        GetFileInNarc(data_0211e33c, data_ov000_02183976, &script, &scriptSize, 0);
        if (script != NULL) {
            func_02012de8();
            _Z24RunOverlayScript0216d1c4iP12StreamHeaderiPi(work->scriptOwner, (StreamHeader*)script, scriptSize, &work->scriptState);
        }
    }
    if (CheckField0NonZero(search)) {
        _Z21BlankFunction020d84f4v();
    }

    unsigned char* buf = data_0211e33c;
    int capacity = 0x30000;
    _Z24ResetObjectState02079a3cPv(&pair);
    const char* path = data_ov000_02183983;
    if (LoadAndDecompressGPCHeaderAndInnerFileInfo(&pair.pGPCFile, pair.machine,
            path, buf, size, capacity, false, 0)) {
        buf += size;
        capacity -= size;

        for (int i = 0; i < 4; i++) {
            if (!TestBitAt0x34(work->roster, (unsigned char)i)) {
                continue;
            }
            Combatant02164fac* c = (Combatant02164fac*)GetCombatantWithFlag0x100(game, i);
            unsigned char* model;
            if (c == NULL || (model = c->model) == NULL) {
                continue;
            }

            SafeAllocator* alloc;
            func_02012de8();
            if (CheckField0x56bLowNibble((Obj02061bd8*)c)) {
                c->object.Destroy();
                if (c->info != NULL) {
                    sprintf(name, data_ov000_0218399e, c->info[0x11]);
                }
                alloc = (SafeAllocator*)(model + 4);
                alloc->Reset();
                _Z26CopyInternalFields0207df50P11Foo0207df50((Foo0207df50*)(model + 0xcc));
                _Z25RestorePairTables0207df90Pc((char*)(model + 0xcc));
                LoadFileIntoMemory(name, data_0211e33c, &size);
                buf = data_0211e33c;
            } else {
                _Z25FormatEffectStats02072c9ciPc(i, statsName);
                if (c->data->flags.male == 1) {
                    statsName[0] = 'w';
                }
                sprintf(name, data_ov000_021839b8, statsName);
                alloc = (SafeAllocator*)(model + 0x52c);
                DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buf, size, capacity, name);
            }

            if (size != 0) {
                c->object.RemoveAllAnimationPackages();
                ((SafeAllocator*)(model + 0x52c))->Reset();
                ClearEightWords((Struct_203dafc*)&info);
                info.allocator = alloc;
                info.unk_10 = 1;
                info.packageID = 0;
                info.unk_8 = size;
                info.fileData = buf;
                c->object.LoadFromCCHROrCMOTArchive(&info, NULL);
            }

            func_02049c88(c, &work->models[i]);
            func_02012de8();
            if (CheckField0x56bLowNibble((Obj02061bd8*)c)) {
                _Z24BackupPairTables0207dfacPc((char*)(model + 0xcc));
                if (c->info != NULL) {
                    sprintf(name, data_ov000_021839c0, c->info[0x11]);
                }
                LoadFileIntoMemory(name, data_0211e33c, &size);
                buf = data_0211e33c;
            } else {
                statsName[0] = 'm';
                sprintf(name, data_ov000_021839da, statsName);
                DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buf, size, capacity, name);
            }

            if (size != 0) {
                c->object.RemoveAnimationPackageByID(1);
                ((SafeAllocator*)(model + 0x540))->Reset();
                ClearEightWords((Struct_203dafc*)&info2);
                info2.unk_10 = 1;
                info2.packageID = 1;
                info2.allocator = (SafeAllocator*)(model + 0x540);
                info2.unk_8 = size;
                info2.fileData = buf;
                c->object.LoadFromCCHROrCMOTArchive(&info2, NULL);
                if (FindFilesInNarcBySubstring(buf, data_ov000_021839e2, &script2, &scriptSize2, 1)) {
                    _Z24RunOverlayScript0216d1c4iP12StreamHeaderiPi((int)(model + 0x540), (StreamHeader*)script2, scriptSize2, &scriptState);
                    SetPtrFieldIfNonNull0x13c(c, scriptState);
                }
            }

            c->flags |= 0x20;
            c->object.MaybeSetRegularAnimation(data_ov000_021839e8, 0);
            if (CheckField0x56bLowNibble((Obj02061bd8*)c)) {
                CombatantData02164fac* data = GetFieldAt0x150((unsigned char*)c);
                if (data != NULL) {
                    data->phase = 0;
                }
            }
            if (CheckField0NonZero(search)) {
                _Z21BlankFunction020d84f4v();
            }
        }
    }

    BackgroundLoader::RemoveLockGlobal();
    func_02012de8();
    func_ov000_02166a94(work);
    unsigned int effectSize = 0x26a80;
    void* mem = allocator->Allocate(effectSize);
    if (mem != NULL) {
        work->effectAllocator.CreateTypeA(mem, effectSize);
    }
    if (_Z20GetFieldB08_0219e008Pv(res) == 0) {
        _Z17CopyState0207dfc8P13State0207dfc8S0_((State0207dfc8*)res->unknown_2cc, (State0207dfc8*)work->state);
    } else {
        _Z17CopyState0207dfc8P13State0207dfc8S0_((State0207dfc8*)&blocks[7], (State0207dfc8*)work->state);
    }
    pair.Reset();
    ZeroDestroyGPCPointer(&pair.pGPCFile);
}
