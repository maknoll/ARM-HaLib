OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(__start)

MEMORY
{
	FLASH (rx) : ORIGIN = 0x00400000, LENGTH = 256k
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 48k
}

SECTIONS
{
    .text : AT(ORIGIN(FLASH))
    {
        KEEP(*(.tos))
        *(.tos)
        KEEP(*(.vectors))
        *(.vectors)
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;
        __fini_array_start = .;
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array))
        __fini_array_end = .;
        __start = .;
        KEEP(*(.init))
        *(.init)
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
    }

	.data : AT(ADDR(.text) + SIZEOF(.text))
	{
        . = ALIGN(4);
		__data_start = .;
		*(.data)
        *(.data*)
        . = ALIGN(4);
		__data_end = .;
	} > SRAM

	.bss (NOLOAD):
	{
        . = ALIGN(4);
        __bss_start = .;
		*(.bss)
        *(.bss*)
        . = ALIGN(4);
        __bss_end = .;
	} > SRAM

    __end = ORIGIN(SRAM) + LENGTH(SRAM) - 4;
    __data_load_start = LOADADDR(.data);
    __data_load_end = __data_load_start + SIZEOF(.data);
}
end = .;
