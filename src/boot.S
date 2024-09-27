#include "mm.h"

.section ".text.boot"

.global _start
_start: 
    mrs x0, mpidr_el1 /* get CPU ID into x0 */
    and x0, x0, #0xFF /* and it with 0xFF */
    cbz x0, master /* if CPU_ID == 0, we branch to master */
    b proc_hang /* else we branch to proc_hang (hanging the processor) */

master: 
    adr x0, bss_begin /* addr of BSS_BEGIN */
    adr x1, bss_end /* addr of BSS_END */
    sub x1, x1, x0 /* get the size of BSS = BSS_END - BSS_BEGIN */
    bl memzero /* zero it: memzero x0 x1 */

    mov sp, #LOW_MEMORY /* set the SP to #LOW_MEMORY */
    bl kernel_main /* jump to kernel_main */
    b proc_hang /* hang the processor if we ever leave kernel_main */

proc_hang:  
    wfe /* wait for event */
    b proc_hang
