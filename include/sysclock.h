#ifndef __SYSCLOCK_H__
#define __SYSCLOCK_H__

#include <easy-pdk/calibrate.h>

#if !defined(F_CPU)
  #error "F_CPU not defined"
#endif

// FREE_PDK_INIT_SYSCLOCK()
#if (F_CPU > 12000000)
  #define FREE_PDK_INIT_SYSCLOCK()              PDK_SET_SYSCLOCK(SYSCLOCK_IHRC_16MHZ)
#elif (F_CPU > 6000000)
  #define FREE_PDK_INIT_SYSCLOCK()              PDK_SET_SYSCLOCK(SYSCLOCK_IHRC_8MHZ)
#elif (F_CPU > 3000000)
  #define FREE_PDK_INIT_SYSCLOCK()              PDK_SET_SYSCLOCK(SYSCLOCK_IHRC_4MHZ)
#elif (F_CPU > 1500000)
  #define FREE_PDK_INIT_SYSCLOCK()              PDK_SET_SYSCLOCK(SYSCLOCK_IHRC_2MHZ)
#elif (F_CPU > 750000)
  #define FREE_PDK_INIT_SYSCLOCK()              PDK_SET_SYSCLOCK(SYSCLOCK_IHRC_1MHZ)
#elif (F_CPU > 375000)
  #define FREE_PDK_INIT_SYSCLOCK()              PDK_SET_SYSCLOCK(SYSCLOCK_IHRC_500KHZ)
#elif (F_CPU > 150000)
  #define FREE_PDK_INIT_SYSCLOCK()              PDK_SET_SYSCLOCK(SYSCLOCK_IHRC_250KHZ)
#elif (F_CPU > ILRC_FREQ/2)
  #define FREE_PDK_INIT_SYSCLOCK()              PDK_SET_SYSCLOCK(SYSCLOCK_ILRC)
#elif (F_CPU > ILRC_FREQ/8)
  #define FREE_PDK_INIT_SYSCLOCK()              PDK_SET_SYSCLOCK(SYSCLOCK_ILRC_DIV2)
#else
  #define FREE_PDK_INIT_SYSCLOCK()              PDK_SET_SYSCLOCK(SYSCLOCK_ILRC_DIV16)
#endif

// FREE_PDK_CALIBRATE_SYSCLOCK(vdd_mv)
#if (F_CPU > 150000)
  #define FREE_PDK_CALIBRATE_SYSCLOCK(vdd_mv)   EASY_PDK_CALIBRATE_IHRC(F_CPU, vdd_mv);
#else
  #define FREE_PDK_CALIBRATE_SYSCLOCK(vdd_mv)   EASY_PDK_CALIBRATE_ILRC(F_CPU, vdd_mv);
#endif

#endif //__SYSCLOCK_H__
