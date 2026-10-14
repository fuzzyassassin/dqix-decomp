#include <globaldefs.h>

#if defined(jpn)
#define __sinit_020e5920 __sinit_020e61fc
#endif

extern "C" void __sinit_020e5920();
extern "C" char ARM9_INIT_START[];

struct Obj0200f29c { char pad[0xc]; void (*fnC)(void); unsigned int fn10; };

// USA: func_0200f29c
extern "C" ARM int func_0200f29c(struct Obj0200f29c* obj) {
    obj->fnC = __sinit_020e5920;
    obj->fn10 = (unsigned int)ARM9_INIT_START;
    return 1;
}
