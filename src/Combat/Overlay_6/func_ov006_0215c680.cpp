#include <globaldefs.h>

#if defined(jpn)
enum { kMenuCursor = 0x2a, kLayoutToTable = 0x48, kWindowFlags = 0x1054 };
#else
enum { kMenuCursor = 0x36, kLayoutToTable = 0x4c, kWindowFlags = 0x1258 };
#endif

struct Obj0208203c { int fields_[3]; };
struct Obj0205eaa0;
struct Obj2081;
struct Container02071ffc;
struct StructC28;
struct AlchemyPot;
struct Recipe;

struct Obj2081 {
    char unk_0[kMenuCursor];
    short cursor_;
};

struct RecipeTable {
    Recipe* unk_0;
    int unk_4[2];
};

struct AlchemyMenu {
#if !defined(jpn)
    int textPosition_;
    char** texts_;
#endif
    void* canvasBuffer_;
    void* allocators_;
    AlchemyPot* pot_;
    Obj2081* menu_;
    void* choice_;
    void* backgrounds_;
    void* canvases_;
    void* sprites_;
    void* animations_;
    Recipe* recipes_;
    Recipe* pageStart_;
    Recipe* recipe_;
    void* records_;
    char save_[8];
    short* cursor_;
    short** items_;
    unsigned char** counts_;
    unsigned short* sizes_;
    int subBackground_[0x20 / 4];
    int ingredients_[0x28 / 4];
    Obj0208203c repeat_;
    unsigned short buttons_;
    unsigned char unk_aa;
    int renderer_[0x54 / 4];
    int layout_[kLayoutToTable / 4];
    RecipeTable table_;
    int menuTexts_[0x18 / 4];
    char itemNames_[0xc];
#if defined(jpn)
    char reservedBeforeResults_[0xc];
#endif
    int results_[4][0x74 / 4];
    int ticks_;
    int menuResult_;
    int task_;
    int unk_358;
    short unk_35c;
    short previousCursor_;
    short mainCursor_;
    short categoryCursor_;
    short itemCursor_;
    short bookCursor_;
    short filterCursor_;
    short recipeCursor_;
    short choiceCursor_;
    short group_;
    short item_;
    unsigned short categories_[3];
    short chosenItems_[3];
    short message_;
    unsigned short messageLength_;
    short successRate_;
    signed char filterCategory_;
    signed char filterKind_;
    unsigned char sort_;
    unsigned char times_;
    unsigned char page_;
    unsigned char pages_;
    unsigned char category_;
    unsigned char count_;
    unsigned char chosenCounts_[3];
    unsigned char state_;
    unsigned char step_;
    unsigned char unk_391;
    unsigned char messageStep_;
    unsigned char repeatDelay_;
    unsigned short flags_;
    unsigned char female_;
    unsigned char background_;
    unsigned char amounts_[3];
    int textSound_;
    int unk_3a0;
    int textSoundOn_;
    unsigned int textSoundTimer_;
    int textSoundPlaying_;
    int textSoundState_;
    int showResult_;
    int resultSprite_[0x70 / 4];
    int resultTask_;
    signed char arrowTimer_;
    unsigned char fadeTimer_;
    unsigned char nextStep_;
    unsigned char saved_;
    unsigned char arrowUp_;
    unsigned char arrowDown_;
    unsigned char resetBlend_;
    unsigned char closing_;
    unsigned char closeRequested_;
};


