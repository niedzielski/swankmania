/*******************************************************************************
BLiT
Stephen Niedzielski [sniedzie@digipen.edu]
Created:  Saturday, November 24, 2007 [Stephen Niedzielski]
Modified: Saturday, November 24, 2007 [Stephen Niedzielski]
*******************************************************************************/


/****************** Includes. ******************/
#include "Global.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>


/****************** Local macros. ******************/
/* Returns pointer to one past the end of the const (static) array. */
#define constVertEnd(x) (&x[sizeof(x) / sizeof(Vertex)])
#define constCmdEnd(x) ((Command *)(&x[sizeof(x) / sizeof(Command)]))

/****************** Template models. ******************/
static const Vertex
vert_a0[] =
{
  { -3, -3 },
  { -3, -4 },
  { 3, -4 },
  { 4, -3 },
  { 5, 6 },
  { 3, 6 },
  { 3, 5 },
  { 1, 6 },
  { -3, 6 },
  { -5, 4 },
  { -5, 1 },
  { -2, -1 },
  { 2, -1 },
  { 2, -2 },
  { -2, -2 },
  { -3, -3 }
},
vert_a1[] =
{
  { -3, 2 },
  { -2, 1 },
  { 1, 1 },
  { 2, 2 },
  { 2, 3 },
  { 1, 4 },
  { -2, 4 },
  { -3, 3 },
  { -3, 2 }
};

const Command cmd_a[] =
{
  { smCmdPolyline, 1, smBlack, constVertEnd( vert_a0 ) },
  { smCmdPolyline, 0, 0, constVertEnd( vert_a1 ) }
};

const Model a =
{
  (Command *)cmd_a,
  constCmdEnd( cmd_a ),
  vert_a0,
  constVertEnd( vert_a1 ),
  { 0, 0 },
  1.0F,
  0,
  6
};

static const Vertex
vertSquare[] =
{
  { -10, -10 },
  { 10, -10 },
  { 10, 10 },
  { -10, 10 },
  { -10, -10 }
};

const Command cmd_Square[] =
{
  { smCmdPolyline, 0, 0, constVertEnd( vertSquare ) }
};

const Model Square =
{
  (Command *)cmd_Square,
  constCmdEnd( cmd_Square ),
  vertSquare,
  constVertEnd( vertSquare ),
  { 0, 0 },
  1.0F,
  0,
  12
};


static const Vertex
vertShip0[] = /* Body outline. */
{
  { 0, -25 },
  { 7, -19 },
  { 19, 12 },
  { 13, 22 },
  { 8, 24 },
  { -8, 24 },
  { -13,22 },
  { -19, 12 },
  { -7, -19 },
  { 0, -25 }
},
vertShip1[] = /* Nosecone detail. */
{
  { -7, -19 },
  { 0, -22 },
  { 7, -19 }
},
vertShip2[] = /* Cockpit outline. */
{
  { 0, -7 },
  { 3, -6 },
  { 6, 3 },
  { 3, 7 },
  { -3, 7 },
  { -6, 3 },
  { -3, -6 },
  { 0, -7 }
},
vertShip3[] = /* Engine detail. */
{
  { -19, 12 },
  { -13, 22 },
  { 13, 22 },
  { 19, 12 }
};

Command cmdShip[] =
{
  { smCmdPolyline, 1, smBlack, constVertEnd( vertShip0 ) },
  { smCmdPolyline, 0, 0, constVertEnd( vertShip1 ) },
  { smCmdPolyline, 0, 0, constVertEnd( vertShip2 ) },
  { smCmdPolyline, 0, 0, constVertEnd( vertShip3 ) }
};

const Model mdlShip =
{
  cmdShip,
  constCmdEnd( cmdShip ),
  vertShip0,
  constVertEnd( vertShip3 ),
  { 0, 0 },
  1.0F,
  0,
  50
};


static const Vertex
vertRockA[] =
{
  { 0, -16 },
  { 7, -15 },
  { 9, -6 },
  { 15, -5 },
  { 16, 2 },
  { 15, 8 },
  { 10, 13 },
  { 4, 12 },
  { -3, 16 },
  { -9, 14 },
  { -14, 9 },
  { -16, 2},
  { -12, -4 },
  { -11, -10 },
  { -5, -11 },
  { 0, -16 }
};

