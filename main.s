        .gba
        .thumb
        .open "BPRE0.gba","build/rom.gba", 0x08000000

        .include "hooks/pointer.s"
        
        .org 0x08800000
        .importobj "build/linked.o"
        .close
