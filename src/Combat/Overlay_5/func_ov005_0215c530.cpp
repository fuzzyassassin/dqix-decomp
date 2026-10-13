#include <globaldefs.h>
#include <GameState/GameState.h>
#include <Resource/GameResources.h>
#include <std_library_functions.h>

struct Obj0205eaa0;
struct StructDE1D4;

struct SortNode {
    SortNode* next_;
    int unk_4;
    short item_;
};

struct Requirements {
    unsigned int unk_0 : 7;
    unsigned int category : 4;
    unsigned int : 18;
    unsigned int protagonistOnly : 1;
    unsigned int rank : 2;
    unsigned int classMask : 12;
    unsigned int : 15;
    unsigned int allowFirst : 1;
    unsigned int allowSecond : 1;
    unsigned int restricted : 1;
    unsigned int : 2;
    int unk_8[6];
};

struct ItemEntry {
    Requirements* requirements;
    int unk_4;
    unsigned int kind : 4;
    unsigned int : 28;
    char unk_c[0xc];
    short count;
    short unk_1a[3];
};

struct ItemData {
    short id;
    unsigned short kind : 4;
    unsigned short : 12;
    unsigned int unk_0 : 7;
    unsigned int category : 4;
    unsigned int classMask : 12;
    unsigned int protagonistOnly : 1;
    unsigned int rank : 2;
    unsigned int allowFirst : 1;
    unsigned int allowSecond : 1;
    unsigned int restricted : 1;
    unsigned int : 3;
};

struct MemberScreen {
    char unk_0[0x4fc];
    int member_;
};

struct EquipmentSlot {
    short item_;
    char unk_2[0x1c - 2];
};

struct MenuScene {
    char unk_0[0x1000];
    char view_[4];
};

struct EquipmentMenu {
    char unk_0[0x1244];
    char view_[0x19e0 - 0x1244];
    SortNode* sortList_;
    char unk_19e4[0x19ec - 0x19e4];
    char itemTable_[0x19f4 - 0x19ec];
    char cursor_[0x2d90 - 0x19f4];
    EquipmentSlot slots_[24];
    char unk_3030[0x3d98 - 0x3030];
    short itemCounts_[8];
    unsigned char unk_3da8;
    unsigned char equippedStep_;
    unsigned char pageStep_;
    char unk_3dab[0x3db8 - 0x3dab];
    unsigned char state_;
    unsigned char lastState_;
    unsigned char step_;
    signed char slot_;
    unsigned char kind_;
    signed char page_;
    unsigned char unk_3dbe;
    signed char lastPage_;
    char unk_3dc0[0x3dcc - 0x3dc0];
    unsigned int flags_;
    char unk_3dd0[0x3dd4 - 0x3dd0];
    unsigned char sortModes_[8];

    MenuScene* GetScene() { return (MenuScene*)((char*)this + 0x244); }
};

extern "C" void* _Z17GetPtrField0x2a04P9GameState(GameState* gs);
short* GetPointerFromArray0xbd0(unsigned char* obj, unsigned int index);
signed char* GetPointerAt0xbf0(void* obj, unsigned int index);
extern "C" int _Z15Compact0207c51cPhi(unsigned char* base, int key);
extern "C" void _Z22ClearElements_021e1518Pv(void* obj);
extern "C" void _Z19BuildChain_021e1b5cPviii(void* a, int b, int c, int d);
extern "C" void _Z19BuildChain_021e1b0cPviii(void* a, int b, int c, int d);
extern "C" MemberScreen* _Z19GetField1c_021a193cPi(int* p);
extern "C" void _Z18InitStruct020de1d4P11StructDE1D4(StructDE1D4* p);
extern "C" void* _Z22FindEntryById_021db08cPvi(void* obj, int val);
extern "C" int func_020dd4c4(int id, ItemEntry* entry);
extern "C" void func_ov005_021579ec(EquipmentMenu* self, unsigned int state, unsigned char slot);
extern "C" void func_0205bb04(void* cursor, int index);
extern "C" void _Z28DispatchWithShortB4_0205eaa0P11Obj0205eaa0ii(Obj0205eaa0* obj, int a, int b);
extern "C" void func_ov005_021555c0(EquipmentMenu* self);
extern "C" void func_ov023_021dcae0(void* obj, int val);
extern "C" void func_ov005_0215792c(EquipmentMenu* self, unsigned char state);

extern "C" unsigned char data_ov005_0215cd08[8];
extern "C" unsigned char data_ov005_0215cd00[8];
extern int data_02108760;

