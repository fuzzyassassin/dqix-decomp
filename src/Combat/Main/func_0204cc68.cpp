#include <globaldefs.h>

struct Wnd0204cc68 {
    char pad0[8];
    unsigned char* buf;
    char padC[0x9c];
    short tilesW;
    short tilesH;
};

// USA: func_0204cc68
extern "C" ARM void func_0204cc68(Wnd0204cc68* wnd, int color, short x0, short y0, short x1, short y1) {
    if (x1 < 0 || y1 < 0) {
        return;
    }
    short h = (short)(wnd->tilesH << 3);
    short w = (short)(wnd->tilesW << 3);
    if (x1 > w) {
        return;
    }
    if (h < y1) {
        return;
    }
    if (x0 == x1 || y0 == y1) {
        return;
    }
    unsigned char hi = (color & 0xf) << 4;
    int lo = color & 0xf;
    for (short y = y0; y < y1; y++) {
        short py = (short)(y & 7) << 2;
        int row = (short)(y >> 3) * wnd->tilesW;
        for (short x = x0; x < x1; x++) {
            short tile = row + (short)(x >> 3);
            short idx = (short)((short)(tile << 5) + (short)((short)(x & 7) >> 1)) + py;
            unsigned char* p = wnd->buf;
            if (x & 1) {
                p[idx] &= 0xf;
                p[idx] |= hi;
            } else {
                p[idx] &= 0xf0;
                p[idx] |= lo;
            }
        }
    }
}
