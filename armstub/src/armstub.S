/* Armstub 
 * The ARM stub is required to comply with the ARM Linux Boot protocol,
 * which ARM machines must follow to boot a Linux Kernel
 * https://leiradel.github.io/2019/01/20/Raspberry-Pi-Stubs.html
 *
 * based on https://github.com/raspberrypi/tools/blob/master/armstubs/armstub8.S
 *
 */
.globl _start
_start:
    ldr w0, kernel_entry32 /* Load the kernel_entry32 addr to w0*/ 
    br x0 /* Branch to register */

.ltorg /* create a literal pool immediately */

.org 0xf0 /* Change the location counter to 0xf0 */
.globl stub_magic /* required by the bootloader */
stub_magic: 
    .word 0x5afe570b 

.org 0xf4 /* Change the location counter to 0xf4 */
.globl stub_version /* required by the bootloader */
stub_version:   
    .word 0

.org 0xfc 
.globl kernel_entry32 /* Stub entry point */
kernel_entry32: 
    .word 0x0 /* Run the kernel (kernel8-rpi4.img) from the beginning */
