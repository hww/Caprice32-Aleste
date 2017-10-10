#include <stdio.h>
#include <string.h>
#include "z80.h"
#include "z80dis.h"
#include "aleste.h"   

extern t_z80regs z80;
void DAsmRegPrint(FILE *file)
{
   fprintf(file, "AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X IX:%04X IY:%04X AF'%04X BC'%04X DE'%04X HL'%04X I:%02X", 
	   z80.AF, z80.BC, z80.DE, z80.HL, z80.SP, z80.IX, z80.IY, z80.AFx, z80.BCx, z80.DEx, z80.HLx, z80.I);
}

int DAsm(Byte* pc, int bank, Byte* addr, FILE *file)
{
  char S[80],T[80],*P,*R;  
  int I,J;
 
  switch(bank&0x300){
	case DBG_RAM:
	fprintf(file, "RAM  %04X:%06X:", bank, pc);
	break;
	case DBG_ROM:
	fprintf(file, "ROM  %04X:%06X:", bank, pc);
	break;
	case DBG_ROM2:
	fprintf(file, "ROM2 %04X:%06X:", bank, pc);
	break;
  }		

  I=*addr++;
  
  switch(I)
  {
    case 0xCB: I=*addr++;;
               strcpy(S,MnemonicsCB[I]);
               break;
    case 0xED: I=*addr++;;
               strcpy(S,MnemonicsED[I]);
               break;
    case 0xFD: I=*addr++;;
               strcpy(S,MnemonicsXX[I]);
               if(P=strchr(S,'%')) *P='Y';
               break;
    case 0xDD: I=*addr++;
               strcpy(S,MnemonicsXX[I]);
               if(P=strchr(S,'%')) *P='X';
               break;
    default:   strcpy(S,Mnemonics[I]);
  }

  if(P=strchr(S,'*'))
  {
    I=*addr++;;
    *P++='\0';
    sprintf(T,"%s%hX",S,I);
    if(R=strchr(P,'*'))
    {
      I=*addr++;
      *R++='\0';
      sprintf(strchr(T,'\0'),"%s%hX%s",P,I,R);
    }
    else strcat(T,P);  
  }
  else if(P=strchr(S,'#'))
       {
         I=*addr++;
         J=*addr++;
         *P++='\0';
         sprintf(T,"%s%hX%s",S,256*J+I,P);
       }
       else strcpy(T,S);
  fprintf(file, "\t%s",T);
  fprintf(file, "%*c", 20-strlen(T), ' ');
  DAsmRegPrint(file);      
  fprintf(file, "\n");
  return(1);
}  
