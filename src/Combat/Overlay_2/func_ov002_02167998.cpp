#include <globaldefs.h>

class GameState;
struct Struct0205de24;
struct Struct_0205c570;
struct Struct_0205d81c;
struct Struct_0205def8;
struct Elem_0205d81c;
struct ShortArrays0204c610;
struct ShortArrays0204c654;
struct Obj0205eaa0;
struct Obj_0205da38;

struct Cursor {
    int col;
    int row;
};

struct Flags3c {
    unsigned int pad : 30;
    unsigned int toggle : 1;
    unsigned int top : 1;
};

extern "C" GameState *_ZN9GameState11GetInstanceEv();
extern "C" unsigned char *_ZN9GameState21GetPartyMemberByIndexEi(GameState *gs, int idx);
int GetField0x3acValue(GameState *gs);
void SetElementFlag0x20ByKey0205def8(struct Struct_0205def8 *s, int clear, int key);
extern "C" void _Z32FindAndLinkMatchingEntry0205de24P14Struct0205de24hh(struct Struct0205de24 *obj, unsigned char keyLow,
                                                                        unsigned char keyHigh);
struct Elem_0205d81c *FindElementByC40205d81c(struct Struct_0205d81c *s, int key);
void GetFourShortsAtIndex(struct ShortArrays0204c610 *base, int index, short *out0, short *out1, short *out2, short *out3);
extern "C" void _Z20SetFourShortsAtIndexP19ShortArrays0204c654issss(struct ShortArrays0204c654 *base, short index, short a, short b, short c, short d);
extern "C" int _Z26GetActiveScaledSum0205d794P15Struct_0205c570(struct Struct_0205c570 *s);
extern "C" void func_0205d7a0(unsigned char *obj, int val);
int TestFlag0SetAndFlag1Clear(unsigned short *flags, int mask);
int IsActiveElementFlag2Set0205da38(struct Obj_0205da38 *obj, int key);
extern "C" void _Z28DispatchWithShortB4_0205eaa0P11Obj0205eaa0ii(struct Obj0205eaa0 *o, int a, int b);
extern "C" int _Z29CheckFlagOrThreshold_02161b48Pci(char *self, int flag);
unsigned char *GetFieldAt0x150(unsigned char *c);
extern "C" void func_ov002_02161cf0(void *self);
extern "C" void func_ov002_0215f6a4(void *self);
extern "C" void func_ov002_02161a8c(void);
extern "C" void func_ov002_021619b4(int member, int a, int b);
extern "C" void func_ov002_0215b9a4(void *self, int mode, int flag);
extern "C" void func_ov002_02156e90(void *self);

extern unsigned char data_ov002_0216cc98[];
extern unsigned char data_02114e54[];
extern unsigned short data_02114e30;
extern char data_02108760[];

