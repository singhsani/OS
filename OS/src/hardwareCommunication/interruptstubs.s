.set IRQ_BASE,0x80

.extern _ZN2OS21hardwareCommunication16InterruptManager15HandleInterruptEhj



.global _ZN2OS21hardwareCommunication16InterruptManager22IgnoreInterruptRequestEv

#.macro HandleException num 
#.global _ZN2OS21hardwareCommunication16InterruptManager15HandleException\num\()Ev
#_ZN2OS21hardwareCommunication16InterruptManager15HandleException\num\()Ev:
    #movb $\num,(interruptNumber)
    #jmp int_bottom
#.endm

.macro HandleInterruptRequest num 
.global _ZN2OS21hardwareCommunication16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN2OS21hardwareCommunication16InterruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE,(interruptNumber)
    jmp int_bottom
.endm

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
HandleInterruptRequest 0x02
HandleInterruptRequest 0x03
HandleInterruptRequest 0x04
HandleInterruptRequest 0x05
HandleInterruptRequest 0x06
HandleInterruptRequest 0x07
HandleInterruptRequest 0x08
HandleInterruptRequest 0x09
HandleInterruptRequest 0x0A
HandleInterruptRequest 0x0B
HandleInterruptRequest 0x0C
HandleInterruptRequest 0x0D
HandleInterruptRequest 0x0E
HandleInterruptRequest 0x0F
HandleInterruptRequest 0x31

#HandleException 0x00
#HandleException 0x01
#HandleException 0x02
#HandleException 0x03
#HandleException 0x04
#HandleException 0x05
#HandleException 0x06
#HandleException 0x07
#HandleException 0x08
#HandleException 0x09
#HandleException 0x0A
#HandleException 0x0B
#HandleException 0x0C
#HandleException 0x0D
#HandleException 0x0E
#HandleException 0x0F
#HandleException 0x10
#HandleException 0x11
#HandleException 0x12
#HandleException 0x13

int_bottom:
    pusha 
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs
    
    pushl %esp
    push (interruptNumber)
    call _ZN2OS21hardwareCommunication16InterruptManager15HandleInterruptEhj
    movl %eax, %esp
    
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa
.global _ZN2OS21hardwareCommunication16InterruptManager22IgnoreInterruptRequestEv
_ZN2OS21hardwareCommunication16InterruptManager22IgnoreInterruptRequestEv:
    iret
    
.data
   interruptNumber: .byte 0
   
