#include <globaldefs.h>
#include "GameState/GameState.h"
#include "Filesystem/GPC.h"
#include "Filesystem/BackgroundLoader.h"

struct BinarySearchByComparatorStruct;
struct ResourceEntry021a28a8 {
    char field_0[0x44];
    char ids[0x2b4];
    char monsters[0xc];
    char nodes[0xc];
};
struct ResourceInfo021a28a8 { int field_0; int filename; };
struct ResourceObject021a28a8 { Object3D object; int field_ac; };
struct ResourceArena021a28a8 {
    char field_0[0x113c];
    SafeAllocator allocator;
    char pairTables[0x20];
};
extern "C" void _Z29ClearSlotsAndProcess_021a27e8Pv(void*);
extern "C" ResourceEntry021a28a8* _Z28FindEntryByCurrentId02027cb0v();
extern "C" int _Z16GetCount0209c0ecPc(char*);
extern "C" void _Z25RestorePairTables0207df90Pc(char*);
extern "C" void _Z24BackupPairTables0207dfacPc(char*);
int GetCheckedHalfword(void*, int);
extern "C" ResourceInfo021a28a8* _Z28SearchWithComparator0206f4f0P30BinarySearchByComparatorStructi(BinarySearchByComparatorStruct*, int);
void* FindNodeBySignedId(void*, int);
bool FindFilesInNarcBySubstring(const void*, const char*, const void**, unsigned int*, unsigned int);
void* DecompressLZ77FileIntoAllocatedSpace(SafeAllocator&, const void*, unsigned int&);
void InsertShortIntoTable021098f4(unsigned short);
void ResetFieldAc(void*);
void RegisterCombatantSlot(GameState*, int, GameObject*);
extern "C" void func_ov017_021a2b1c(void*);
extern char data_ov017_021d7668[];
extern char data_0211e33c[] __attribute__((aligned(4)));
extern char data_ov017_021d7680[];
extern char data_ov017_021d7689[];

// USA: func_ov017_021a28a8
extern "C" ARM void func_ov017_021a28a8(ResourceArena021a28a8* arena) {
    GameState* state = GameState::GetInstance();
    SafeAllocator* allocator = &arena->allocator;
    char* tables = arena->pairTables;
    _Z29ClearSlotsAndProcess_021a27e8Pv(arena);
    ResourceEntry021a28a8* area = _Z28FindEntryByCurrentId02027cb0v();
    if (!area) return;
    ResourceObject021a28a8* objects = (ResourceObject021a28a8*)allocator->Allocate(_Z16GetCount0209c0ecPc(area->ids) * 0xb0);
    if (!objects) return;
    _Z25RestorePairTables0207df90Pc(tables);
    BackgroundLoader::AddLockGlobal();
    BackgroundLoader::FreeAllocationsGlobal();
    GPCReadPair archive;
    GPCReadPair* pair = &archive;
    ZeroInitGPCPointer(&archive.pGPCFile);
    pair->ZeroInitializeMachine();
    unsigned int headerLength;
    if (LoadAndDecompressGPCHeaderAndInnerFileInfo(&archive.pGPCFile, archive.machine, data_ov017_021d7668, data_0211e33c, headerLength, 0x30000, false, 0)) {
        unsigned int start = headerLength;
        unsigned int available = 0x30000 - start;
        for (int i = 0; i < _Z16GetCount0209c0ecPc(area->ids); ++i) {
            int id = GetCheckedHalfword(area->ids, i);
            ResourceInfo021a28a8* info = _Z28SearchWithComparator0206f4f0P30BinarySearchByComparatorStructi((BinarySearchByComparatorStruct*)area->monsters, (short)id);
            void* node = FindNodeBySignedId(area->nodes, (short)id);
            if (info && node) {
                char filename[16];
                sprintf(filename, data_ov017_021d7680, info->filename);
                unsigned int archiveLength = 0;
                if (DecompressFileFromGPCByName(archive.pGPCFile, archive.machine, data_0211e33c + start, archiveLength, available, filename)) {
                    const void* file;
                    unsigned int fileLength;
                    if (FindFilesInNarcBySubstring(data_0211e33c + start, data_ov017_021d7689, &file, &fileLength, 1)) {
                        unsigned int length;
                        void* decompressed = DecompressLZ77FileIntoAllocatedSpace(*allocator, file, length);
                        if (!decompressed) {
                            InsertShortIntoTable021098f4(3);
                        } else {
                            ResetFieldAc(&objects[i]);
                            objects[i].object.unknown_2_ = id;
                            ObjectArchiveLoadInfo load;
                            load.fileData = decompressed;
                            load.unk_8 = length;
                            load.unk_0 = 0;
                            load.unk_10 = 0;
                            load.unk_14 = 0;
                            load.unk_18 = 0;
                            load.packageID = 0;
                            load.allocator = allocator;
                            if (objects[i].object.LoadFromCCHROrCMOTArchive(&load, 0)) {
                                RegisterCombatantSlot(state, i + 7, (GameObject*)&objects[i]);
                            } else InsertShortIntoTable021098f4(3);
                        }
                    }
                }
            }
        }
        archive.Reset();
    }
    BackgroundLoader::RemoveLockGlobal();
    _Z24BackupPairTables0207dfacPc(tables);
    func_ov017_021a2b1c(arena);
    archive.Reset();
    ZeroDestroyGPCPointer(&archive.pGPCFile);
}
