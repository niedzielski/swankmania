/*******************************************************************************
BLiT
Stephen Niedzielski [sniedzie@digipen.edu]
Created:  Tuesday, November 13, 2007 [Stephen Niedzielski]
Modified: Tuesday, November 13, 2007 [Stephen Niedzielski]
*******************************************************************************/


/****************** Includes. ******************/
#include "Global.h"


/****************** Globals. ******************/
volatile unsigned char Frame = 0;


/****************** Function Implementations. ******************/
void smInit()
{
  /* Turn off QS. */
  MCF_GPIO_PORTQS = 0x00;

  /* Configure QS data direction to output. */
  MCF_GPIO_DDRQS = 0xFF;

  /* Configure QS for IO operation. */
  MCF_GPIO_PQSPAR = 0x00;

  /* Turn off AN. */
  MCF_GPIO_PORTAN = 0x00;

  /* Configure AN5:0, AN7:6 data direction to output, input. */
  MCF_GPIO_DDRAN = 0x3F;

  /* Configure AN for IO operation. */
  MCF_GPIO_PANPAR = 0x00;

  /* Turn off TC. */
  MCF_GPIO_PORTTC = 0x00;

  /* Configure TC:0, TC:1 data direction to output, input. */
  MCF_GPIO_DDRTC |= 0x01;
  MCF_GPIO_DDRTC &= ~0x02;

  /* Configure TC for IO operation. */
  MCF_GPIO_PTCPAR = 0x00;
  
  /* Reset the frame flag. */
  Frame = 0;
}


__declspec(interrupt) void ISR_FrameHandler()
{
  Frame = 1;
  
  /* Clear the interrupt event. */
  MCF_EPORT_EPFR(0) = (uint8)(MCF_EPORT_EPFR(0) | MCF_EPORT_EPFR_EPF1);
}


void smModeDat()
{
  MCF_GPIO_PORTTC = (unsigned char)!smCmd;
}

void smModeCmd()
{
  MCF_GPIO_PORTTC = (unsigned char)smCmd;
}

void smSend( unsigned short Datum )
{  
  MCF_GPIO_PORTAN = (unsigned char)((MCF_GPIO_PORTAN & 0xC0) | smDL(Datum));
  MCF_GPIO_PORTQS = smDH(Datum);
  nop();
  MCF_GPIO_PORTQS |= smGo; /* Go must be set AFTER the data has been loaded. */
  nop();
  MCF_GPIO_PORTQS = !smGo; /* Stop. */
}

void smFlip()
{
  smModeCmd();
  smSend( smCmdFlipScreenBuffer );
}

void smPolyline()
{
  smModeCmd();
  smSend( smCmdPolyline );
  smModeDat();
}

void smWaitForFrame()
{
  smEnableFrame();

  while( !Frame )
  {
  }

  Frame = 0;
  smDisableFrame();
}

void smDot()
{
  smModeCmd();
  smSend( smCmdDot );
  smModeDat();
}

void smColor( unsigned short Color )
{
  smModeCmd();
  smSend( smCmdColor );
  smModeDat();
  smSend( Color );
}
