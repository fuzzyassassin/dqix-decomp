#include <globaldefs.h>
#include <std_library_functions.h>

struct KeyboardKey {
    short x_;
    short y_;
    const char* text_;
    const char* shiftedText_;
    unsigned char flags_;
    unsigned char unk_d;
    unsigned char size_;
    unsigned char unk_f;
    char unk_10[4];
};

struct KeyboardLayout {
    KeyboardKey* keys_;
    short unk_4;
    short count_;
};

struct Keyboard {
    KeyboardKey* key_;
    KeyboardLayout* layout_;
    char* text_;
    int unk_c;
    int size_;
    int unk_14;
    int unk_18;
    short unk_1c;
    unsigned char mask_;
    unsigned char palette_;
    unsigned char shifted_;
};

struct KeyboardCanvas {
    char unk_0[8];
    void* pixels_;
    char unk_c[0xa0 - 0xc];
    int unk_a0;
    char unk_a4[0xac - 0xa4];
    short originX_;
    short originY_;
};

struct Struct_0205d81c;
struct TableA68;

struct KeyboardScreen {
    Keyboard* keyboard_;
    KeyboardLayout* layout_;
    char unk_8[0xac - 0x8];
    char elements_[0x133c - 0xac];
    char texts_[4];
};

extern "C" KeyboardCanvas* _Z23FindElementByC40205d81cP15Struct_0205d81ci(struct Struct_0205d81c* s, int key);
const char* FindEntryByKey(struct TableA68* table, int key);
extern "C" int func_020420e8(const char* text, int large);
void SetField0xa0AndByte0xc4IfFlag0x1Clear(unsigned char* obj, int value, unsigned char key);
extern "C" void func_0204ecb4(KeyboardCanvas* wnd, int a, int b, int w, int h, signed char* margins);
extern "C" void func_0204f41c(KeyboardCanvas* ctx, short x, short y, const char* str, int size,
                              unsigned char palette, short* outA, short* outB, int flag);
extern "C" void func_0204f3bc(KeyboardCanvas* ctx, int value);
extern "C" void func_ov003_0215ec68(int size, short* width, short* height);
extern "C" void func_0204f914(KeyboardCanvas* obj, int mode, short x0, short y0, short x1, short y1);
struct Obj0204fbf8;
extern "C" void _Z36InvokeHandlerAfterCacheFlush0204fbf8P11Obj0204fbf8(struct Obj0204fbf8* obj);

// USA: func_ov012_0218ab34
extern "C" ARM void func_ov012_0218ab34(KeyboardScreen* self, int skip)
{
    if (skip != 0)
        return;

    KeyboardCanvas* canvas = _Z23FindElementByC40205d81cP15Struct_0205d81ci((struct Struct_0205d81c*)self->elements_, 0xe);
    if (canvas == NULL)
        return;

    short originX = canvas->originX_ * 8;
    short originY = canvas->originY_ * 8;
    const char* title = FindEntryByKey((struct TableA68*)self->texts_, 0xe);
    int titleX = (0xf0 - func_020420e8(title, 1)) >> 1;

    Keyboard* keyboard = self->keyboard_;
    KeyboardLayout* layout = self->layout_;
    unsigned char mask;
    unsigned char shifted;
    int count;
    KeyboardKey* key;
    int i;
    int palette;
    palette = keyboard->palette_;
    mask = keyboard->mask_;
    shifted = keyboard->shifted_;
    count = layout->count_;
    key = layout->keys_;

    short outA;
    short outB;
    short width;
    short height;

    if (canvas->pixels_ != NULL)
        memset(canvas->pixels_, 0, 0x7800);
    SetField0xa0AndByte0xc4IfFlag0x1Clear((unsigned char*)canvas, canvas->unk_a0, 0xe);
    func_0204ecb4(canvas, 0, 0, 0x1e, 0x12, 0);
    func_0204f41c(canvas, titleX, 6, title, 0xc, 0xf, &outA, &outB, palette);
    func_0204f3bc(canvas, 0x18);

    for (i = 0; i < count; i++, key++) {
        if ((key->flags_ & mask) == 0)
            continue;

        const char* normal = key->text_;
        const char* text = normal;
        if (shifted != 0 || (mask & 2) != 0)
            text = key->shiftedText_;
        if (key->unk_d != 0)
            text = normal;

        int textWidth = func_020420e8(text, 1);
        func_ov003_0215ec68(key->size_, &width, &height);
        short x = key->x_ - originX;
        short y = key->y_ - originY;
        func_0204f914(canvas, 4, x + 1, y + 1, width + x - 1, height + y - 1);
        width = (width - textWidth) >> 1;
        func_0204f41c(canvas, width + x, y + 2, text, 0xc, 0xf, &outA, &outB, palette);
    }

    _Z36InvokeHandlerAfterCacheFlush0204fbf8P11Obj0204fbf8((struct Obj0204fbf8*)canvas);
}
