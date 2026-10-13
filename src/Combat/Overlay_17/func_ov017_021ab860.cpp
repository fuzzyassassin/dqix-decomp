#include <globaldefs.h>
#include "Resource/Script.h"
#include "Resource/GameResources.h"
#include "GameState/GameState.h"
#include "Filesystem/BackgroundLoader.h"
#include "Combat/Main/CopyRecord0200fbb4.h"

#if defined(jpn)
enum { kResourceHeaderOffset = 0x4fc, kResourceTailOffset = 0x4ec };
#else
enum { kResourceHeaderOffset = 0x70c, kResourceTailOffset = 0x6fc };
#endif

int GetWord0x0(int* p);
extern "C" void* func_02012fe4(void);
extern "C" void* memset(void* dst, int val, unsigned int size);
extern "C" unsigned char* func_0205ec34(void);
int TestBitInByteArray(int obj, unsigned char* bits, int index);
int IsGlobalU16InRange(GameState* gameState);
struct Obj021abb68;
void InitState28_021abb68(struct Obj021abb68* obj, unsigned char arg);
struct List02046a3c;
struct Node02046a3c;
void InsertNodeAfterHead(struct List02046a3c* list, struct Node02046a3c* node);
extern "C" int func_ov017_0219ff58(GameResources* res, int a, int b, int c);
void* GetField0x3f8Address(GameState* battleStruct);
extern "C" void VectorizedMemset(void* dst, int val, int size);
void InitAndResetHeader_0219e310(unsigned char* obj, int flag);
struct TailList020469b4;
struct TailNode020469b4;
void AppendNodeToTail(struct TailList020469b4* list, struct TailNode020469b4* node);

struct Active021ab860 {
    unsigned short zoneId;      // 0x0
    unsigned short pad2;
    unsigned short group;       // 0x4
    char pad6[2];
    int header;                 // 0x8
};

struct State021ab860 {
    int header;                 // 0x0
    unsigned short key;         // 0x4
    unsigned short group;       // 0x6
    unsigned short entryId;     // 0x8
    char pada[2];
    Vector3i vec;               // 0xc
    short field_0x18;           // 0x18
};
extern State021ab860 data_ov017_021d83b0;
extern Vector3i data_ov017_021d83bc;
extern char data_ov017_021d78c4[];
extern Script::OpcodeLookupEntry data_ov017_021d78a4[];

struct Grotto021ab860 {
    char pad0[0xc];
    int zoneId;                 // 0xc
    Vector3i entrance;          // 0x10
};

struct Entry3f8_021ab860 {
    unsigned short entryId;     // 0x0
    char pad2[2];
    unsigned char b4;           // 0x4
    char pad5[2];
    unsigned char b7;           // 0x7
    unsigned char b8;           // 0x8
    unsigned char b9;           // 0x9
    char pada;
    signed char bb;             // 0xb
    unsigned char bc;           // 0xc
    char padd[3];
    Vector3i vec;               // 0x10
    short h1c;                  // 0x1c
    short h1e;                  // 0x1e
    int w20, w24, w28, w2c;     // 0x20
    char pad30[0x6c - 0x30];
    short h6c;                  // 0x6c
    char pad6e[2];
};

// USA: func_ov017_021ab860
extern "C" ARM int func_ov017_021ab860(int arg0, unsigned char arg1) {
    GameState* gs = GameState::GetInstance();
    GetWord0x0((int*)gs);
    data_ov017_021d83b0.header = ((Active021ab860*)func_02012fe4())->header;
    data_ov017_021d83b0.key = 0;
    data_ov017_021d83b0.group = 0;
    data_ov017_021d83b0.entryId = 0;
    memset(&data_ov017_021d83bc, 0, sizeof(Vector3i));
    data_ov017_021d83b0.field_0x18 = 0;
    unsigned char* save = func_0205ec34();
    if (TestBitInByteArray((int)save, save + 0x8c, 0x113a) != 0) {
        return 1;
    }
    if (IsGlobalU16InRange(gs) != 0) {
        int status;
        GameState* state = GameState::GetInstance();
        Active021ab860* active = (Active021ab860*)func_02012fe4();
        Grotto021ab860* grotto = (Grotto021ab860*)state->GetGrottoStruct();
        if (grotto == NULL) {
            status = 0;
        } else {
            data_ov017_021d83b0.key = active->group;
            data_ov017_021d83b0.group = active->zoneId;
            data_ov017_021d83b0.entryId = grotto->zoneId;
            data_ov017_021d83b0.field_0x18 = 0;
            data_ov017_021d83bc = grotto->entrance;
            data_ov017_021d83b0.vec.z += 0x2000;
            status = 4;
        }
        if (status == 0) {
            return 0;
        }
    } else {
        int status;
        int task;
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        loader->MaybeFreeAllocations();
        task = loader->QueueLoadFile(data_ov017_021d78c4, NULL);
        if (task < 0) {
            status = 0;
        } else {
            while (loader->GetTaskStatus(task) == 0) {
                loader->RemoveAllLocks();
            }
            if (loader->GetDetailedTaskStatus(task) != 2) {
                loader->RemoveTask(task);
                status = 0;
            } else {
                unsigned int length;
                void* data;
                loader->GetLoadedFileByID(task, &data, &length);
                Script script;
                script.Initialize();
                script.SetOpcodeLookup(data_ov017_021d78a4);
                script.Load(data, length);
                script.Execute();
                loader->RemoveTask(task);
                status = 4;
            }
        }
        if (status == 0) {
            return 0;
        }
    }
    if (data_ov017_021d83b0.entryId != 0) {
        GameResources* res = func_ov017_0218b5b0();
        InitState28_021abb68((struct Obj021abb68*)res->unknown_ptr_array_3afc[6], arg1);
        InsertNodeAfterHead((struct List02046a3c*)res->unknown_ptr_array_36fc[0],
                            (struct Node02046a3c*)res->unknown_ptr_array_3afc[6]);
        int busy = func_ov017_0219ff58(res, 1, 0, 0);
        if (busy != 0) {
            return 3;
        }
        if (busy == 0) {
            Entry3f8_021ab860* e = (Entry3f8_021ab860*)GetField0x3f8Address(gs);
            VectorizedMemset(e, 0, sizeof(Entry3f8_021ab860));
            e->b4 = 1;
            e->b8 = 1;
            e->b9 = 1;
            e->bb = -1;
            e->w20 = -1;
            e->w24 = -1;
            e->w28 = -1;
            e->w2c = -1;
            e->h1e = -1;
            e->bc = 0;
            e->h6c = -1;
            e->entryId = data_ov017_021d83b0.entryId;
            e->vec = data_ov017_021d83bc;
            e->h1c = data_ov017_021d83b0.field_0x18;
            e->b7 = 1;
            _Z28CallFunc0200fbb4AtField0x3f8Pv(gs, e);
        }
        struct TailList020469b4* tail;
        unsigned char* header = (unsigned char*)res->unknown_ptr_array_36fc[4];
        tail = (struct TailList020469b4*)res->unknown_ptr_array_36fc[0];
        InitAndResetHeader_0219e310(header, 0);
        AppendNodeToTail(tail, (struct TailNode020469b4*)header);
        *(short*)((unsigned char*)res + 0x44ae) = 0;
        *(short*)((unsigned char*)res + 0x44b0) = 0;
        return 3;
    }
    return 0;
}
