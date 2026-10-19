#include <globaldefs.h>
#include "Input/Input.h"

#pragma define_section initcode ".init" RX

extern "C" KeyManager* _ZN10KeyManagerC1Ev(KeyManager* self);
extern "C" KeyManager* _ZN10KeyManagerD1Ev(KeyManager* self);
void BlankFunction02012530(void*);
void EmptyStub02012534(void);
void ClearField0x0_02046724(int* field);
extern "C" void __register_global_object(void* obj, void* func, void* node);

extern unsigned char data_02114e54[];
extern int data_02114e04;
extern int data_02114e08;
extern int data_02114e14;

// KEEP-NAME: the ROM symbol here is the mangled C++ name, not a func_ tag.
// USA: func_020e66a0
extern "C" __declspec(initcode) ARM void __sinit_020e66a0(void) {
    _ZN10KeyManagerC1Ev(&g_keyManager);
    __register_global_object(&g_keyManager, (void*)_ZN10KeyManagerD1Ev, &data_02114e14);
    BlankFunction02012530(data_02114e54);
    __register_global_object(data_02114e54, (void*)EmptyStub02012534, &data_02114e08);
    ClearField0x0_02046724(&data_02114e04);
}