Command cmdRockA[] =
{
  { smCmdPolyline, 1, smBlack, constVertEnd( vertRockA ) },
};

const Model mdlRockA =
{
  cmdRockA,
  constCmdEnd( cmdRockA ),
  vertRockA,
  constVertEnd( vertRockA ),
  { 0, 0 },
  1.0F,
  0,
  10
};


static const Vertex
vertRockB[] =
{
  { -2, -24 },
  { 9, -26 },
  { 19, -19 },
  { 28, 0 },
  { 14, 7 },
  { 13, 23 },
  { -4, 26 },
  { -9, 22},
  { -19, 23 },
  { -28, 6 },
  { -23, -1 },
  { -24, -19 },
  { -14, -25 },
  { -2, -24 }
};

Command cmdRockB[] =
{
  { smCmdPolyline, 1, smGreen, constVertEnd( vertRockB ) },
};

const Model mdlRockB =
{
  cmdRockB,
  constCmdEnd( cmdRockB ),
  vertRockB,
  constVertEnd( vertRockB ),
  { 0, 0 },
  1.0F,
  0,
  24
};

static const Vertex
vertRockC[] =
{
  { 0, -17 },
  { 2, -10 },
  { 15, -7 },
  { 17, 3 },
  { 5, 17 },
  { -5, 16 },
  { -13, 12 },
  { -17, 3 },
  { -9, -14 },
  { 0, -17 }

};

Command cmdRockC[] =
{
  { smCmdPolyline, 1, smBlue, constVertEnd( vertRockC ) },
};

const Model mdlRockC =
{
  cmdRockC,
  constCmdEnd( cmdRockC ),
  vertRockC,
  constVertEnd( vertRockC ),
  { 0, 0 },
  1.0F,
  0,
  13
};


static const Vertex
vertTriangle[] =
{
  { 0, -2 },
  { 2, 2 },
  { -2, 2 },
  { 0, -2 }
};

Command cmdTriangle[] =
{
  { smCmdPolyline, 1, smRed, constVertEnd( vertTriangle ) },
};

const Model mdlTriangle =
{
  cmdTriangle,
  constCmdEnd( cmdTriangle ),
  vertTriangle,
  constVertEnd( vertTriangle ),
  { 0, 0 },
  1.0F,
  0,
  4
};


static const Vertex
vertStar[] =
{
  { 0, -7 },
  { 2, -3 },
  { 7, -2 },
  { 4, 2 },
  { 5, 7},
  { 0, 5 },
  { -5, 7 },
  { -4, 2 },
  { -7, -2 },
  { -2, -3 },
  { 0, -7 }
};

Command cmdStar[] =
{
  { smCmdPolyline, 1, smBlack, constVertEnd( vertStar ) },
};

const Model mdlStar =
{
  cmdStar,
  constCmdEnd( cmdStar ),
  vertStar,
  constVertEnd( vertStar ),
  { 0, 0 },
  1.0F,
  0,
  7
};

static const Vertex
vertHexagon[] =
{
  { 3, -6 },
  { 7, 0 },
  { 3, 6 },
  { -3, 6 },
  { -7, 0 },
  { -3, -6 },
  { 3, -6 }
};

Command cmdHexagon[] =
{
  { smCmdPolyline, 1, smBlack, constVertEnd( vertHexagon ) },
};

const Model mdlHexagon = /* I hexawill, please. */
{
  cmdHexagon,
  constCmdEnd( cmdHexagon ),
  vertHexagon,
  constVertEnd( vertHexagon ),
  { 0, 0 },
  1.0F,
  0,
  7
};


