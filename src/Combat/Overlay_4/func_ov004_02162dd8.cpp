#include <globaldefs.h>

#include "Combat/Main/BattleList.h"
#include "Combat/ResourceScriptEntry.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "GameState/GameState.h"
#include "Memory/SafeAllocator.h"
#include "std_library_functions.h"

struct StreamHeader;
struct MapAllocatorNode { int field0; SafeAllocator allocator; };

struct Slot02162dd8 {
    ResourceScriptPackedTriple t[4];
    int pad[2];
};

struct Loader02162dd8 {
    unsigned char running;
    char pad1[3];
    unsigned char active;
    char pad5[0xf];
    Slot02162dd8* entries;
};

extern Loader02162dd8 data_ov004_021707e8;
extern int data_ov004_02170854[];
extern char data_ov004_0217052d[];
extern unsigned char data_0211e33c[0x30000];

unsigned char CopyOutRegion0x571d_020114ec(char* obj, void* dst);
extern "C" MapAllocatorNode* func_ov011_021845f8(void*, int);
int GetFieldAt0x150_02053c6c(unsigned char* obj);
int InitAndRunScript0208274c(void* ctx, StreamHeader* script, int size, int arg3);

static inline Slot02162dd8* GetSlot(int vocation, Slot02162dd8* slots, int member) {
    int row = member * 12;
    return &slots[row + (vocation - 1)];
}

static inline short GetLow(ResourceScriptPackedTriple* t) {
    return t->low;
}

static inline short GetMiddle(ResourceScriptPackedTriple* t) {
    return t->middle;
}

static inline short GetHigh(ResourceScriptPackedTriple* t) {
    return t->high;
}

// USA: func_ov004_02162dd8
extern "C" ARM int func_ov004_02162dd8(void* param) {
    if (data_ov004_021707e8.active == 0) {
        return 0;
    }
    data_ov004_021707e8.running = 1;
    GameState* gs = GameState::GetInstance();
    unsigned char ids[4];
    int count = CopyOutRegion0x571d_020114ec((char*)gs, ids);
    data_ov004_021707e8.entries = 0;
    data_ov004_021707e8.entries = (Slot02162dd8*)func_ov011_021845f8(param, 4)->allocator.Allocate(0x480);
    if (data_ov004_021707e8.entries != 0) {
        memset(data_ov004_021707e8.entries, 0, 0x480);
        BackgroundLoader::AddLockGlobal();
        for (int i = 0; i < count; i++) {
            for (int j = 1; j < 13; j++) {
                {
                    char path[0x20] = {0};
                    unsigned int size;
                    ResourceScriptEntry script;
                    sprintf(path, data_ov004_0217052d, data_ov004_02170854[j]);
                    if (LoadFileIntoMemory(path, &data_0211e33c, &size) != 0) {
                        GameObject* c = GetCombatantWithFlag0x100_0200ff1c(gs, ids[i]);
                        if (c != 0) {
                            unsigned char* f = (unsigned char*)GetFieldAt0x150_02053c6c((unsigned char*)c);
                            if (f != 0) {
                                InitAndRunScript0208274c(&script, (StreamHeader*)&data_0211e33c, size, *(unsigned short*)(f + data_ov004_02170854[j] * 2 + 0x16c));
                                Slot02162dd8* slot = GetSlot(data_ov004_02170854[j], data_ov004_021707e8.entries, ids[i]);
                                slot->t[0].low = GetLow(&script.initial.value8);
                                slot->t[0].middle = GetMiddle(&script.initial.value8) & 0x3ff;
                                slot->t[0].high = GetHigh(&script.initial.value8) & 0x3ff;
                                slot->t[1].low = GetLow(&script.initial.valueC);
                                slot->t[1].middle = GetMiddle(&script.initial.valueC) & 0x3ff;
                                slot->t[1].high = GetHigh(&script.initial.valueC) & 0x3ff;
                                slot->t[2].low = GetLow(&script.initial.value10);
                                slot->t[2].middle = GetMiddle(&script.initial.value10) & 0x3ff;
                                slot->t[2].high = GetHigh(&script.initial.value10) & 0x3ff;
                                slot->t[3].low = GetMiddle(&script.initial.valueC);
                            }
                        }
                    }
                }
            }
        }
        BackgroundLoader::RemoveLockGlobal();
    }
    data_ov004_021707e8.active = 0;
    data_ov004_021707e8.running = 0;
    return 0;
}
