#include <globaldefs.h>
#include "GameState/GameState.h"

struct Random;

struct CombatantSleep {
    char unk0[0x3c];
    unsigned char unk3c_0 : 6;
    unsigned char autoAct : 1;
    unsigned char unk3c_7 : 1;
    char unk3d[0x7f - 0x3d];
    unsigned char turns7f;
    unsigned char turns80;
    unsigned char turns81;
};

struct ActionNode {
    unsigned short action;
    char unk2[7];
    unsigned char targetCount;
    char unka;
    unsigned char flag : 1;
    unsigned char other : 7;
};

#define SLEEP(combatant) ((struct CombatantSleep*)(combatant)->currentStats_)

extern float data_ov000_02182ad4[];
extern float data_ov000_02182bd4[];

int NextRandomMax(struct Random* random, int max);
int IsFlag0x14Bit0x8Set(GameObject* combatant);
void ClearFlag0x14Bit0x8AndBytes(void* stats);
int CheckFlag0x14Bit0x10Set(unsigned char* stats);
void ClearBattleFlag0x14Bit4(void* stats);
int IsFlag0x14Bit0x20Set(GameObject* combatant);
void ClearFlag0x20AndBytes(void* stats);

// USA: func_ov000_0215833c
extern "C" ARM int func_ov000_0215833c(struct Random* random, int index, ActionNode* node) {
    unsigned char* turns;
    GameObject* combatant = GameState::GetInstance()->GetCombatantByIndex(index);
    if (combatant == 0) {
        return 0;
    }
    if (SLEEP(combatant)->autoAct) {
        node->flag = 1;
    }
    float r = (float)NextRandomMax(random, 100) / 100.0f;
    turns = &SLEEP(combatant)->turns7f;

    if (IsFlag0x14Bit0x8Set(combatant)) {
        if (turns[0] != 0) {
            int remaining = turns[0] - 1;
            float chance = data_ov000_02182ad4[remaining & 0xff];
            turns[0] = remaining;
            if (chance > r) {
                turns[0] = 0;
                ClearFlag0x14Bit0x8AndBytes(combatant->currentStats_);
                node->action = 0x384;
                node->targetCount = 0;
                return 1;
            }
        }
    } else if (CheckFlag0x14Bit0x10Set((unsigned char*)combatant->currentStats_)) {
        if (turns[1] != 0) {
            int remaining = turns[1] - 1;
            float chance = data_ov000_02182bd4[remaining & 0xff];
            turns[1] = remaining;
            if (chance > r) {
                turns[1] = 0;
                ClearBattleFlag0x14Bit4(combatant->currentStats_);
                node->action = 0x385;
                node->targetCount = 0;
                return 1;
            }
        }
    } else if (IsFlag0x14Bit0x20Set(combatant) && turns[2] != 0) {
        int remaining = turns[2] - 1;
        float chance = data_ov000_02182ad4[remaining & 0xff];
        turns[2] = remaining;
        if (chance > r) {
            turns[2] = 0;
            ClearFlag0x20AndBytes(combatant->currentStats_);
            node->action = 0x3aa;
            node->targetCount = 0;
            return 1;
        }
    }
    return 0;
}
