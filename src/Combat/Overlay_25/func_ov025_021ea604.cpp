#include <globaldefs.h>
#include "GameState/GameState.h"

struct ListNode021600f8 {
    char pad0[0xc];
    short actorId;
    short ids[1];
};

struct List021600f8 {
    unsigned short type;
    char pad2[7];
    unsigned char count;
    char padA[2];
    unsigned char flag0 : 1;
    unsigned char flag1 : 1;
    unsigned char flag2 : 1;
    unsigned char flag3 : 1;
    unsigned char flag4 : 1;
    unsigned char flags5 : 3;
};

struct Command021ea604 {
    unsigned short type;
    char pad2[2];
    Command021ea604* next;
};

struct Event021ea604 {
    char pad0[8];
    Command021ea604* commands;
};

struct Combatant021ea604 {
    char pad0[0x138];
    struct {
        char pad0[0x28];
        short actorId;
    }* info;
};

struct ActionDisplay {
    char pad0[0x5c5];
    unsigned char counter;
    char pad5c6[0x5cc - 0x5c6];
    unsigned char active;
    char pad5cd[3];
    unsigned char blocked;
    unsigned char enabled;
    short queued[9];
    int queuedCount;
    char command[0x738 - 0x5e8];
    unsigned char busy;
    char pad739[0x748 - 0x739];
    unsigned short timer;
};

void* GetActiveCombatWork();
extern "C" List021600f8* _Z18GetSlotPtr02160f20Pv(void*);
extern "C" ListNode021600f8* _Z22GetNodeAtIndex021600f8P12List021600f8i(List021600f8*, int);
extern "C" short func_ov000_0215ffa0(ListNode021600f8*);
extern "C" int func_ov000_0215fd90(void* entry, int effect);
extern "C" void _Z20ResetFields_021ed35cPc(char*);
extern "C" void func_ov025_021ea958(ActionDisplay*, bool, bool, short);
extern "C" void func_ov025_021ed380(void*, unsigned short, short, int, void*, int, int);
extern "C" void func_ov025_021ead5c(ActionDisplay*, bool);

static inline int IsPartyMember(int id) {
    return id >= 0 && id <= 3;
}

// USA: func_ov025_021ea604
extern "C" ARM void func_ov025_021ea604(ActionDisplay* self, int index, int category, Event021ea604* event) {
    GameState* gs = GameState::GetInstance();
    List021600f8* list = _Z18GetSlotPtr02160f20Pv(GetActiveCombatWork());
    ListNode021600f8* node = _Z22GetNodeAtIndex021600f8P12List021600f8i(list, index);
    int last = 0;
    if (self->blocked) {
        int partyFlag = 0;
        bool lastOfSide = true;
        if (node->ids[0] >= 0 && node->ids[0] <= 3) {
            partyFlag = 1;
        }
        bool party = partyFlag;
        for (int i = index + 1; i < list->count; i++) {
            ListNode021600f8* next = _Z22GetNodeAtIndex021600f8P12List021600f8i(list, i);
            int otherFlag = 0;
            if (next->ids[0] >= 0 && next->ids[0] <= 3) {
                otherFlag = 1;
            }
            bool other = otherFlag;
            if ((party && other) || (!party && !other)) {
                lastOfSide = false;
                break;
            }
        }
        for (Command021ea604* c = event->commands; c != NULL; c = c->next) {
            if (c->type == 8) {
                self->queued[self->queuedCount] = func_ov000_0215ffa0(node);
                self->queuedCount++;
                c->type = 0;
            }
        }
        if (lastOfSide) {
            last = 1;
            self->enabled = 1;
        }
    }
    if (node != NULL) {
        int actor = func_ov000_0215ffa0(node);
        if (event == NULL) {
            return;
        }
        if (func_ov000_0215fd90(event, 0xb)) {
            Combatant021ea604* c = (Combatant021ea604*)gs->GetCombatantByIndex(node->ids[0]);
            if (c != NULL) {
                actor = c->info->actorId;
            }
        }
        if (list->type == 0x399) {
            actor = node->actorId;
        }
        int canReset = 0;
        if (!self->busy && self->timer < 500 && !self->active) {
            canReset = 1;
        }
        bool ok = true;
        if (IsPartyMember(actor) && list->flag0 && !func_ov000_0215fd90(event, 1)) {
            ok = false;
        }
        else if (!IsPartyMember(actor) && list->flag3 && !func_ov000_0215fd90(event, 1)) {
            ok = false;
        }
        if (ok && canReset) {
            _Z20ResetFields_021ed35cPc(self->command);
        }
        if (ok || last) {
            bool isLast = false;
            if (last) {
                isLast = true;
            }
            short id = actor;
            if (last) {
                id = -2;
            }
            func_ov025_021ea958(self, IsPartyMember(actor), isLast, id);
        }
        for (Command021ea604* c = event->commands; c != NULL; c = c->next) {
            func_ov025_021ed380(self->command, c->type, actor, 1, event, -1, 0);
        }
        if (self->active && func_ov000_0215fd90(event, 2)) {
            func_ov025_021ead5c(self, IsPartyMember(actor));
        }
    }
    self->counter++;
}
