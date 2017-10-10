
#include "cap32.h"
#include "z80.h"
#include "aleste.h"
#include <time.h>

bool ALESTE = true;

Byte alesteMapper[4];

AlesteExtend alesteExtend;

#ifdef DEBUG_ALESTE_RTC_AS
extern FILE *pfoDebug;
#else
#ifdef DEBUG_ALESTE_RTC
extern FILE *pfoDebug;
#else
#ifdef DEBUG_ALESTE_MAGIC_SOUND
extern FILE *pfoDebug;
#endif
#endif
#endif

extern Byte *pbRAM;
extern uLong freq_table[];
extern t_CPC CPC;
/*
 *
 * MAGIC SOUND
 *
 */

Byte msMapper[4][4];	// 4 channels and 4 pages
Byte msVolume[4];		// 4 channels 
unsigned int  msTimer[4];

Byte msDMAMode[4];			// mode
unsigned int  msDMABeg[4];		// Dma address
unsigned int  msDMALen[4];	// Dma lenght

unsigned int  msDMAPtr[4];	// Dma pointer
unsigned int  msDMAEnd[4];	// Dma end
unsigned int  msDMAInc[4];	// Dma increment

Byte msDMAMask;			// Dma mask
Byte msDMAStatus;

unsigned int msFrequense;


void initMS(){
	int i, j;
	msFrequense = freq_table[CPC.snd_playback_rate];
	msDMAMask = 0xF;	// SWITCH OFF ALL CHANNELS
	msDMAStatus = 0;
	for(i=0; i<4; i++){
		msDMABeg[i] = 0;
		msDMALen[i] = 0;
		msDMAPtr[i] = 0;
		msDMAEnd[i] = 0;
		msDMAInc[i] = 0;
	}
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			msMapper[i][j] = 0;
		}
	}
}

inline int SynthesizerMS(void){
	unsigned int dptr;
	Byte* ptr;
	Byte m;
	bool nmi;
	int samp;
	samp = 0;
	nmi = false;
	m = ~(msDMAMask | msDMAStatus) ;
	if((m&1)){
		dptr = msDMAPtr[0]>>16;
		ptr = pbRAM + ((dptr & 0x3FFF) | msMapper[0][dptr>>14]<<14);
		samp += ((int)*ptr-0x80) * (int)msVolume[0];
		msDMAPtr[0]+=msDMAInc[0];
		if(msDMAPtr[0]>=msDMAEnd[0]){
			if(msDMAMode[0] & 0x10)
			{	msDMAPtr[0] -= msDMABeg[0]; }
			else
			{	msDMAStatus |= 1; msDMAMask |= 1; nmi = true; }

		}
		
	}
	if((m&2)){
		dptr = msDMAPtr[1]>>16;
		ptr = pbRAM + ((dptr & 0x3FFF) | msMapper[1][dptr>>14]<<14);
		samp += ((int)*ptr-0x80) * (int)msVolume[1];
		msDMAPtr[1]+=msDMAInc[1];
		if(msDMAPtr[1]>=msDMAEnd[1]){
			if(msDMAMode[1] & 0x10)
			{	msDMAPtr[1] -= msDMABeg[1]; }
			else
			{	msDMAStatus |= 2; msDMAMask |= 2; nmi = true; }
		}
	}
	if((m&4)){
		dptr = msDMAPtr[2]>>16;
		ptr = pbRAM + ((dptr & 0x3FFF) | msMapper[2][dptr>>14]<<14);
		samp += ((int)*ptr-0x80) * (int)msVolume[2];
		msDMAPtr[2]+=msDMAInc[2];
		if(msDMAPtr[2]>=msDMAEnd[2]){
			if(msDMAMode[2] & 0x10)
			{	msDMAPtr[2] -= msDMABeg[2]; }
			else
			{	msDMAStatus |= 4; msDMAMask |= 4; nmi = true; }
		}
	}
	if((m&8)){
		dptr = msDMAPtr[3]>>16;
		ptr = pbRAM + ((dptr & 0x3FFF) | msMapper[3][dptr>>14]<<14);
		samp += ((int)*ptr-0x80) * (int)msVolume[3];
		msDMAPtr[3]+=msDMAInc[3];
		if(msDMAPtr[3]>=msDMAEnd[3]){
			if(msDMAMode[3] & 0x10)
			{	msDMAPtr[3] -= msDMABeg[3]; }		
			else
			{	msDMAStatus |= 8; msDMAMask |= 8; nmi = true; }
		}
	}
	if(nmi)
		z80_NMI();
	//fprintf(pfoDebug, "0x%04x\n", samp);
	return samp/2;
}


