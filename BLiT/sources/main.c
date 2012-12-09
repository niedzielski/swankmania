/*******************************************************************************
BLiT
Stephen Niedzielski [sniedzie@digipen.edu]
Created:  Monday, October 15, 2007 [Stephen Niedzielski]
Modified: Monday, October 15, 2007 [Stephen Niedzielski]
*******************************************************************************/


/****************** Includes. ******************/
#include "Global.h"
#include <stdlib.h>
staticAllocator( ModelAllocator, 15, sizeof(Model) );
//Allocator * pModelAllocator = &ModelAllocator.Allocator;

staticAllocator( CommandAllocator, 15, sizeof(Command) );

//#define MAX_OBJECTS   25
//staticAllocator( DLL_Allocator, MAX_OBJECTS, sizeof(DLL_Node) );

//DL_List ObjectList;


/*
Probably have to change memory manager to use DL_List.
Need character manager. / the farm
objs have type
col. will just parse through list I guess...  Delete items not on screen.
triangle  bullets with particles
circle collision
touchscreen / controller
commit order - draw starts in bg to obscure problems.
particles on triangle bullets
random model deformations
Collision
*/


/*
  Collision manager
    parse list checking collisions
      if collision
        call collision function (ship, rock, or bullet)
*/

/*
void ObjectFree( void * Object )
{
  AllocatorFree( ModelAllocator, Object );
}
*/


/*
  AN7 PS
  AN6 CLK
  TC2 Q8
*/
#define nesPS     0x80
#define nesClk    0x40
#define nesQ8     0x04
#define nesRight  0x01
#define nesLeft   0x02
#define nesDown   0x04
#define nesUp     0x08
#define nesStart  0x10
#define nesSelect 0x20
#define nesB      0x40
#define nesA      0x80
void InitializeNESController(void)
{
/* Initializes the NES controller pins for use. */

  /* Configure AN7:6 data direction to output. */
  MCF_GPIO_DDRAN |= (nesPS | nesClk);

  /* Configure TC2 data direction input. */
  MCF_GPIO_DDRTC &= ~nesQ8;
  
  MCF_GPIO_PORTAN &= ~nesClk;
}

unsigned char ReadNESController(void)
{
/* This function manages the NES controller.  When called, the function triggers
   the NES controller clock line and reads the serial output for each button.

   Result:
   The current state of the controller in an active high unsigned character
   format as follows:

   Bit  Button
   7:   A
   6:   B
   5:   Select
   4:   Start
   3:   Up
   2:   Down
   1:   Left
   0:   Right */

  unsigned char Result = (MCF_GPIO_SETTC & 0x04) >> 2,
                Count;

  /* Clock to zero. */

  /* Change from parallel to serial mode. */
  MCF_GPIO_PORTAN &= ~nesPS;

  Count = 0;
  while( Count < 7 )
  {
    /* Pulse the clock, get the output, pulse the clock, get the output, ... */
    MCF_GPIO_PORTAN |= nesClk;
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    MCF_GPIO_PORTAN &= ~nesClk;
    Result <<= 1;
    Result |= (MCF_GPIO_SETTC & 0x04) >> 2;
    ++Count;
  }

  /* Active low to active high. */
  Result = ~Result;

  /* Revert to parallel mode. */
  MCF_GPIO_PORTAN |= nesPS;

  return Result;
}



DemiModel
Bullet0 ,
Rock0   ,
Rock1   ,
Rock2   ;


