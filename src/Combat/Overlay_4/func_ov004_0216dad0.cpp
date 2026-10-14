#include <globaldefs.h>
#include "GameState/GameState.h"

void SetByte0x7f70(void* obj, unsigned char value);
int CheckSaveBufferStatus(int flag);

extern "C" int func_020ab5d4(void* buf, int a, int b, void* out);

struct State_0216dad0 {
    unsigned char mode;
    unsigned char f1;
    unsigned char f2;
    unsigned char status;
    unsigned char f4;
    unsigned char f5;
    unsigned char b6;
    unsigned char b7;
    unsigned short id;
    unsigned char pada[2];
    void* fc;
    void* buf;
};
extern State_0216dad0 data_ov004_02171034;

// USA: func_ov004_0216dad0
extern "C" ARM int func_ov004_0216dad0(void) {
    GameState* gs = GameState::GetInstance();
    SetByte0x7f70(gs, 1);
    data_ov004_02171034.status = 0;
    data_ov004_02171034.mode = 0;
    int s0 = CheckSaveBufferStatus(0);
    int s1 = CheckSaveBufferStatus(1);
    if (s0 == 1 || s1 == 1) {
        data_ov004_02171034.status = 6;
        return 0;
    }
    if (s1 == 4) {
        data_ov004_02171034.status = 0;
        if (s0 == 3) {
            data_ov004_02171034.mode = 1;
        }
        return 0;
    }
    if (s1 == 2) {
        data_ov004_02171034.status = 7;
        return 0;
    }
    if (s0 == 2) {
        data_ov004_02171034.status = 4;
        return 0;
    }
    if (s0 == 0) {
        data_ov004_02171034.status = 1;
    } else if (s0 == 3) {
        data_ov004_02171034.status = 2;
    }
    if (data_ov004_02171034.status == 1) {
        // the callee writes 4 bytes (u16 id, u8, u8); the 3-byte declaration is what
        // makes the info[3] read alias the global stores, as in the ROM
        unsigned char info[3];
        if (func_020ab5d4(data_ov004_02171034.buf, 0, 0, info) == 0) {
            unsigned char v = *((unsigned char*)gs + 0x5cc8);
            if (v == 0) {
                data_ov004_02171034.status = 6;
            } else if (v == 2) {
                data_ov004_02171034.status = 4;
            }
            return 0;
        }
        data_ov004_02171034.id = *(unsigned short*)info;
        data_ov004_02171034.b7 = info[2];
        data_ov004_02171034.b6 = info[3];
    }
    return 0;
}
