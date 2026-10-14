#include <globaldefs.h>
#include "System/Graphics.h"
#include "GameState/GameState.h"

struct Struct0200fb08;
struct Vec3Target0203a46c;

struct GaugeSprite0218251c {
    unsigned char pad0[0x82];
    short alpha;
    unsigned char pad84[0x88 - 0x84];
};

struct GaugeDisplay0218251c {
    GaugeSprite0218251c sprites[13];
    unsigned char level;
    unsigned char subLevel;
    short timer;
    short fade;
};

struct GaugeOrder0218251c {
    unsigned char order[5];
};

extern "C" int _Z24NormalizeField5_0200fb08P14Struct0200fb08(Struct0200fb08* gs);
void SetVec3At0x1c(Vec3Target0203a46c* obj, int x, int y, int z);
extern "C" void func_02047554(GaugeSprite0218251c* obj, int idx, int something);

extern const GaugeOrder0218251c data_ov000_021836d0;
extern const signed char data_ov000_021836d5[][2];
extern const signed char data_ov000_021836d6[][2];

static inline void DrawSprite(GaugeSprite0218251c* sprite) {
    GXFIFO_MATRIX_PUSH = 0;
    func_02047554(sprite, 0, 1);
    GXFIFO_MATRIX_POP = 1;
}

// USA: func_ov000_0218251c
extern "C" ARM void func_ov000_0218251c(GaugeDisplay0218251c* self) {
    int level = self->level;
    int subLevel = self->subLevel;
    if (level <= 0) {
        return;
    }
    int phase = _Z24NormalizeField5_0200fb08P14Struct0200fb08((Struct0200fb08*)GameState::GetInstance()) - 1;
    GaugeOrder0218251c order = data_ov000_021836d0;
    int t = 30 - self->timer;

    if (level > 1 || t >= 0) {
        int x = 0;
        int z = 15;
        if (t < 6) {
            float f = (6 - t) / 6.0f;
            x = (int)(-64.0f * (f * f));
        }
        int x2 = x;
        if (level >= 2) {
            x = 0;
            x2 /= 4;
        }
        int fade = self->fade;
        if (fade > 0 && fade < 5) {
            float f = (5 - fade) / 5.0f;
            int d = (int)(64.0f * (f * f));
            x -= d;
            x2 -= d;
        }

        SetVec3At0x1c((Vec3Target0203a46c*)&self->sprites[3], (x + 2) << 12, 0x1f000, z-- << 12);
        self->sprites[3].alpha = 0x1f;
        DrawSprite(&self->sprites[3]);

        int l = level - 1;

        SetVec3At0x1c((Vec3Target0203a46c*)&self->sprites[l], (x2 + 11) << 12, 0x8000, z-- << 12);
        self->sprites[l].alpha = 0x1f;
        DrawSprite(&self->sprites[l]);

        if (level >= 2 && t < 6) {
            SetVec3At0x1c((Vec3Target0203a46c*)&self->sprites[subLevel - 1], (x + 11) << 12, 0x8000, z-- << 12);
            self->sprites[subLevel - 1].alpha = (6 - t) * 31 / 6;
            if (self->sprites[subLevel - 1].alpha > 0x1f) {
                self->sprites[subLevel - 1].alpha = 0x1f;
            }
            DrawSprite(&self->sprites[subLevel - 1]);
        }

        int w = t - 2;
        int idx = 9;
        if ((level == 3 && t >= 6) || subLevel == 3) {
            idx = 10;
        }
        int y = 0;
        if (w > 0 && w < 6) {
            if (w <= 3) {
                y = -w;
            } else {
                y = w - 6;
            }
        }
        SetVec3At0x1c((Vec3Target0203a46c*)&self->sprites[idx], (x + 28) << 12, (y + 20) << 12, z << 12);
        self->sprites[idx].alpha = 0x1f;
        DrawSprite(&self->sprites[idx]);

        if (phase == 4) {
            int k = 0x1b;
            int j = 11;
            if (idx == 10) {
                k = 0x1c;
                j = 12;
            }
            SetVec3At0x1c((Vec3Target0203a46c*)&self->sprites[j], (x + data_ov000_021836d5[k][0]) << 12,
                          (y + data_ov000_021836d6[k][0]) << 12, (z - 1) << 12);
            self->sprites[j].alpha = 0x1f;
            DrawSprite(&self->sprites[j]);
        }
    }

    int u = t - 5;
    if (level > 1 || u > 0) {
        int x = 0;
        if (u < 6) {
            float f = (6 - u) / 6.0f;
            x = (int)(-64.0f * (f * f));
        }
        int fade = self->fade;
        if (fade > 0 && fade < 5) {
            float f = (5 - fade) / 5.0f;
            x -= (int)(64.0f * (f * f));
        }

        SetVec3At0x1c((Vec3Target0203a46c*)&self->sprites[8], (x + 3) << 12, 0x21000, 0x1000);
        self->sprites[8].alpha = 0x1f;
        DrawSprite(&self->sprites[8]);

        int c = order.order[phase];
        unsigned char k = c + 4;
        SetVec3At0x1c((Vec3Target0203a46c*)&self->sprites[4], (x + data_ov000_021836d5[k][0]) << 12,
                      data_ov000_021836d6[k][0] << 12, 0);
        self->sprites[4].alpha = 0x1f;
        DrawSprite(&self->sprites[4]);

        int slot = level + 4;
        int nextC = c + 5;
        if (level == 3) {
            nextC++;
        }
        SetVec3At0x1c((Vec3Target0203a46c*)&self->sprites[slot], (x + data_ov000_021836d5[nextC][0]) << 12,
                      data_ov000_021836d6[nextC][0] << 12, -0x1000);
        self->sprites[slot].alpha = 0x1f;
        DrawSprite(&self->sprites[slot]);
    }
}