// USA: func_ov002_02167998
extern "C" ARM void func_ov002_02167998(char *base) {
    unsigned char *obj = (unsigned char *) (base + 0xec8);
    int col;
    short v;
    int last;
    int shown;
    GameState *gs = _ZN9GameState11GetInstanceEv();
    int phase     = *(int *) (base + 0x1bc0);
    if (phase == 0) {
        base[0x1c34] = 0;
        for (int i = 0; i < 5; i++) {
            SetElementFlag0x20ByKey0205def8((struct Struct_0205def8 *) obj, 0, data_ov002_0216cc98[i]);
        }
        base[0x1c20]               = GetField0x3acValue(gs);
        *(short *) (base + 0x1c02) = 0;
        _Z32FindAndLinkMatchingEntry0205de24P14Struct0205de24hh((struct Struct0205de24 *) obj, 0, 2);
        func_ov002_02161cf0(base);
        func_ov002_0215f6a4(base);
        (*(int *) (base + 0x1bc0))++;
        func_ov002_02161a8c();
        func_ov002_021619b4(*(signed char *) (base + 0x1c20), *(int *) (base + 0x1a68), *(int *) (base + 0x1bd8));
        return;
    }
    if (phase != 1) return;
    *(int *) (base + 0x247c) |= 4;
    struct Elem_0205d81c *e = FindElementByC40205d81c((struct Struct_0205d81c *) obj, 0x18);
    if (e != 0) {
        short idx = *(signed char *) (base + 0x1c73);
        short a, b, c, d;
        GetFourShortsAtIndex((struct ShortArrays0204c610 *) e, idx, &a, &b, &c, &d);
        idx += *(signed char *) (base + 0x1c73) + 1;
        _Z20SetFourShortsAtIndexP19ShortArrays0204c654issss((struct ShortArrays0204c654 *) e, idx, a, b, c, d);
        idx += *(signed char *) (base + 0x1c73) + 1;
        _Z20SetFourShortsAtIndexP19ShortArrays0204c654issss((struct ShortArrays0204c654 *) e, idx, a, b, c, d);
    }
    int mode;
    int sel;
    short old = *(short *) (base + 0x1c02);
    col         = old % (*(signed char *) (base + 0x1c73) + 1);
    Cursor *cur = (Cursor *) (obj + 0x6c);
    mode        = cur->col;
    sel         = cur->row;
    *(short *) (base + 0x1c02) = _Z26GetActiveScaledSum0205d794P15Struct_0205c570((struct Struct_0205c570 *) obj);
    if (old != *(short *) (base + 0x1c02)) {
        if (col == sel && sel == *(signed char *) (base + 0x1c73) && data_02114e54[0x55] == 0) {
            sel--;
            v = mode * (*(signed char *) (base + 0x1c73) + 1) + sel;
            func_0205d7a0(obj, v);
            *(short *) (base + 0x1c02) = v;
        }
        base[0x1c20] = -1;
        if (sel < *(signed char *) (base + 0x1c73)) {
            base[0x1c20] = *(signed char *) (base + sel + 0x1c6e);
        }
        base[0x1c34] = 1;
    }
    last  = sel == *(signed char *) (base + 0x1c73);
    shown = !last;
    SetElementFlag0x20ByKey0205def8((struct Struct_0205def8 *) obj, shown, 0x1a);
    SetElementFlag0x20ByKey0205def8((struct Struct_0205def8 *) obj, shown, 0x1b);
    if (old != *(short *) (base + 0x1c02)) return;
    int pressed = TestFlag0SetAndFlag1Clear(&data_02114e30, 0x601);
    int confirm = (pressed | IsActiveElementFlag2Set0205da38((struct Obj_0205da38 *) (base + 0x2c8 + 0xc00), 0x14)) ? 1 : 0;
    if (confirm) {
        if (sel == *(signed char *) (base + 0x1c73)) {
            _Z28DispatchWithShortB4_0205eaa0P11Obj0205eaa0ii((struct Obj0205eaa0 *) data_02108760, 1, 0);
            for (int i = 0; i < 5; i++) {
                SetElementFlag0x20ByKey0205def8((struct Struct_0205def8 *) obj, 1, data_ov002_0216cc98[i]);
            }
            *(short *) (base + 0x1c02) = -1;
            func_ov002_02156e90(base);
            func_ov002_02156e90(base);
            func_ov002_02156e90(base);
            return;
        }
        int member       = *(signed char *) (base + 0x1c20);
        unsigned char *m = _ZN9GameState21GetPartyMemberByIndexEi(gs, member);
        if (m == 0) return;
        switch (mode) {
        case 0:
            if (member == GetField0x3acValue(gs)) return;
            func_ov002_0215b9a4(base, *(int *) (base + 0x1bb8) & 0xff, 1);
            _Z28DispatchWithShortB4_0205eaa0P11Obj0205eaa0ii((struct Obj0205eaa0 *) data_02108760, 1, 0);
            *(int *) (base + 0x1bb8)   = 0x19;
            *(int *) (base + 0x1bc0)   = 0;
            *(short *) (base + 0x1c04) = (signed char) *(int *) (GetFieldAt0x150(m) + 0x94c);
            break;
        case 1: {
            struct Flags3c *f = (struct Flags3c *) (*(unsigned char **) (m + 0x134) + 0x3c);
            unsigned short t = f->toggle;
            t++;
            t %= 2;
            f->toggle = t;
            func_ov002_0215b9a4(base, *(int *) (base + 0x1bb8) & 0xff, 0);
            _Z28DispatchWithShortB4_0205eaa0P11Obj0205eaa0ii((struct Obj0205eaa0 *) data_02108760, 1, 0);
            break;
        }
        case 2: {
            unsigned char *f = GetFieldAt0x150(m);
            obj[0xb8]        = *(int *) (base + 0x1bb8);
            *(int *) (base + 0x247c) &= ~4;
            _Z28DispatchWithShortB4_0205eaa0P11Obj0205eaa0ii((struct Obj0205eaa0 *) data_02108760, 1, 0);
            *(int *) (base + 0x1bb8)   = 0x1c;
            *(int *) (base + 0x1bc0)   = 0;
            *(short *) (base + 0x1c06) = f[0x56a];
            break;
        }
        }
        return;
    }
    if (_Z29CheckFlagOrThreshold_02161b48Pci(base, 1)) {
        for (int i = 0; i < 5; i++) {
            SetElementFlag0x20ByKey0205def8((struct Struct_0205def8 *) obj, 1, data_ov002_0216cc98[i]);
        }
        *(short *) (base + 0x1c02) = -1;
        func_ov002_02156e90(base);
        func_ov002_02156e90(base);
        func_ov002_02156e90(base);
    }
}