void writeMS(reg_pair addr, Byte data){
	Byte unit, a, a1, ch;
	unit = addr.b.h & 3;
	a = addr.b.l & 3;

	switch(unit){
		case 0:	// DMA
			switch(addr.b.l & 0xf){
			case 0x8:	//DMACOM
				// CAN BE IGNORED
			break;
			case 0xB:	//DMAMOD		
				msDMAMode[data & 3] = data;
			break;
			case 0xD:	//DMARES		
				// CAN BE IGNORED
			break;
			case 0xA:	//DMAMASK		
				// XXXX XXnn  Channel number
				// XXXX X0XX  Clear MAsk (START CHANNEL)
				// XXXX X1XX  Set mask (STOP CHANNEL)
				ch = data&3;
				if(data & 4)
				{	msDMAMask |= 1<<ch; }
				else
				{
					msDMAPtr[ch]  = msDMABeg[ch];
					msDMAEnd[ch]  = msDMABeg[ch] + msDMALen[ch];
					// Start channel
					msDMAMask &= ~(1<<ch);
					#ifdef DEBUG_ALESTE_MAGIC_SOUND
					fprintf(pfoDebug, "MS START CHANNEL 0x%02x 0x%02x 0x%04x - 0x%04x\n", ch , msDMAMode[ch], msDMAPtr[ch]>>16, msDMAEnd[ch]>>16);
					#endif
				}
			#ifdef DEBUG_ALESTE_MAGIC_SOUND
			fprintf(pfoDebug, "MS SET MASK 0x%02x\n", msDMAMask);
			#endif
			break;
			default:
				ch = (addr.b.l>>1) & 0x3;
				if(addr.b.l & 1)
				{ // LENGHT
						msDMALen[ch] = (msDMALen[ch]>>8) & 0x00FF0000;
						msDMALen[ch] |= data<<24;
				} 
				else 
				{ // DMA POSITION
						msDMABeg[ch]  = (msDMABeg[ch]>>8) & 0x00FF0000;
						msDMABeg[ch] |= data<<24;
				}
			break;
			}
			break;
		case 1:	// TIMER
			if(!(addr.b.l & 4) && a>2) // TIMER 0
			{
				return;
			}
			if(!(addr.b.l & 8)) // TIMER 1
			{
				if(a>0) 
					return;
				else
					a = 3;
			}
			msTimer[a]  = msTimer[a]>>8;
			msTimer[a] |= data<<8;
			/* HOW GET FREQUESNCE */
			msDMAInc[a] = 0x10000 / ((double)(msFrequense*msTimer[a]) / 4000000.0);
			/* ------------------ */
			#ifdef DEBUG_ALESTE_MAGIC_SOUND
			fprintf(pfoDebug, "MS SET TIMER 0x%02x=0x%04x\n", a , msTimer[a]);
			#endif
			break;
		case 2:	// VOLUME
			msVolume[a] = data;
			#ifdef DEBUG_ALESTE_MAGIC_SOUND
			fprintf(pfoDebug, "MS SET VOLUME [%02x]=0x%02x\n", a , data);
			#endif
			break;
		case 3:	// MAPPER
			a1 = addr.b.l>>2 & 3;
			msMapper[a1][a] = ~data & 0x1F;
			#ifdef DEBUG_ALESTE_MAGIC_SOUND
			fprintf(pfoDebug, "MS SET MAPPER [%02x][%02x]=0x%02x\n", a1, a , msMapper[a1][a]);
			#endif
			break;

	}

}

