
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define EXTERN_ROM extern __attribute__((long_call))

#include "gba_types.h"

EXTERN_ROM void end_intro(void);
EXTERN_ROM void play_sound(u16 sound_num);
EXTERN_ROM void play_song(u16 song_num);
EXTERN_ROM void callback3(void);
EXTERN_ROM void callback_OAM(void);
EXTERN_ROM void write_OAM(void);       
EXTERN_ROM void sub_080704D0(void);
EXTERN_ROM void fadescreen2(u32 bitmask, u32 r1, u32 r2, u32 r3, u32 color);

//EXTERN_ROM u32 __aeabi_uidiv(u32 dividend, u32 divisor);
//EXTERN_ROM u32 __aeabi_uidivmod(u32 dividend, u32 divisor);
EXTERN_ROM void lz77uncompvram(void *src, void *dest);
EXTERN_ROM void lz77uncompwram(void *src, void *dest);


inline void fadescreen()
{
    fadescreen2(0xFFFFFFFF, 0x0, 0x0, 0x10, 0x0000); 
}

inline void unfadescreen()
{
    fadescreen2(0xFFFFFFFF, 0x0, 0x10, 0x0, 0x7FFF); 
}

inline void fadescreen_white()
{
    fadescreen2(0xFFFFFFFF, 0x0, 0x0, 0x10, 0x7FFF);
}

void __attribute((noinline))  copy_pal(void *source, void *dest)
{
	__asm("mov r2, #0x8");
	SystemCall(0xC);
}

#endif /* FUNCTIONS_H */