int main(void)
{
  float
  x = 119,
  y = 79;
  unsigned char Input;
  Model * m;
  unsigned char Rocks = 0;
  float scale;
  
  ctorAllocator( ModelAllocator, ModelAllocator->Pool );
  ctorAllocator( CommandAllocator, CommandAllocator->Pool );
  //ctorAllocator( DLL_Allocator, DLL_Allocator->Pool );
  //ctorDL_List( &ObjectList, DLL_Allocator, ObjectFree );

  m = Copy( &mdlShip );
  m->Position.x = 119;
  m->Position.y = 79;

  Bullet0.m = Copy( &mdlTriangle );
  Bullet0.m->Position.x = 500;
  Bullet0.m->Position.y = 500;

  Rock0.m = Copy( &mdlRockA );
  Rock1.m = Copy( &mdlRockB );
  Rock2.m = Copy( &mdlRockC );

  Rock0.InUse = 0;
  Rock1.InUse = 0;
  Rock2.InUse = 0;

  smInit();
  
  InitializeNESController();
  
  //init_adc();
  
  

  for(;;)
  {
    smFlip();
    
    Input = ReadNESController();

    m->Angle %= 360;
    if( m->Angle < 0 )
      m->Angle += 360;

    if( Input & nesLeft )
      --m->Angle;
      
    if( Input & nesRight )
      ++m->Angle;
    
    if( Input & nesStart )
    {
      m->Position.x = 119;
      m->Position.y = 79;
      m->Momentum = 0;
      m->Angle = 0;
    }
/*
    if( Input & nesLeft && m->Angle != 270 )
      if( m->Angle < 90 || m->Angle > 270 )
        --m->Angle;
      else
        ++m->Angle;
    
    if( Input & nesRight && m->Angle != 90 )
      if( m->Angle < 90 || m->Angle >= 270 )
        ++m->Angle;
      else
        --m->Angle;
    if( Input & nesUp && m->Angle != 0 )
      if( m->Angle < 180 )
        --m->Angle;
      else
        ++m->Angle;
      
    if( Input & nesDown && m->Angle != 180 )
      if( m->Angle < 180 )
        ++m->Angle;
      else
        --m->Angle;
*/
    //if( !(rand() % 5) )
      ++Rock0.DrawAngle;
    //if( !(rand() % 5) )
      ++Rock1.DrawAngle;
    //if( !(rand() % 5) )
      ++Rock2.DrawAngle;
    Bullet0.DrawAngle += 10;
    
    if( rand() % 90 == 25 ) 
    {
      if( !Rock2.InUse )
      {
        Rock2.InUse = 1;
        Rock2.m->Position.x = rand() % 240;
        Rock2.m->Position.y = rand() % 160;
        Rock2.m->Scale = 0.5F + 1.0F / (rand() % 100 + 1);
        Rock2.m->Angle = rand() % 360;
        Rock2.m->Momentum = rand() % 200;
      }
      else if( !Rock0.InUse )
      {
        Rock0.InUse = 1;
        Rock0.m->Position.x = rand() % 240;
        Rock0.m->Position.y = rand() % 160;
        Rock0.m->Scale = 0.5F + 1.0F / (rand() % 100 + 1);
        Rock0.m->Angle = rand() % 360;
        Rock0.m->Momentum = rand() % 200;
      }
      else if( !Rock1.InUse )
      {
        Rock1.InUse = 1;
        Rock1.m->Position.x = rand() % 240;
        Rock1.m->Position.y = rand() % 160;
        Rock1.m->Scale = 0.5F + 1.0F / (rand() % 100 + 1);
        Rock1.m->Angle = rand() % 360;
        Rock1.m->Momentum = rand() % 200;
      }
    }
    
    if( Rock0.InUse )
      DemiDraw( &Rock0 );
    if( Rock1.InUse )
      DemiDraw( &Rock1 );
    if( Rock2.InUse )
      DemiDraw( &Rock2 );
    
    if( Input & nesA && (m->Momentum < 1000) )
      m->Momentum += 10;
    
    if( Input & nesDown && (m->Momentum > -1000) )
      m->Momentum -= 10;
    
    if( Input & nesB && !Bullet0.InUse )
    {
      Bullet0.m->Position.x = m->Position.x + (m->Radius - 27) * Sine(m->Angle);
      Bullet0.m->Position.y = m->Position.y - (m->Radius - 27) * Cosine(m->Angle);
      Bullet0.m->Momentum = 500 + m->Momentum;
      Bullet0.m->Angle = m->Angle;
      Bullet0.InUse = 1;
    }


    if( m->Momentum != 0 )
    {
      if( m->Momentum < 0 )
        m->Momentum += 2;
      else
        m->Momentum -= 2;
    }
    m->Position.x += m->Momentum * .0025 * Sine(m->Angle);
    m->Position.y += m->Momentum * .0025 * -Cosine(m->Angle);
/*
    if( m->Position.x < 0 )
      m->Position.x = 239;
    
    if( m->Position.x > 239 )
      m->Position.x = 0;
    
    if( m->Position.y < 0 )
      m->Position.y = 159;
    
    if( m->Position.y > 159 )
      m->Position.y = 0;
*/
    Bullet0.m->Position.x += Bullet0.m->Momentum * .0025 * Sine(Bullet0.m->Angle);
    Bullet0.m->Position.y += Bullet0.m->Momentum * .0025 * -Cosine(Bullet0.m->Angle);
    if( Bullet0.m->Momentum != 0 )
    {
      if( Bullet0.m->Momentum < 0 )
        Bullet0.m->Momentum += 2;
      else
        Bullet0.m->Momentum -= 2;
    }
    else
      Bullet0.InUse = 0;
    
    Rock0.m->Position.x += Rock0.m->Momentum * .0025 * Sine(Rock0.m->Angle);
    Rock0.m->Position.y += Rock0.m->Momentum * .0025 * -Cosine(Rock0.m->Angle);
    Rock1.m->Position.x += Rock1.m->Momentum * .0025 * Sine(Rock1.m->Angle);
    Rock1.m->Position.y += Rock1.m->Momentum * .0025 * -Cosine(Rock1.m->Angle);
    Rock2.m->Position.x += Rock2.m->Momentum * .0025 * Sine(Rock2.m->Angle);
    Rock2.m->Position.y += Rock2.m->Momentum * .0025 * -Cosine(Rock2.m->Angle);

    smColor( smBlue );
    Draw( m );

    if( Bullet0.InUse )
      DemiDraw( &Bullet0 );
    
    if( Rock0.InUse && Bullet0.InUse )
    {      
      scale = Rock0.m->Radius * Rock0.m->Scale;
      if( Bullet0.m->Position.x >= Rock0.m->Position.x - scale &&
          Bullet0.m->Position.x <= Rock0.m->Position.x + scale &&
          Bullet0.m->Position.y >= Rock0.m->Position.y - scale &&
          Bullet0.m->Position.y <= Rock0.m->Position.y + scale )
      {
        Bullet0.InUse = 0;
        Rock0.InUse = 0;
      }
    }
    if( Rock1.InUse && Bullet0.InUse )
    {      
      scale = Rock1.m->Radius * Rock1.m->Scale;
      if( Bullet0.m->Position.x >= Rock1.m->Position.x - scale &&
          Bullet0.m->Position.x <= Rock1.m->Position.x + scale &&
          Bullet0.m->Position.y >= Rock1.m->Position.y - scale &&
          Bullet0.m->Position.y <= Rock1.m->Position.y + scale )
      {
        Bullet0.InUse = 0;
        Rock1.InUse = 0;
      }
    }
    if( Rock2.InUse && Bullet0.InUse )
    {      
      scale = Rock2.m->Radius * Rock2.m->Scale;
      if( Bullet0.m->Position.x >= Rock2.m->Position.x - scale &&
          Bullet0.m->Position.x <= Rock2.m->Position.x + scale &&
          Bullet0.m->Position.y >= Rock2.m->Position.y - scale &&
          Bullet0.m->Position.y <= Rock2.m->Position.y + scale )
      {
        Bullet0.InUse = 0;
        Rock2.InUse = 0;
      }
    }
    smWaitForFrame();
  }
  
  return 0;
}