Byte readMS(reg_pair addr){
	Byte res = 0xFF;
	if((addr.b.h & 0x3) == 0){
		 // DMA
		if((addr.b.l & 0xf) == 8){
			//DMACOM
			res = msDMAStatus;
			msDMAStatus = 0;
		}
	}
    #ifdef DEBUG_ALESTE_MAGIC_SOUND
       fprintf(pfoDebug, "MS READ STATUS 0x%02x\n", res);
    #endif
	return res;
}


/*
 *
 * RTC CONTROLLER
 *
 */

Byte rtcReg;
Byte rtcMem[64];

void rtcPowerOn(){
	int i;
	for (i=0; i<64; i++)
		rtcMem[i] = 0xFF;
	rtcMem[13]=0;
}

void rtcAS(Byte data){
    #ifdef DEBUG_ALESTE_RTC_AS
       fprintf(pfoDebug, "RTC AS 0x%02x\r\n", data);
    #endif		
	rtcReg=data; 
}

Byte rtcRead(){
	struct tm *t;
	time_t result;
	Byte data = 0;
	result = time(NULL);
	t = localtime(&result);
	switch(rtcReg){
		case 0:	// Seconds
			data = t->tm_sec;
			break;
		case 1:	// Seconds alarm
			break;
		case 2:	// Minutes
			data = t->tm_min;
			break;
		case 3:	// Minutes alarm
			break;
		case 4:	// Hours
			data = t->tm_hour;
			break;
		case 5:	// Hours alarm
			break;
		case 6: // Day of week
			data = t->tm_wday;
			break;
		case 7: // Day of month
			data = t->tm_mday;
			break;
		case 8: // Month
			data = t->tm_mon;
			break;
		case 9: // Year
			data = t->tm_year-80; // ALESTE year begins with 1980
			break;
		case 10: // Reg A
			data = 1;
			break;
		case 11: // Reg B
			data = 7;
		break;
		case 12: // Reg C
			data = 0x10;
			break;
		case 13: // Reg D
			data  = rtcMem[rtcReg];
			rtcMem[rtcReg] = 0x80;
			break;
		default: // Memory
			data = rtcMem[rtcReg];
			break;
	}
    #ifdef DEBUG_ALESTE_RTC
       fprintf(pfoDebug, "RTC Read 0x%02x=0x%02x\r\n", rtcReg, data);
    #endif		
	return data;
}

void rtcWrite(Byte data){
	    #ifdef DEBUG_ALESTE_RTC
	       fprintf(pfoDebug, "RTC Write 0x%02x=0x%02x\r\n", rtcReg, data);
	    #endif		
		switch(rtcReg){
		case 0:	// Seconds
			break;
		case 1:	// Seconds alarm
			break;
		case 2:	// Minutes
			break;
		case 3:	// Minutes alarm
			break;
		case 4:	// Hours
			break;
		case 5:	// Hours alarm
			break;
		case 6: // Day of week
			break;
		case 7: // Day of month
			break;
		case 8: // Month
			break;
		case 9: // Year
			break;
		case 10: // Reg A
			break;
		case 11: // Reg B
			break;
		case 12: // Reg C
			break;
		case 13: // Reg D
			break;
		default: // Memory
			rtcMem[rtcReg] = data;
			break;
	}
}

void alesteReset(){
	initMS();
	alesteExtend.b = 0;
	alesteMapper[0] = 0;
	alesteMapper[1] = 0;
	alesteMapper[2] = 0;
	alesteMapper[3] = 0;
}

void alestePowerOn(){
	rtcPowerOn();
	alesteReset();
}
