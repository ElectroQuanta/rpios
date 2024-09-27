/*
 * void memzero( unsigned long src, unsigned int n) ;
 * void memzero( u64 src, u32 n);
 * x0: src
 * x1: n bytes to zero
 */

.globl memzero /* Declare 'memzero' as a global symbol. */
memzero:
    str xzr, [x0], #8 /* Store zero (xzr) at the address in x0, then post-increment x0 by 8 bytes. */
    subs x1, x1, #8 /* Subtract 8 from x1 and set condition flags (for comparison). */
    b.gt memzero  /* Branch back to 'memzero' if x1 (remaining bytes) > 0. */
    ret           /* Return from the function. */
    
