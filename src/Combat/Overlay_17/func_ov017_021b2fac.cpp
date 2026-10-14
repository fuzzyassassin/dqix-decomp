#include <globaldefs.h>

struct Task021b2fac {
    char pad0[1];
    unsigned char done;
    char pad2[6];
    short combatantId;
    signed char state;
    unsigned char flagsB;
    char padC[4];
    int taskId;
};

struct Stats021b2fac {
    char pad0[0x56b];
    unsigned char kind : 4;
    unsigned char : 4;
};

struct Alloc021b2fac {
    char pad0[0xcc];
    char tables[1];
};

struct Combatant021b2fac {
    char pad0[4];
    short field4;
    char pad6[0x9c - 6];
    unsigned short field9c;
    char padA0[0x150 - 0x9e];
    struct Stats021b2fac* stats;
    struct Alloc021b2fac* alloc;
    char pad158[0x1c4 - 0x158];
    unsigned char* entry;
};

struct LoadInfo021b2fac {
    int f0;
    void* data;
    int size;
    void* alloc;
    int pad[4];
};

extern "C" void* _ZN9GameState11GetInstanceEv(void);
extern "C" void* _ZN16BackgroundLoader11GetInstanceEv(void);
extern "C" void* func_ov017_0218b5b0(void);
extern "C" Combatant021b2fac* _Z25GetCombatantWithFlag0x100P9GameStatei(void* gs, int id);
extern "C" void _Z30ResetEntriesAndNotify_021b33d8Pv(void* p);
extern "C" void _ZN8Object3D7DestroyEv(void* o);
extern "C" void _ZN13SafeAllocator5ResetEv(void* a);
extern "C" void* _ZN13SafeAllocator8AllocateEj(void* a, unsigned int n);
extern "C" int _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(void* l, const char* a, const char* b, void* alloc);
extern "C" int _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(void* l, const char* a, void* alloc);
extern "C" int _ZN16BackgroundLoader13GetTaskStatusEi(void* l, int id);
extern "C" int _ZN16BackgroundLoader21GetDetailedTaskStatusEi(void* l, int id);
extern "C" void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(void* l, int id, void** out, unsigned int* size);
extern "C" void _ZN16BackgroundLoader10RemoveTaskEi(void* l, int id);
extern "C" int func_ov017_021b3444(struct Task021b2fac* t);
extern "C" int func_ov017_021b38c8(struct Task021b2fac* t);
extern "C" void func_02083e28(void* p, int v);
extern "C" void _ZN8Object3D10EnableFlagEi(void* o, int mask);
extern "C" void _ZN8Object3D11DisableFlagEi(void* o, int mask);
extern "C" void _ZN8Object3D10MakeHiddenEv(void* o);
extern "C" int func_ov017_021b3560(struct Task021b2fac* t);
extern "C" void func_ov017_021b3678(struct Task021b2fac* t);
extern "C" int func_ov017_021b3780(struct Task021b2fac* t);
extern "C" int func_ov017_021b3e14(struct Task021b2fac* t);
extern "C" void _Z32CallHelperIfCheckPasses_0218fcf8iii(void* a, int b, int c);
extern "C" void _Z19ResetStruct020d3c08Pc(char* p);
extern "C" void _Z36InitHandlerArrayAndRunScript020d3c84P24HandlerSlotArray020d3c84P12StreamHeaderi(char* p, void* hdr, unsigned int n);
extern "C" void* _Z15FindEntryByKindP32FindEntryByKindContainer020d3d90i(char* c, int kind);
extern "C" void memcpy(void* d, const void* s, unsigned int n);
extern "C" void func_ov017_02191508(int id, void* e);
extern "C" void sprintf(char* buf, const char* fmt, ...);
extern "C" void _Z15ClearEightWordsP14Struct_203dafc(void* p);
extern "C" void _Z25RestorePairTables0207df90Pc(char* p);
extern "C" void _Z24BackupPairTables0207dfacPc(char* p);
extern "C" void _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE(void* o, void* info, void* cb);
extern "C" void _ZN8Object3D8SetScaleEiii(void* o, int x, int y, int z);
extern "C" void _Z20SetByte0xbeShiftPrevP13Bytes02033b88i(void* o, int v);
extern "C" void _ZN8Object3D17SetInheritedAlphaEi(void* o, int a);
extern "C" void _Z18SetFlag0x1ceBit0x4Ph(void* o);
extern "C" void func_ov017_02191fec(void* p, int v);

extern char data_ov017_021d7a78[];
extern char data_ov017_021d7a8c[];
extern char data_ov017_021d7a9c[];

