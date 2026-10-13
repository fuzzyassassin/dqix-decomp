#include "GameState/GameState.h"
#include <globaldefs.h>

struct Obj2081;
struct Cont0207fdf0;
struct Obj0205eaa0;
struct Obj0208203c;
struct Container020dedd0;
struct Obj02179e18;
struct Obj021dcae0;

void *GetPtrField0x2a04(GameState *gs);

extern "C" int func_ov003_02179f34(char *obj);
short FindMappedMemberId02080468(void *obj, int id);
extern "C" void func_ov003_02177dd4(void *obj);
void SetElementFlag0x40(struct Obj2081 *obj, int id, int value);
void SetEntryLowNibbleAndElement02080c68(void *obj, int id, int value);
void ResetWithSub0208203c(struct Obj0208203c *obj);
extern "C" void func_ov003_021748c4(unsigned char *self);
extern "C" void func_ov003_0217a14c(void *p);
extern "C" void func_ov023_021dcae0(struct Obj021dcae0 *obj, int val);
extern "C" int func_ov003_021765b4(void *self);
void DispatchWithShortB4_0205eaa0(struct Obj0205eaa0 *obj, int a, int b);
struct Element020de650 {
    char pad[8];
    unsigned int word;
};
struct Element020de650 *FindElementByKey020dedd0(struct Container020dedd0 *c, int key);
void CallFunc0204c804OnNonMatchingKey(struct Cont0207fdf0 *obj, int key);
extern "C" int func_ov003_02179da8(void *obj, int flag);
extern "C" int func_ov003_021766e8(void *self);
extern "C" void func_ov003_02177208(char *obj);
extern "C" void func_ov003_0217726c(char *obj);
extern "C" int func_ov003_02178218(void *self);
extern "C" int func_02081f20(void *obj, int scaleCount);
unsigned short GetInnerShort_0217b200(void **obj);
short SumKeyedLookups02086bf4(char *obj, int key);
unsigned int ComputeTimeRemaining_02179e18(struct Obj02179e18 *obj);
extern "C" int func_ov003_021782a0(struct Obj2081 *obj);
int TestFlag0SetAndFlag1Clear(unsigned short *obj, int mask);
void CallFunc0204c804OnMatchingKey(struct Obj2081 *obj, int key);
extern "C" void func_ov003_02176468(unsigned char *self);
extern "C" int func_ov003_021764f4(unsigned char *self);
void RefillAndResetEntry_02175d78(char *obj);
extern "C" void func_ov003_02175df4(void *self);

extern struct Obj0205eaa0 data_02108760;
extern unsigned short data_02114e30;

static inline int ElemKind(struct Element020de650 *e) {
    unsigned int w = e->word;
    return (int) ((w << 18) >> 30);
}

