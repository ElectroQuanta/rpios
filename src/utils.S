/* void delay(u64 ticks); */
/* x0: nr of ticks */
.globl delay /* make it a global symbol to allow access by external files */
delay:
    subs x0, x0, #1 /* decrement the value passed in (in x0) */
    bne delay /* loop until 0 */
    ret

/* void put32(u64 addr, u32 val); */
/* x0: addr (u64) */
/* w1: val (u32) */
.globl put32 /* make it a global symbol to allow access by external files */
put32:
    str w1, [x0] /* store the value at the addr pointed by x0 */
    ret

/* u32 get32(u64 address); */
/* x0: u64 */
/* w0: return value */
.globl get32 /* make it a global symbol to allow access by external files */
get32:
    ldr w0, [x0] /* load the value (to w0) from the addr pointed by x0 */
    ret
