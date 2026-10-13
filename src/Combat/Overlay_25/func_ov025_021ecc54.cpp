#include <globaldefs.h>

struct Struct021ecb90 {
    int a;
    unsigned char idx : 6;
    unsigned char mode : 2;
    unsigned char c;
    unsigned char d;
    unsigned char pad07;
    unsigned int e;
    unsigned int f;
    unsigned int g;
    unsigned int ringBase;
    unsigned int ringStride;
    int j;
    short k;
    short l;
    unsigned int m;
    int n;
    unsigned short o;
    short p;
    short q;
    short r;
    short s;
    short t;
    unsigned char u;
    unsigned char v;
    unsigned char w;
    unsigned char pad3b;
    unsigned short x;
    unsigned short pad3e;
};

struct Container021ecc54 {
    struct Struct021ecb90 entries[12];
    unsigned char f300;
    unsigned char f301;
    unsigned short f302;
    short f304;
    unsigned char f306;
    unsigned char pad307;
    int f308;
    void* f30c;
    unsigned char f310;
    unsigned char f311;
};

struct Member021ecc54 {
    unsigned long long flags;
    char pad08[0x18];
    struct Member021ecc54* next;
};

struct ListNode021600f8 {
    struct Member021ecc54* members;
    char pad04[0x14];
    unsigned char counts[3];
};

struct ListNode02160094 {
    struct Member021ecc54* members[3];
    char pad0c[0x1a];
    unsigned char counts[6];
};

struct List021ecc54 {
    char pad00[8];
    unsigned char count8;
    unsigned char count9;
};

struct Source021ecc54 {
    struct List021ecc54* list;
    unsigned int f04;
    unsigned int f08;
    unsigned int f0c;
    unsigned int f10;
    short k0;
    short k1;
    int n;
    short l0;
    short l1;
    unsigned int m;
    unsigned short f24;
    unsigned short flags;
    unsigned short o;
    short p;
    short q;
    short r;
    short s;
    short t;
    unsigned char u;
    unsigned char v;
    char pad36[2];
    unsigned char f38;
};

extern "C" struct ListNode021600f8* _Z22GetNodeAtIndex021600f8P12List021600f8i(struct List021ecc54* list, int index);
extern "C" struct ListNode02160094* _Z22GetNodeAtIndex02160094P12List02160094i(struct List021ecc54* list, int index);
extern "C" void func_ov025_021ebb24(struct Struct021ecb90* obj);
extern "C" int func_ov000_0215fd90(struct Member021ecc54* member, int flag);
extern "C" void func_ov025_021ed0b8(struct Container021ecc54* obj, struct Struct021ecb90* src);

extern unsigned int data_ov025_021ef010[];
extern const int data_ov025_021ef008[];

// USA: func_ov025_021ecc54
extern "C" ARM void func_ov025_021ecc54(struct Container021ecc54* obj, struct Source021ecc54* src) {
    int counts[2];
    struct Struct021ecb90 entry;

    obj->f306 = 0;
    counts[0] = src->list->count9;
    counts[1] = src->list->count8;

    for (int k = 0; k < 2; k++) {
        if (src->flags & data_ov025_021ef010[k]) continue;
        for (int i = 0; i < counts[k]; i++) {
            struct List021ecc54* list = src->list;
            int total = -1;
            if (data_ov025_021ef008[k] == 1) {
                struct ListNode021600f8* node = _Z22GetNodeAtIndex021600f8P12List021600f8i(list, i);
                if (node != 0) {
                    total = node->counts[0];
                    total += node->counts[1];
                    total += node->counts[2];
                }
            } else if (data_ov025_021ef008[k] == 0) {
                struct ListNode02160094* node = _Z22GetNodeAtIndex02160094P12List02160094i(list, i);
                if (node != 0) {
                    total = node->counts[0];
                    total += node->counts[2];
                    total += node->counts[3];
                    total += node->counts[4];
                    total += node->counts[5];
                    total += node->counts[1];
                }
            }
            if (total <= 0) continue;

            func_ov025_021ebb24(&entry);
            int found = 0;
            struct Member021ecc54** members = 0;
            unsigned char* cnts = 0;
            if (data_ov025_021ef008[k] == 1) {
                found = 1;
            } else if (data_ov025_021ef008[k] == 0) {
                struct ListNode02160094* node = _Z22GetNodeAtIndex02160094P12List02160094i(src->list, i);
                if (node != 0) {
                    members = node->members;
                    cnts = node->counts;
                }
            }
            if (members != 0) {
                for (int t = 0; t < 3; t++) {
                    struct Member021ecc54* m = *members;
                    int n = *cnts;
                    for (int j = 0; j < n; j++) {
                        if (data_ov025_021ef008[k] == 0 && m->flags == 0x100) entry.d |= 6;
                        if (m->flags != 0) {
                            found = 1;
                            break;
                        }
                        m++;
                    }
                    if (found) break;
                    members++;
                    cnts++;
                }
            }

            entry.a = (int)src->list;
            entry.idx = i;
            entry.mode = data_ov025_021ef008[k];
            if (src->flags & 0x10) {
                entry.mode = 2;
            } else if (src->flags & 0x20) {
                entry.mode = 3;
            }
            entry.c = 6;
            entry.f = src->f04;
            entry.ringBase = src->f0c;
            entry.ringStride = src->f10;
            entry.g = src->f08;
            entry.n = src->n;
            entry.l = src->l0;
            entry.m = src->m;
            entry.o = src->o;
            entry.p = src->p;
            entry.q = src->q;
            entry.u = src->u;
            entry.v = src->v;
            entry.r = src->r;
            entry.s = src->s;
            entry.t = src->t;
            if (src->k1 < 0) {
                entry.k = src->k0;
                entry.l = src->l0;
            } else {
                int hasStatus;
                struct List021ecc54* list2 = src->list;
                if (data_ov025_021ef008[k] == 1) {
                    struct ListNode021600f8* node = _Z22GetNodeAtIndex021600f8P12List021600f8i(list2, i);
                    if (node != 0) {
                        for (struct Member021ecc54* m = node->members; m != 0; m = m->next) {
                            if (func_ov000_0215fd90(m, 3)) {
                                hasStatus = 1;
                                goto checked;
                            }
                        }
                    }
                } else if (data_ov025_021ef008[k] == 0) {
                    struct ListNode02160094* node = _Z22GetNodeAtIndex02160094P12List02160094i(list2, i);
                    if (node != 0) {
                        for (struct Member021ecc54* m = node->members[0]; m != 0; m = m->next) {
                            if (func_ov000_0215fd90(m, 3)) {
                                hasStatus = 1;
                                goto checked;
                            }
                        }
                    }
                }
                hasStatus = 0;
            checked:
                if (hasStatus) {
                    entry.k = src->k1;
                    entry.l = src->l1;
                    entry.d |= 0x20;
                    entry.n &= ~1;
                } else {
                    entry.k = src->k0;
                    entry.l = src->l0;
                }
            }
            if (entry.k < 0) entry.d |= 2;
            if (entry.l < 0) entry.d |= 4;
            if (!found) entry.d |= 6;
            if (src->f38 != 0) entry.d |= 0x40;
            func_ov025_021ed0b8(obj, &entry);
        }
    }
    obj->f302 = src->f24;
    if (obj->f300 != 0) obj->f310 = 0;
}