struct Obj0215951c;
struct Obj02159094;
struct Struct021596f0;
void CallFunc0204c804OnMatchingKey(Obj2081*, int);
short FindMappedMemberId02080468(void*, int);
void SetElementFlag0x40(Obj2081*, int, int);
extern "C" void func_020813ec(void*, int);
void SetEntryLowNibbleAndElement02080c68(void*, int, int);
void CalcField389_0215951c(Obj0215951c*);
void ClearSublistEntriesFlag4(void*, int);
extern "C" void func_ov006_0215f4dc(AlchemyMenu*);
void ClearFlagsForIds_021573c8(void*);
extern "C" void func_ov006_021553bc(void*, short*, unsigned char*);
void ResetWithSub0208203c(Obj0208203c*);
extern "C" void func_ov006_02155710(void*, int, int);
extern "C" int func_ov006_021595b4(AlchemyMenu*);
extern "C" unsigned char func_ov006_02158a28(AlchemyMenu*);
extern "C" unsigned char func_ov006_02158b78(AlchemyMenu*);
void DispatchWithShortB4_0205eaa0(Obj0205eaa0*, int, int);
extern "C" int func_ov006_02159218(AlchemyMenu*);
void ExpireStatusSlot02159094(Obj02159094*);
void ClearField44IfSet_02158c28(StructC28*);
extern "C" void func_ov006_0215943c(AlchemyMenu*);
int Check02159564(void*);
extern "C" void func_ov006_02159274(AlchemyMenu*, unsigned char*, short*, unsigned char*);
void UpdateEntryFlags021596f0(Struct021596f0*);
extern "C" int func_ov006_02159834(AlchemyMenu*);
int TestFlag0SetAndFlag1Clear(unsigned short*, int);
extern "C" void func_ov006_02159108(AlchemyMenu*, int, int, int);
extern "C" Obj0205eaa0 data_02108760;
extern "C" unsigned short data_02114e30[];

static inline unsigned char GetCategory(AlchemyMenu* self) { SDK_NULL_ASSERT(self); return self->category_; }

static inline unsigned char GetCount(AlchemyMenu* self) { SDK_NULL_ASSERT(self); return self->count_; }

extern "C" int func_ov006_021570fc(AlchemyPot*, int);
extern "C" void func_ov006_02159db0(AlchemyMenu*);
extern "C" signed char func_ov006_02159e50(AlchemyMenu*);