// USA: func_ov017_021b2fac
extern "C" ARM void func_ov017_021b2fac(struct Task021b2fac* task) {
    struct Alloc021b2fac* a5;
    void* m;
    void* src;
    void* loader;
    Combatant021b2fac* c2;
    struct Alloc021b2fac* a0;
    unsigned char* ent;
    void* gs;
    void* mgr;
    Combatant021b2fac* c;
    char* alloc4;
    void* e;
    struct Alloc021b2fac* a4;
    int kind;
    void* file4;
    unsigned int size4;
    char handlers[0xb8];
    char name[0x50];
    void* file5;
    unsigned int size5;
    struct LoadInfo021b2fac info;
    gs = _ZN9GameState11GetInstanceEv();
    loader = _ZN16BackgroundLoader11GetInstanceEv();
    mgr = func_ov017_0218b5b0();
    c = _Z25GetCombatantWithFlag0x100P9GameStatei(gs, task->combatantId);
    if (c == 0) {
        _Z30ResetEntriesAndNotify_021b33d8Pv(task);
        task->done = 1;
        return;
    }
    if (task->state == 0) {
        int has;
        if (c->stats != 0) {
            has = c->stats->kind != 0;
        } else {
            has = 0;
        }
        if (has != 0) {
            _ZN8Object3D7DestroyEv(c);
            a0 = c->alloc;
            _ZN13SafeAllocator5ResetEv((char*)a0 + 4);
            _ZN13SafeAllocator5ResetEv((char*)a0 + 0x18);
            task->taskId = _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(loader, data_ov017_021d7a78, data_ov017_021d7a8c, 0);
            task->state = 4;
        } else if (func_ov017_021b3444(task) != 0) {
            task->state = 1;
        } else if (func_ov017_021b38c8(task) != 0) {
            func_02083e28(c->stats, 0);
            task->state = 3;
        } else {
            task->done = 1;
            return;
        }
        _ZN8Object3D10EnableFlagEi(c, 0x200);
        return;
    }
    if (task->state == 1) {
        if (func_ov017_021b3560(task) != 0) {
            task->state = 2;
            func_ov017_021b3678(task);
        }
        return;
    }
    if (task->state == 2) {
        if (func_ov017_021b3780(task) != 0) {
            func_ov017_021b38c8(task);
            task->state = 3;
        }
        return;
    }
    if (task->state == 3) {
        if (func_ov017_021b3e14(task) != 0) {
            c2 = _Z25GetCombatantWithFlag0x100P9GameStatei(gs, task->combatantId);
            if (c2->field9c != 0) {
                m = func_ov017_0218b5b0();
                _Z32CallHelperIfCheckPasses_0218fcf8iii(m, task->combatantId, c2->field9c);
            }
            _ZN8Object3D11DisableFlagEi(c2, 0x200);
            if (task->flagsB & 8) {
                _ZN8Object3D10MakeHiddenEv(c2);
                task->flagsB &= ~8;
            }
            task->combatantId = -1;
            task->done = 1;
        }
        return;
    }
    if (task->state == 4) {
        if (_ZN16BackgroundLoader13GetTaskStatusEi(loader, task->taskId) != 0) {
            if (_ZN16BackgroundLoader21GetDetailedTaskStatusEi(loader, task->taskId) == 2) {
                _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(loader, task->taskId, &file4, &size4);
                if (file4 != 0) {
                    _Z19ResetStruct020d3c08Pc(handlers);
                    _Z36InitHandlerArrayAndRunScript020d3c84P24HandlerSlotArray020d3c84P12StreamHeaderi(handlers, file4, size4);
                    kind = c->stats != 0 ? c->stats->kind : 0;
                    src = _Z15FindEntryByKindP32FindEntryByKindContainer020d3d90i(handlers, kind);
                    e = _ZN13SafeAllocator8AllocateEj((char*)c->alloc + 0x18, 0x24);
                    if (e != 0) {
                        memcpy(e, src, 0x24);
                        c->entry = (unsigned char*)e;
                        func_ov017_02191508(task->combatantId, e);
                    }
                }
            }
            _ZN16BackgroundLoader10RemoveTaskEi(loader, task->taskId);
            task->taskId = -1;
            ent = c->entry;
            a4 = c->alloc;
            if (ent != 0) {
                sprintf(name, data_ov017_021d7a9c, ent[0x11]);
                task->taskId = _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(loader, name, (char*)a4 + 4);
            }
            task->state = 5;
        }
        return;
    }
    if (task->state == 5) {
        if (_ZN16BackgroundLoader13GetTaskStatusEi(loader, task->taskId) != 0) {
            a5 = c->alloc;
            alloc4 = (char*)a5 + 4;
            if (_ZN16BackgroundLoader21GetDetailedTaskStatusEi(loader, task->taskId) == 2) {
                _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(loader, task->taskId, &file5, &size5);
                if (file5 != 0) {
                    _Z15ClearEightWordsP14Struct_203dafc(&info);
                    info.data = file5;
                    info.size = size5;
                    info.alloc = alloc4;
                    _Z25RestorePairTables0207df90Pc(a5->tables);
                    _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE(c, &info, 0);
                    _Z24BackupPairTables0207dfacPc(a5->tables);
                }
            }
            _ZN8Object3D8SetScaleEiii(c, 0x10a, 0x10a, 0x10a);
            _Z20SetByte0xbeShiftPrevP13Bytes02033b88i(c, 0);
            _ZN8Object3D11DisableFlagEi(c, 0x200);
            _ZN8Object3D17SetInheritedAlphaEi(c, 0);
            _Z18SetFlag0x1ceBit0x4Ph(c);
            func_ov017_02191fec(mgr, c->field4);
            _ZN16BackgroundLoader10RemoveTaskEi(loader, task->taskId);
            task->taskId = -1;
            task->combatantId = -1;
            task->done = 1;
        }
    }
}
