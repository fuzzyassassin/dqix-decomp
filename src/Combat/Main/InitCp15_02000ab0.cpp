#include <globaldefs.h>

// USA: func_02000ab0  (semantic: NitroSDK crt0 CP15 / protection-unit setup)
//
// PROVENANCE: called from the crt0 entry (Entry, 0x02000800) before main. It disables the
// protection unit and caches, flushes them, programs the eight MPU regions (c6), the DTCM
// and ITCM windows (c9), the cache/write-buffer and access-permission bits (c2, c3, c5),
// then re-enables the unit. Every step is a coprocessor `mrc`/`mcr p15` access, which C
// cannot express; the NitroSDK writes this routine as an `asm` function, as here.

extern "C" char data_027e0021[];
extern "C" char data_027e0000[];

extern "C" ARM asm void func_02000ab0(void) {
    mrc p15, 0, r0, c1, c0, 0
    ldr r1, =0xf9005
    bic r0, r0, r1
    mcr p15, 0, r0, c1, c0, 0
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0
    mcr p15, 0, r0, c7, c6, 0
    mcr p15, 0, r0, c7, c10, 4
    ldr r0, =0x4000033
    mcr p15, 0, r0, c6, c0, 0
    ldr r0, =0x200002d
    mcr p15, 0, r0, c6, c1, 0
    ldr r0, =data_027e0021
    mcr p15, 0, r0, c6, c2, 0
    ldr r0, =0x8000035
    mcr p15, 0, r0, c6, c3, 0
    ldr r0, =data_027e0000
    orr r0, r0, #0x1a
    orr r0, r0, #1
    mcr p15, 0, r0, c6, c4, 0
    ldr r0, =0x100002f
    mcr p15, 0, r0, c6, c5, 0
    ldr r0, =0xffff001d
    mcr p15, 0, r0, c6, c6, 0
    ldr r0, =0x27ff017
    mcr p15, 0, r0, c6, c7, 0
    mov r0, #0x20
    mcr p15, 0, r0, c9, c1, 1
    ldr r0, =data_027e0000
    orr r0, r0, #0xa
    mcr p15, 0, r0, c9, c1, 0
    mov r0, #0x42
    mcr p15, 0, r0, c2, c0, 1
    mov r0, #0x42
    mcr p15, 0, r0, c2, c0, 0
    mov r0, #2
    mcr p15, 0, r0, c3, c0, 0
    ldr r0, =0x5100011
    mcr p15, 0, r0, c5, c0, 3
    ldr r0, =0x15111011
    mcr p15, 0, r0, c5, c0, 2
    mrc p15, 0, r0, c1, c0, 0
    ldr r1, =0x5707d
    orr r0, r0, r1
    mcr p15, 0, r0, c1, c0, 0
    bx lr
}