/* Make much smaller or remove. */
const float SineLUT[91] = 
{
  0.000000E+00,
  1.745241E-02,
  3.489950E-02,
  5.233596E-02,
  6.975647E-02,
  8.715574E-02,
  1.045285E-01,
  1.218693E-01,
  1.391731E-01,
  1.564345E-01,
  1.736482E-01,
  1.908090E-01,
  2.079117E-01,
  2.249511E-01,
  2.419219E-01,
  2.588190E-01,
  2.756374E-01,
  2.923717E-01,
  3.090170E-01,
  3.255682E-01,
  3.420201E-01,
  3.583679E-01,
  3.746066E-01,
  3.907311E-01,
  4.067366E-01,
  4.226183E-01,
  4.383711E-01,
  4.539905E-01,
  4.694716E-01,
  4.848096E-01,
  5.000000E-01,
  5.150381E-01,
  5.299193E-01,
  5.446390E-01,
  5.591929E-01,
  5.735764E-01,
  5.877853E-01,
  6.018150E-01,
  6.156615E-01,
  6.293204E-01,
  6.427876E-01,
  6.560590E-01,
  6.691306E-01,
  6.819984E-01,
  6.946584E-01,
  7.071068E-01,
  7.193398E-01,
  7.313537E-01,
  7.431448E-01,
  7.547096E-01,
  7.660444E-01,
  7.771460E-01,
  7.880108E-01,
  7.986355E-01,
  8.090170E-01,
  8.191520E-01,
  8.290376E-01,
  8.386706E-01,
  8.480481E-01,
  8.571673E-01,
  8.660254E-01,
  8.746197E-01,
  8.829476E-01,
  8.910065E-01,
  8.987940E-01,
  9.063078E-01,
  9.135455E-01,
  9.205049E-01,
  9.271839E-01,
  9.335804E-01,
  9.396926E-01,
  9.455186E-01,
  9.510565E-01,
  9.563048E-01,
  9.612617E-01,
  9.659258E-01,
  9.702957E-01,
  9.743701E-01,
  9.781476E-01,
  9.816272E-01,
  9.848078E-01,
  9.876883E-01,
  9.902681E-01,
  9.925462E-01,
  9.945219E-01,
  9.961947E-01,
  9.975641E-01,
  9.986295E-01,
  9.993908E-01,
  9.998477E-01,
  1
};

float Sine( short Angle )
{
  Angle %= 360;
  if( Angle < 0 )
    Angle += 360;

  if( Angle <= 90 )
    return SineLUT[Angle];
    
  if( Angle <= 180 )
    return SineLUT[179 - Angle];
  
  if( Angle <= 270 )
    return -SineLUT[Angle - 180];
  
  return -SineLUT[360 - Angle];
}

float Cosine( short Angle )
{
  return Sine( (unsigned short)(Angle + 90) );
}


/****************** Function defintions. ******************/
Vertex Scale( Vertex v, float Scale )
{
  v.x *= Scale;
  v.y *= Scale;
  
  return v;
}


Vertex Rotate( Vertex v, signed short Angle )
{
  float s = Sine(Angle),
        c = Cosine(Angle);
  signed char x = v.x,
              y = v.y;

  v.x = (char)(c * x - s * y);
  v.y = (char)(s * x + c * y);

  return v;
}

ucVertex Clip( fVertex o, Vertex v )
{
  ucVertex Result;
/*  ssVertex t;
  float m,
        x,
        y;
  t.x = (o.x + o.x);
  t.y = (o.y + o.y);
  m = (float)t.y / t.x;
  
  // m == 0 case.
  /* Check left domain. */
/*  if( t.x < 0 )
  {
    x = t.x + t.x * m;
    y = t.y + t.y / m;
  }*/
  Result.x = (unsigned char)( (v.x + o.x) < 0
    ? 0
    : (v.x + o.x) > 239
    ? 239
    : (v.x + o.x) );
  Result.y = (unsigned char)( (v.y + o.y) < 0
    ? 0
    : (v.y + o.y) > 159
    ? 159
    : (v.y + o.y)  );
  
  return Result;
}

void Collide( Model * m, Vertex * v )
{
/*  DLL_Node * n = ObjectList->Head;
  DLL_Node * o;
  
  while( n )
  {
    o = ObjectList->Head;
    while( o )
    {
      if( (Model *)(n->Data)->Radius && not n
    }
    n = n->Next;
  }*/
}

