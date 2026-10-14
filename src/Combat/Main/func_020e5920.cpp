#include <globaldefs.h>

#pragma define_section initcode ".init" RX

extern float data_020ef07c[6] __attribute__((aligned(4)));
extern float data_020f33b4[6];
extern char data_020f33d8[];
extern char data_020f33cc[];

extern "C" void _Z22ClearSubMemberAndResetPc(void* obj);
extern "C" void _Z25ResetAndFinalizeSubMemberPc(void* obj);
extern "C" void __register_global_object(void* obj, void* func, void* node);

// KEEP-NAME: the ROM symbol here is the mangled C++ name, not a func_ tag.
// USA: func_020e5920
extern "C" __declspec(initcode) ARM void __sinit_020e5920(void) {
    float t;
    float a;
    t = data_020ef07c[1] + data_020ef07c[2];
    t = data_020ef07c[0] + t;
    t = data_020ef07c[3] + t;
    data_020f33b4[1] = t;
    t = data_020f33b4[5] + data_020ef07c[1];
    a = data_020ef07c[2];
    data_020f33b4[4] = t;
    t = t + a;
    a = data_020ef07c[0];
    data_020f33b4[3] = t;
    t = t + a;
    data_020f33b4[2] = t;
    _Z22ClearSubMemberAndResetPc((void*)&data_020f33d8);
    __register_global_object((void*)&data_020f33d8, (void*)_Z25ResetAndFinalizeSubMemberPc, (void*)&data_020f33cc);
}
