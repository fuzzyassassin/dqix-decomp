#include <globaldefs.h>

struct Param02030b0c { unsigned char _u[8]; };
extern "C" int _ZNK6Script9Parameter5ToIntEv(const struct Param02030b0c* self);

struct W12 {
    unsigned int a : 5;
    unsigned int b : 7;
    unsigned int c : 8;
    unsigned int d : 5;
    unsigned int e : 7;
};
union U12 { struct W12 b; unsigned int raw; };
struct Record12 {
    unsigned short id : 11;
    unsigned short slot : 5;
    unsigned short f2;
    union U12 u;
    unsigned short f8;
    unsigned short fa;
};

struct RecordList0209a55c;
void AppendRecord12Capped(struct RecordList0209a55c* list, struct Record12* src);

extern struct RecordList0209a55c* data_02109ba4;

static inline int ParamInt(const struct Param02030b0c* p) { return _ZNK6Script9Parameter5ToIntEv(p); }

// USA: func_0209a218
extern "C" ARM int func_0209a218(struct Param02030b0c* args) {
    struct Record12 rec;
    unsigned int v;

    rec.id = ParamInt(&args[0]);
    rec.u.b.a = ParamInt(&args[1]);
    rec.u.b.b = ParamInt(&args[2]);
    rec.f2 = ParamInt(&args[3]);
    rec.slot = ParamInt(&args[4]);
    v = ParamInt(&args[5]);
    rec.u.raw &= ~0xff000u;
    rec.u.raw |= (v & 0xff) << 12;
    rec.f8 = ParamInt(&args[6]);
    rec.fa = ParamInt(&args[7]);
    v = ParamInt(&args[8]);
    rec.u.raw &= ~0x1f00000u;
    rec.u.raw |= (v & 0x1f) << 20;
    rec.u.b.e = 0;

    if (rec.u.b.c != 0) {
        AppendRecord12Capped(data_02109ba4, &rec);
    }
    return 1;
}
