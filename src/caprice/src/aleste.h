#ifndef ALESTE_H
#define ALESTE_H

#include "z80.h"

#define ALESTE_MAPPER_MASK 0x1F

// DEBUGGING INFO 
#define DBG_RAM  0x000
#define DBG_ROM  0x100
#define DBG_ROM2 0x200

typedef union {
	struct {
   int HIGHTY  : 1;
   int HIGHTX  : 1;
   int MAPMOD  : 1;
   int BLACKS  : 1;
   int CS53    : 1; // (1 select of 8253, any OUT will write, IN impossible) 
   int CSAY   : 1; // equal 0 swith off RTC access. But if it 1 it enable to RTC access. But access to RTC by 8255  
   int SPARE1  : 1;
   int SPARE2  : 1;
   } bit;  
	 Byte b;
}  AlesteExtend;


EXTERN_C bool ALESTE;
EXTERN_C AlesteExtend alesteExtend;

EXTERN_C Byte alesteMapper[4];
EXTERN_C void rtcPowerOn();
EXTERN_C void rtcAS(Byte data);
EXTERN_C Byte rtcRead();
EXTERN_C void rtcWrite(Byte data);
EXTERN_C bool fdc_interrupt();
EXTERN_C void alesteReset();
EXTERN_C void alestePowerOn();
EXTERN_C inline int SynthesizerMS(void);
EXTERN_C void writeMS(reg_pair addr, Byte data);
EXTERN_C Byte readMS(reg_pair addr);





#endif