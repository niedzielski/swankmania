/*******************************************************************************
BLiT
Stephen Niedzielski [sniedzie@digipen.edu]
Created:  Tuesday, November 13, 2007 [Stephen Niedzielski]
Modified: Tuesday, November 13, 2007 [Stephen Niedzielski]
*******************************************************************************/


#ifndef BLiT_Graphics
#define BLiT_Graphics

/****************** Constants. ******************/
/* Some basic colors. */
#define smRed   0x1C0
#define smGreen 0x038
#define smBlue  0x007
#define smBlack 0x000

/* Commands. */
#define smCmdFlipScreenBuffer 0x000
#define smCmdPolyline         0x001
#define smCmdDot              0x005
#define smCmdColor            0x004

/* Pins.
  Expected pin setup:

  Port  Func  IO
  IRQ1  Frame I <- I think this is marked as IRQ4 on the demo board schematics.
  TC0   Cmd   O
  QS3   Go    O
  QS2:0 D8:6  O
  AN5:0 D5:0  O
*/
/* Change.  Need to have reference on pin something.*/
#define smTS2   MCF_GPIO_PORTAN_PORTAN7
#define smTS1   MCF_GPIO_PORTAN_PORTAN6
#define smFrame MCF_GPIO_PORTTC_PORTTC1
#define smCmd   MCF_GPIO_PORTTC_PORTTC0
#define smGo    MCF_GPIO_PORTQS_PORTQS3
#define smDH(x) ((unsigned char)(x >> 6))
#define smDL(x) ((unsigned char)(x) & 63)

#define smEnableFrame();  mcf5xxx_wr_sr( 0x2000 );
#define smDisableFrame(); mcf5xxx_wr_sr( 0x2FFF );
#define smVertex( v )\
  smSend(v.y);\
  smSend(v.x);

void smModeDat();
void smModeCmd();
void smSend( unsigned short Datum );
void smFlip();
void smPolyline();
void smWaitForFrame();
void smDot();
void smColor( unsigned short Color );

/****************** Globals. ******************/
extern volatile unsigned char Frame;

/****************** Function Prototypes. ******************/
void smInit();
void ISR_FrameHandler();

#endif /* BLiT_Graphics */
