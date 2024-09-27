SECTIONS
{
	.text.boot : { *(.text.boot) } /* Boot code (defined in boot.S) */
	.text : { *(.text) } /* All other code */
	.rodata : { *(.rodata) } /* Read-only data (constants) */
	.data : { *(.data) } /* initialized data */
	. = ALIGN(0x8); /* Set the location counter to an aligned position */

/* We need to determine the initial and end address of the BSS segment 
 * because we need to explicitly clear it in boot.S to prevent 
 * uninitialized data to corrupt our code
*/
	bss_begin = .; /* Get the initial address of BSS */
	.bss : { *(.bss*) } /* Uninitialized data */
	bss_end = .; /* Get the initial address of BSS */
}