// USA: func_ov003_0217ab34
extern "C" ARM void func_ov003_0217ab34(unsigned char *self) {
    GameState *battle = GameState::GetInstance();
    char *battleSum   = (char *) GetPtrField0x2a04(battle);
    void *elemObj     = *(void **) (self + 0x89c);
    int state         = *(unsigned char *) (self + 0x1000 + 0x3f);

    if (state == 0) {
        int cnt               = func_ov003_02179f34((char *) self);
        unsigned short *flags = (unsigned short *) (self + 0x1000 + 0x46);
        *flags                = (unsigned short) (*flags & ~0x400);
        if (cnt > 8) {
            *flags = (unsigned short) (*flags | 0x400);
        }
        *(short *) (self + 0xf00 + 0xfe) = 0x16;
        if (*(short *) (self + 0x1000 + 0xe) < 0) {
            *(short *) (self + 0x1000 + 0xe) = FindMappedMemberId02080468(elemObj, *(short *) (self + 0xf00 + 0xfe));
        }
        short first = FindMappedMemberId02080468(elemObj, *(short *) (self + 0xf00 + 0xfe));
        short col   = (short) (*(short *) (self + 0x1000 + 0xe) - first);
        short row   = (short) (*(short *) (self + 0x1000 + 0x14) * 8 + col);
        *(short *) (self + 0x1000 + 0x3a)         = *(short *) (battleSum + 0xc + row * 2);
        *(unsigned char *) (self + 0x1000 + 0x3c) = 1;
        func_ov003_02177dd4(self);
        SetElementFlag0x40((struct Obj2081 *) elemObj, *(short *) (self + 0xf00 + 0xfe), 0);
        SetEntryLowNibbleAndElement02080c68(elemObj, *(short *) (self + 0xf00 + 0xfe), 0);
        ResetWithSub0208203c((struct Obj0208203c *) (self + 0x88c));
        *(void **) (self + 0xff8)                 = 0;
        *(unsigned char *) (self + 0x1000 + 0x3f) = 1;
        func_ov003_021748c4(self);
        return;
    }

    if (state == 1) {
        short saved               = *(short *) (self + 0x1000 + 0x3a);
        *(void **) (self + 0xff8) = self + 0x1000 + 0xe;
        func_ov003_0217a14c(self);
        func_ov023_021dcae0((struct Obj021dcae0 *) (self + 0x3c), *(short *) (self + 0x1000 + 0x3a));
        if (func_ov003_021765b4(self) != 0 && saved == *(short *) (self + 0x1000 + 0x3a)) {
            DispatchWithShortB4_0205eaa0(&data_02108760, 1, 0);
            ResetWithSub0208203c((struct Obj0208203c *) (self + 0x88c));
            *(void **) (self + 0xff8) = 0;
            *(void **) (self + 8) =
                FindElementByKey020dedd0((struct Container020dedd0 *) (self + 0x874), *(short *) (self + 0x1000 + 0x3a));
            if (*(void **) (self + 8) == 0) return;
            *(short *) (self + 0xf00 + 0xfc) = *(short *) (self + 0xf00 + 0xfe);
            SetEntryLowNibbleAndElement02080c68(elemObj, *(short *) (self + 0xf00 + 0xfe), 1);
            *(unsigned char *) (self + 0x1000 + 0x3f) = 2;
            if (ElemKind(*(struct Element020de650 **) (self + 8)) == 0) {
                CallFunc0204c804OnNonMatchingKey((struct Cont0207fdf0 *) elemObj, 0);
                *(short *) (self + 0x1000 + 0x36)          = 0x12;
                *(unsigned char *) (self + 0x1000 + 0x3f)  = 0;
                unsigned short f                           = *(unsigned short *) (self + 0x1000 + 0x46);
                f                                          = (unsigned short) ((f | 0x20) & ~0x2000);
                *(unsigned short *) (self + 0x1000 + 0x46) = f;
                return;
            }
            int tier = func_ov003_02179da8(*(void **) (self + 8), 1);
            switch (tier) {
                case 1:
                    CallFunc0204c804OnNonMatchingKey((struct Cont0207fdf0 *) elemObj, 0);
                    *(short *) (self + 0x1000 + 0x36)         = 0xd;
                    *(unsigned char *) (self + 0x1000 + 0x3f) = 6;
                    *(unsigned short *) (self + 0x1000 + 0x46) =
                        (unsigned short) (*(unsigned short *) (self + 0x1000 + 0x46) | 0x2000);
                    if (ElemKind(*(struct Element020de650 **) (self + 8)) != 2) return;
                    *(short *) (self + 0x1000 + 0x36)         = 0x11;
                    *(unsigned char *) (self + 0x1000 + 0x3f) = 4;
                    return;
                case 2:
                    CallFunc0204c804OnNonMatchingKey((struct Cont0207fdf0 *) elemObj, 0);
                    *(short *) (self + 0x1000 + 0x36)         = 0x1c;
                    *(unsigned char *) (self + 0x1000 + 0x3e) = 1;
                    *(unsigned char *) (self + 0x1000 + 0x3f) = 0;
                    *(unsigned short *) (self + 0x1000 + 0x46) =
                        (unsigned short) (*(unsigned short *) (self + 0x1000 + 0x46) | 0x2000);
                    return;
                default: return;
            }
        }
        if (func_ov003_021766e8(self) == 0) return;
        ResetWithSub0208203c((struct Obj0208203c *) (self + 0x88c));
        *(void **) (self + 0xff8) = 0;
        CallFunc0204c804OnNonMatchingKey((struct Cont0207fdf0 *) elemObj, 0);
        *(unsigned char *) (self + 0x1000 + 0x3e)  = 4;
        *(unsigned char *) (self + 0x1000 + 0x3f)  = 1;
        *(unsigned short *) (self + 0x1000 + 0x46) = (unsigned short) (*(unsigned short *) (self + 0x1000 + 0x46) | 0x2000);
        return;
    }

    if (state == 2) {
        func_ov003_02177208((char *) self);
        func_ov003_0217726c((char *) self);
        ResetWithSub0208203c((struct Obj0208203c *) (self + 0x88c));
        *(unsigned char *) (self + 0x1000 + 0x3f) = 3;
        *(unsigned char *) (self + 0x1000 + 0x4a) = 0;
        return;
    }

    if (state == 3) {
        int delta             = 0;
        unsigned char counter = *(unsigned char *) (self + 0x1000 + 0x4a);
        if (counter < 5) {
            *(unsigned char *) (self + 0x1000 + 0x4a) = (unsigned char) (counter + 1);
        } else {
            delta = func_ov003_02178218(self);
            if (delta != 0) {
                *(unsigned char *) (self + 0x1000 + 0x4a) = 0;
            }
        }
        GameState *b2 = GameState::GetInstance();
        int ticks     = (int) b2->GetTickCount();
        int ratio     = func_02081f20(self + 0x88c, ticks);
        if ((unsigned short) (ratio + 0xffff) <= 1) {
            unsigned short v = GetInnerShort_0217b200((void **) (self + 0x88c));
            if (v == 0x40)
                delta = 1;
            else if (v == 0x80)
                delta = -1;
            else if (v == 0x20)
                delta = 0x83;
            else if (v == 0x10)
                delta = ~0x82;
        }
        if (delta != 0) {
            int newCap          = *(unsigned char *) (self + 0x1000 + 0x3c) + delta;
            int keyed           = SumKeyedLookups02086bf4(battleSum, *(short *) (self + 0x1000 + 0x3a));
            unsigned int remain = ComputeTimeRemaining_02179e18(*(struct Obj02179e18 **) (self + 8));
            if ((int) remain < keyed) keyed = (int) remain;
            if (keyed < newCap) newCap = keyed;
            if (newCap <= 1) newCap = 1;
            *(unsigned char *) (self + 0x1000 + 0x4b) = (*(unsigned char *) (self + 0x1000 + 0x3c) < newCap) ? 1 : 0;
            *(unsigned char *) (self + 0x1000 + 0x4c) = (newCap < *(unsigned char *) (self + 0x1000 + 0x3c)) ? 1 : 0;
            *(unsigned char *) (self + 0x1000 + 0x3c) = (unsigned char) newCap;
            func_ov003_02177208((char *) self);
            func_ov003_0217726c((char *) self);
        }
        int hit = func_ov003_021782a0((struct Obj2081 *) self);
        if (TestFlag0SetAndFlag1Clear(&data_02114e30, 0x401) != 0 || hit == 1) {
            DispatchWithShortB4_0205eaa0(&data_02108760, 1, 0);
            CallFunc0204c804OnNonMatchingKey((struct Cont0207fdf0 *) elemObj, 0);
            *(short *) (self + 0x1000 + 0x36) = 0xd;
            if (*(unsigned char *) (self + 0x1000 + 0x3c) > 1) {
                *(short *) (self + 0x1000 + 0x36) = 0x20;
            }
            *(unsigned char *) (self + 0x1000 + 0x3f) = 6;
            *(unsigned short *) (self + 0x1000 + 0x46) =
                (unsigned short) (*(unsigned short *) (self + 0x1000 + 0x46) | 0x2000);
            ResetWithSub0208203c((struct Obj0208203c *) (self + 0x88c));
            if (ElemKind(*(struct Element020de650 **) (self + 8)) != 2) return;
            *(short *) (self + 0x1000 + 0x36)         = 0x11;
            *(unsigned char *) (self + 0x1000 + 0x3f) = 4;
            return;
        }
        if (TestFlag0SetAndFlag1Clear(&data_02114e30, 2) != 0 || hit == -1) {
            CallFunc0204c804OnMatchingKey((struct Obj2081 *) elemObj, 9);
            CallFunc0204c804OnMatchingKey((struct Obj2081 *) elemObj, 0xa);
            ResetWithSub0208203c((struct Obj0208203c *) (self + 0x88c));
            *(unsigned char *) (self + 0x1000 + 0x3f) = 0;
        }
        return;
    }

    if (state == 4) {
        func_ov003_02176468(self);
        *(unsigned char *) (self + 0x1000 + 0x3f) = 5;
        return;
    }

    if (state == 5) {
        int res = func_ov003_021764f4(self);
        if (res == -1) goto fail5;
        if (res != 1) return;
        *(short *) (self + 0x1000 + 0x36)         = 0x10;
        *(unsigned char *) (self + 0x1000 + 0x3f) = 6;
        return;
    fail5:
        *(short *) (self + 0x1000 + 0x36)          = 0x30;
        *(unsigned char *) (self + 0x1000 + 0x3f)  = 0;
        *(unsigned short *) (self + 0x1000 + 0x46) = (unsigned short) (*(unsigned short *) (self + 0x1000 + 0x46) | 0x20);
        return;
    }

    if (state == 6) {
        func_ov003_02176468(self);
        *(unsigned char *) (self + 0x1000 + 0x3f) = 7;
        return;
    }

    if (state == 7) {
        int res = func_ov003_021764f4(self);
        if (res == -1) goto fail7;
        if (res != 1) return;
        RefillAndResetEntry_02175d78((char *) self);
        func_ov003_02175df4(self);
        *(short *) (self + 0x1000 + 0x36)          = 0xe;
        *(unsigned char *) (self + 0x1000 + 0x3e)  = 4;
        *(unsigned char *) (self + 0x1000 + 0x3f)  = 1;
        *(unsigned short *) (self + 0x1000 + 0x46) = (unsigned short) (*(unsigned short *) (self + 0x1000 + 0x46) | 0x20);
        return;
    fail7:
        *(short *) (self + 0x1000 + 0x36)          = 0x30;
        *(unsigned char *) (self + 0x1000 + 0x3e)  = 6;
        *(unsigned char *) (self + 0x1000 + 0x3f)  = 0;
        *(unsigned short *) (self + 0x1000 + 0x46) = (unsigned short) (*(unsigned short *) (self + 0x1000 + 0x46) | 0x20);
        return;
    }
}
