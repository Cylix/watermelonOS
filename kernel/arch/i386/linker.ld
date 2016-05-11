/* Bootloader entry point: _start symbol */
ENTRY(_start)

/* Sections of the object files that will be put in the final kernel image. */
SECTIONS
{
	/* Begin putting sections at 1 MiB, 0x00100000 */
	. = 1M;

	/* Multiboot header comes first so that the bootloader can find it
	   Next we'll put the .text section. */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)

    /* create variable whose address refers to the end of kernel address space */
    end_kernel = .;
	}
}
