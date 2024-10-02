ENTRY(_start)

SECTIONS
{
	.text.boot : { *(.text.boot) } /* Boot code (defined in boot.S) */
	.text : { *(.text) } /* All other code */
	.rodata : { *(.rodata) } /* Read-only data (constants) */
	.data : { *(.data) } /* initialized data */
	. = ALIGN(0x8); /* Set the location counter to an aligned position */

	bss_begin = .; /* Get the initial address of BSS */
	.bss : { *(.bss*) } /* Uninitialized data */
	bss_end = .; /* Get the initial address of BSS */
}

/* MEMORY */
/* { */
/*     RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 512K */
/*     /\* Define additional memory regions if necessary *\/ */
/*     /\* e.g., ROM for bootloader or other purposes *\/ */
/* } */
/* SECTIONS */
/* { */
/*     /\* Boot Code *\/ */
/*     .text.boot : { */
/*         *(.text.boot) */
/*     } > RAM */

/*     /\* Main Code *\/ */
/*     .text : { */
/*         *(.text) */
/*     } > RAM */

/*     /\* Read-Only Data *\/ */
/*     .rodata : { */
/*         *(.rodata) */
/*     } > RAM */

/*     /\* Initialized Data *\/ */
/*     .data : { */
/*         *(.data) */
/*     } > RAM */

/*     /\* Ensure alignment *\/ */
/*     . = ALIGN(0x8); */

/* /\* We need to determine the initial and end address of the BSS segment  */
/*  * because we need to explicitly clear it in boot.S to prevent  */
/*  * uninitialized data to corrupt our code */
/* *\/ */
/*     /\* BSS Segment *\/ */
/*     bss_begin = .; */
/*     .bss : { */
/*         *(.bss*) */
/*     } > RAM */
/*     bss_end = .; */
/* } */
