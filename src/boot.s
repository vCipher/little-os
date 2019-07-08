/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */
 
/* Declare a multiboot header that marks the program as a kernel. */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
 
/* Allocate memory to stack */
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
 
/* Declare a text section with _start function */
.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp # set up a stack

	call kmain

	/*
	If the system has nothing more to do, put the computer into an
	infinite loop. To do that:
	1) Disable interrupts with cli (clear interrupt enable in eflags).
		They are already disabled by the bootloader, so this is not needed.
		Mind that you might later enable interrupts and return from
		kmain (which is sort of nonsensical to do).
	2) Wait for the next interrupt to arrive with hlt (halt instruction).
		Since they are disabled, this will lock up the computer.
	3) Jump to the hlt instruction if it ever wakes up due to a
		non-maskable interrupt occurring or due to system management mode.
	*/
	cli
1:	hlt
	jmp 1b