extern kmain

global loader ; the entry symbol for ELF

KERNEL_STACK_SIZE equ 4096    ; size of stack in bytes

MAGIC_NUMBER equ 0x1BADB002   ; define the magic number constant
FLAGS equ 0x0                 ; multiboot flags
CHECKSUM equ -MAGIC_NUMBER    ; calculate the checksum
                              ; (magic number + checksum + flags should equal 0)

; reserve memory for the kernel stack
section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .text:
align 4
   dd MAGIC_NUMBER
   dd FLAGS
   dd CHECKSUM

; point esp to the start of the stack
mov esp, kernel_stack + KERNEL_STACK_SIZE

loader: ; entrypoint in linker script
   mov eax, 0xCAFEBABE

   push dword 3
   push dword 2
   push dword 1
   call kmain

.loop: 
   jmp .loop