// USA: func_ov006_0215c680
extern "C" ARM void func_ov006_0215c680(AlchemyMenu* self) {
    Obj2081* menu = self->menu_;
    if (self->step_ == 0) {
        CallFunc0204c804OnMatchingKey(menu, 0);
        CallFunc0204c804OnMatchingKey(menu, 1);
        self->group_ = 0x10;
        if (self->categoryCursor_ < 0)
            self->categoryCursor_ = FindMappedMemberId02080468(menu, self->group_);
        SetElementFlag0x40(menu, self->group_, 0);
        func_020813ec(menu, self->group_);
        SetEntryLowNibbleAndElement02080c68(menu, self->group_, 0);
        self->item_ = -1;
        self->count_ = 0;
        CalcField389_0215951c((Obj0215951c*)self);
        SetElementFlag0x40(menu, 0x11, 0);
        ClearSublistEntriesFlag4(menu, 0x11);
        func_ov006_0215f4dc(self);
        self->flags_ |= 0x10;
        self->flags_ |= 0x20;
        SetEntryLowNibbleAndElement02080c68(menu, 0x11, 1);
        ClearFlagsForIds_021573c8(self->layout_);
        func_ov006_021553bc(self->pot_, self->chosenItems_, self->chosenCounts_);
        ResetWithSub0208203c(&self->repeat_);
        self->cursor_ = 0;
        AlchemyPot* pot = self->pot_;
        func_ov006_02155710(pot, -1, 0);
        self->step_++;
    } else if (self->step_ == 1) {
        if (func_ov006_021595b4(self))
            return;
        self->cursor_ = &self->categoryCursor_;
        if (self->previousCursor_ != *self->cursor_) {
            CalcField389_0215951c((Obj0215951c*)self);
            func_ov006_0215f4dc(self);
        }
        if (func_ov006_02158a28(self)) {
            DispatchWithShortB4_0205eaa0(&data_02108760, 1, 0);
            ResetWithSub0208203c(&self->repeat_);
            self->cursor_ = 0;
            if (func_ov006_02159218(self)) {
                SetEntryLowNibbleAndElement02080c68(menu, self->group_, 1);
                SetElementFlag0x40(menu, self->group_, 1);
                SetEntryLowNibbleAndElement02080c68(menu, 0x11, 0);
                self->step_++;
            }
        } else {
            if (func_ov006_02158b78(self)) {
                ResetWithSub0208203c(&self->repeat_);
                self->cursor_ = 0;
                self->state_ = 6;
                self->step_ = 0;
                ExpireStatusSlot02159094((Obj02159094*)self);
                func_ov006_021553bc(self->pot_, self->chosenItems_, self->chosenCounts_);
                func_ov006_0215f4dc(self);
            }
            ClearField44IfSet_02158c28((StructC28*)self);
        }
    } else if (self->step_ == 2) {
        func_ov006_0215943c(self);
        func_ov006_021553bc(self->pot_, self->chosenItems_, self->chosenCounts_);
        self->step_++;
    } else if (self->step_ == 3) {
        if (Check02159564(self))
            return;
        if (func_ov006_02158a28(self) && self->previousCursor_ == *self->cursor_) {
            unsigned char category;
            unsigned char count;
            count = 0;
            category = 0;
            short item = 0;
            func_ov006_02159274(self, &category, &item, &count);
            if (count) {
                DispatchWithShortB4_0205eaa0(&data_02108760, 1, 0);
                ResetWithSub0208203c(&self->repeat_);
                self->cursor_ = 0;
                SetElementFlag0x40(self->menu_, 0x11, 1);
                self->category_ = category;
                self->item_ = item;
                self->count_ = 1;
                self->step_++;
                self->flags_ &= ~0x10;
                self->flags_ |= 0x20;
                self->message_ = 9;
                self->messageStep_ = 0;
                return;
            }
        } else if (func_ov006_02158b78(self)) {
            ResetWithSub0208203c(&self->repeat_);
            self->cursor_ = 0;
            self->itemCursor_ = -1;
            self->step_ = 0;
        }
        ClearField44IfSet_02158c28((StructC28*)self);
    } else if (self->step_ == 4) {
        UpdateEntryFlags021596f0((Struct021596f0*)self);
        self->repeatDelay_ = 0;
        self->step_++;
    } else if (self->step_ == 5) {
        self->arrowTimer_ = 0;
        int result = func_ov006_02159834(self);
        if (result == 1)
            return;
        if (TestFlag0SetAndFlag1Clear(data_02114e30, 1) || result == 2) {
            DispatchWithShortB4_0205eaa0(&data_02108760, 1, 0);
            ResetWithSub0208203c(&self->repeat_);
            self->cursor_ = 0;
            self->flags_ &= ~8;
            CallFunc0204c804OnMatchingKey(menu, 6);
            func_ov006_02159108(self, self->category_, self->item_, self->count_);
            func_ov006_021553bc(self->pot_, self->chosenItems_, self->chosenCounts_);
            self->step_++;
            self->flags_ |= 0x20;
            self->message_ = 0xa;
            self->messageStep_ = 0;
        } else if (func_ov006_02158b78(self) || result == 3) {
            ResetWithSub0208203c(&self->repeat_);
            self->cursor_ = 0;
            self->flags_ &= ~8;
            CallFunc0204c804OnMatchingKey(menu, 6);
            self->step_ = 0;
            self->message_ = 0x24;
            self->messageStep_ = 0;
            self->flags_ |= 0x120;
        }
    } else if (self->step_ == 6) {
        func_ov006_021570fc(self->pot_, 1);
        func_ov006_02159db0(self);
        self->step_++;
    } else if (self->step_ == 7) {
        int r = func_ov006_02159e50(self);
        if (r != -1) {
            if (r == 1) {
                self->state_ = 8;
                self->showResult_ = 0;
                self->step_ = 0;
            }
        } else {
            while (self->chosenItems_[0] > 0)
                ExpireStatusSlot02159094((Obj02159094*)self);
            func_ov006_021553bc(self->pot_, self->chosenItems_, self->chosenCounts_);
            self->state_ = 5;
            self->step_ = 0;
            self->flags_ |= 0x20;
            self->message_ = 0x24;
            self->messageStep_ = 0;
            self->flags_ |= 0x100;
        }
    }
}
