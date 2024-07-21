ENTRY(loader)

SECTIONS {
   /* start loading code at 1MB */
   . = 0x00100000;

   /* align all text sections at 4 KB */
   .text ALIGN (0x1000) :
   {
      *(.text)
   }


   /* align all read-only data sections at 4 KB */
   .rodata ALIGN (0x1000) :
   {
      *(.rodata*)
   }

   /* align all data sections at 4 KB*/
   .data ALIGN (0x1000) :
   {
      *(.data)
   }

   /* align all COMMON and bss sections at 4 KB */
   .bss ALIGN (0x1000) :
   {
      *(COMMON)
      *(.bss)
   }
}
