#include <globaldefs.h>
#include "World/ZoneWarpScript.h"

#pragma define_section initcode ".init" RX

extern float data_020ef378[8];

// USA: func_020e5a74
extern "C" __declspec(initcode) ARM void __sinit_020e5a74(void) {
    float t;
    float a;
    float b;
    data_020fdc20.accumulatedValues[4] = data_020ef378[1] + (data_020ef378[2] + (data_020ef378[0] + data_020ef378[3]));
    t = data_020fdc20.accumulatedValues[3] + data_020ef378[0];
    a = data_020ef378[3];
    data_020fdc20.accumulatedValues[2] = t;
    t = t + a;
    b = data_020ef378[2];
    data_020fdc20.accumulatedValues[1] = t;
    t = t + b;
    data_020fdc20.accumulatedValues[0] = t;
}
