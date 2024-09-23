#pragma once

#if RPI_VERSION == 3
// PBASE: Peripheral Base (see bcm2836 datasheet)
#define PBASE = 0x3F000000

#elif RPI_VERSION == 4
// PBASE: Peripheral Base (see bcm2711 datasheet)
// bcm2711.dtsi
// soc { ranges = <0x7e000000  0x0 0xfe000000  0x01800000>,
#define PBASE = 0xFE000000

#else
#define PBASE 0
#error RPI_VERSION NOT defined

#endif
