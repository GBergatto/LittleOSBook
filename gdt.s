global load_gdt
global load_segment_registers

load_gdt:
    lgdt [esp + 4]
    ret

load_segment_registers:
    mov ax, 0x10 ; kernel data segment
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    jmp 0x08:flush_cs ; 0x08: kernel code segment

flush_cs:
    ret