void Draw( Model * m )
{
  Command * c;
  const Vertex * v;
  unsigned char Collided = 0;
  assert(m);
  c = m->Cmds;
  v = m->Verts;

  for( ; c < m->CmdsEnd; )
  {
    /* Command. */
    smModeCmd();
    smSend( c->Cmd );
    
    /* Command data. */
    if( c->HasData )
    {
      smSend( c->Data );
    }
    
    /* Data. */
    smModeDat();
    /* Verticies. */
    while( v < c->End )
    {
      ucVertex T;
      Vertex t = Scale( *v, m->Scale );
      t = Rotate( t, m->Angle );
      T = Clip( m->Position, t );
      if( ( !Collided && ( (m->Position.x + t.x) <= 0 ||
          (m->Position.x + t.x) >= 239 ||
          (m->Position.y + t.y) <= 0 ||
          (m->Position.y + t.y) >= 159 ) ) )
      {
        //if( !m->IsCollided )
          m->Momentum = -m->Momentum;
          Collided = 1;
          //m->Angle += 90;
        //m->Angle += 180;
        //if( !m->Momentum )
        //m->Momentum = 0;
/*
        if( (m->Position.x + t.x) <= 0 )
          m->Position.x += 1;
        if( (m->Position.x + t.x) >= 239  )
          m->Position.x -= 1;
        if( (m->Position.y + t.y) <= 0 )
          m->Position.y += 1;
        if( (m->Position.y + t.y) >= 159 )
          m->Position.y -= 1;*/
      }


      smVertex( T );
      ++v;
    }
    /*
    switch( (v - c->End - 1) & 7 )
    {
      case 0: 
        while( v < c->End )
        {
              smVertex(v->X, v->Y); ++v;
      case 7: smVertex(v->X, v->Y); ++v;
      case 6: smVertex(v->X, v->Y); ++v;
      case 5: smVertex(v->X, v->Y); ++v;
      case 4: smVertex(v->X, v->Y); ++v;
      case 3: smVertex(v->X, v->Y); ++v;
      case 2: smVertex(v->X, v->Y); ++v;
      case 1: smVertex(v->X, v->Y); ++v;
        }
    }*/
    ++c;
  }
}


void DemiDraw( DemiModel * d )
{
  Command * c;
  const Vertex * v;
  unsigned char Collided = 0;
  assert(d);
  c = d->m->Cmds;
  v = d->m->Verts;

  for( ; c < d->m->CmdsEnd; )
  {
    /* Command. */
    smModeCmd();
    smSend( c->Cmd );
    
    /* Command data. */
    if( c->HasData )
    {
      smSend( c->Data );
    }
    
    /* Data. */
    smModeDat();
    /* Verticies. */
    while( v < c->End )
    {
      ucVertex T;
      Vertex t = Scale( *v, d->m->Scale );
      t = Rotate( t, d->DrawAngle );
      T = Clip( d->m->Position, t );
      if( ( !Collided && ( (d->m->Position.x + t.x) <= 0 ||
          (d->m->Position.x + t.x) >= 239 ||
          (d->m->Position.y + t.y) <= 0 ||
          (d->m->Position.y + t.y) >= 159 ) ) )
      {
        d->InUse = 0;
      }


      smVertex( T );
      ++v;
    }
    /*
    switch( (v - c->End - 1) & 7 )
    {
      case 0: 
        while( v < c->End )
        {
              smVertex(v->X, v->Y); ++v;
      case 7: smVertex(v->X, v->Y); ++v;
      case 6: smVertex(v->X, v->Y); ++v;
      case 5: smVertex(v->X, v->Y); ++v;
      case 4: smVertex(v->X, v->Y); ++v;
      case 3: smVertex(v->X, v->Y); ++v;
      case 2: smVertex(v->X, v->Y); ++v;
      case 1: smVertex(v->X, v->Y); ++v;
        }
    }*/
    ++c;
  }
}

extern Allocator * ModelAllocator;
extern Allocator * CommandAllocator;

Model * Copy( const Model * m )
{
  Model * Clone = AllocatorAllocate( ModelAllocator );
  assert( Clone );
  
  Clone->Cmds     = m->Cmds;
  Clone->CmdsEnd  = m->CmdsEnd;
  Clone->Verts    = m->Verts;
  Clone->VertsEnd = m->VertsEnd;
  Clone->Radius   = m->Radius;
  Clone->Position = m->Position;
  Clone->Scale    = m->Scale;
  Clone->Angle    = m->Angle;

  //memcpy( Clone->Cmds, m->Cmds, (m->CmdsEnd - m->Cmds) * sizeof(Command) );
  
  
  return Clone;
}