// USA: func_ov005_0215c530
extern "C" ARM void func_ov005_0215c530(EquipmentMenu* self) {
    char* party = (char*)_Z17GetPtrField0x2a04P9GameState(GameState::GetInstance());
    int count = self->itemCounts_[self->kind_];
    short* items = GetPointerFromArray0xbd0((unsigned char*)(party + 0x1d4), data_ov005_0215cd08[self->kind_]);
    signed char* nums = GetPointerAt0xbf0(party + 0x1d4, data_ov005_0215cd08[self->kind_]);
    _Z15Compact0207c51cPhi((unsigned char*)(party + 0x1d4), data_ov005_0215cd00[self->kind_]);
    int sorted = 0;
    int byEquip = 0;
    if (self->sortModes_[self->kind_] == 0 || self->sortModes_[self->kind_] == 1) {
        _Z22ClearElements_021e1518Pv(&self->sortList_);
        _Z19BuildChain_021e1b5cPviii(&self->sortList_, -1, data_ov005_0215cd00[self->kind_], -1);
        sorted = 1;
    } else if (self->sortModes_[self->kind_] == 3) {
        _Z22ClearElements_021e1518Pv(&self->sortList_);
        _Z19BuildChain_021e1b0cPviii(&self->sortList_, -1, data_ov005_0215cd00[self->kind_], -1);
        sorted = 1;
    } else if (self->sortModes_[self->kind_] == 2) {
        byEquip = 1;
        sorted = 1;
    }
    if (sorted) {
        short current = self->slots_[self->slot_].item_;
        short newItems[0x110];
        signed char newNums[0x110];
        ItemEntry entry;
        Requirements requirements;
        for (int i = 0; i < 0x110; i++) {
            newItems[i] = -1;
            newNums[i] = 0;
        }
        if (!byEquip) {
            SortNode* node = self->sortList_;
            int n = 0;
            while (node != NULL) {
                for (int i = 0; i < count; i++) {
                    short item = items[i];
                    if (node->item_ == item) {
                        newItems[n] = item;
                        newNums[n] = nums[i];
                        n++;
                        node = node->next_;
                        break;
                    }
                    if (i == count - 1)
                        node = node->next_;
                }
            }
        } else {
            signed char member = _Z19GetField1c_021a193cPi((int*)func_ov017_0218b5b0()->unknown_ptr_array_36fc[3])->member_;
            _Z18InitStruct020de1d4P11StructDE1D4((StructDE1D4*)&entry);
            memset(&requirements, 0, sizeof(requirements));
            entry.requirements = &requirements;
            int n = 0;
            int rest = 0;
            for (int i = 0; i < count; i++) {
                short id = items[i];
                if (id > 0) {
                    _Z18InitStruct020de1d4P11StructDE1D4((StructDE1D4*)&entry);
                    memset(&requirements, 0, sizeof(requirements));
                    entry.requirements = &requirements;
                    ItemData* data = (ItemData*)_Z22FindEntryById_021db08cPvi(self->itemTable_, id);
                    if (data != NULL) {
                        entry.count = data->id;
                        entry.kind = data->kind;
                        requirements.unk_0 = data->unk_0;
                        requirements.category = data->category;
                        requirements.classMask = data->classMask;
                        requirements.protagonistOnly = data->protagonistOnly;
                        requirements.rank = data->rank;
                        requirements.allowFirst = data->allowFirst;
                        requirements.allowSecond = data->allowSecond;
                        requirements.restricted = data->restricted;
                    }
                    if (func_020dd4c4(member, &entry) == 0) {
                        newItems[n] = items[i];
                        newNums[n] = nums[i];
                        n++;
                        items[i] = -1;
                        nums[i] = 0;
                    } else {
                        rest++;
                    }
                }
            }
            _Z15Compact0207c51cPhi((unsigned char*)(party + 0x1d4), data_ov005_0215cd00[self->kind_]);
            memcpy(&newItems[n], items, rest * 2);
            memcpy(&newNums[n], nums, rest);
        }
        memcpy(items, newItems, count * 2);
        memcpy(nums, newNums, count);
        if (self->slot_ >= 8 && self->slot_ < 0x18) {
            int index = -1;
            for (int i = 0; i < count; i++) {
                if (current == items[i]) {
                    index = (short)i;
                    break;
                }
            }
            if (index >= 0) {
                self->lastPage_ = self->page_;
                self->page_ = index / 16;
                signed char slot = self->slot_;
                self->slot_ = index % 16 + 8;
                if (slot != self->slot_) {
                    func_ov005_021579ec(self, 4, self->slot_);
                    func_0205bb04(self->cursor_, self->slot_ - 8);
                }
            }
        }
        _Z28DispatchWithShortB4_0205eaa0P11Obj0205eaa0ii((Obj0205eaa0*)&data_02108760, 1, 0);
    }
    if (self->sortModes_[self->kind_] == 0 || self->sortModes_[self->kind_] == 1) {
        self->sortModes_[self->kind_] = 3;
        self->flags_ |= 0x800;
    } else if (self->sortModes_[self->kind_] == 3) {
        self->sortModes_[self->kind_] = 2;
        self->flags_ |= 0x800;
    } else if (self->sortModes_[self->kind_] == 2) {
        self->sortModes_[self->kind_] = 1;
        self->flags_ |= 0x800;
    }
    func_ov005_021555c0(self);
    func_ov023_021dcae0(self->GetScene()->view_, self->slots_[self->slot_].item_);
    self->flags_ |= 0x40;
    self->pageStep_ = 0;
    func_ov005_0215792c(self, self->lastState_);
}
