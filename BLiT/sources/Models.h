/*******************************************************************************
BLiT
Stephen Niedzielski [sniedzie@digipen.edu]
Created:  Tuesday, November 13, 2007 [Stephen Niedzielski]
Modified: Tuesday, November 13, 2007 [Stephen Niedzielski]
*******************************************************************************/


#ifndef BLiT_Models
#define BLiT_Models


/****************** Interfaces. ******************/
typedef struct
{
  char x,
       y;
} Vertex;

typedef struct fVertex
{
  float x,
        y;
} fVertex;

typedef struct ucVertex
{
  unsigned char x,
                y;
} ucVertex;

typedef struct ssVertex
{
  signed short x,
               y;
} ssVertex;

typedef struct
{
  unsigned short  Cmd,
                  Data; /* Optional. */
  unsigned char   HasData;
  const Vertex *  End;  /* Points to one vertex past the end of valid
                           command verticies. */
} Command;

typedef struct
{
  Command *       Cmds,
          *       CmdsEnd;
  const Vertex *  Verts,
               *  VertsEnd;
  fVertex        Position;
  float           Scale;
  short           Angle;
  unsigned char   Radius;
  float           Momentum;
} Model;

typedef struct
{
  Model * m;
  unsigned char InUse;
  short DrawAngle;
} DemiModel;

/****************** Globals. ******************/
extern const  Model a     ,
              Square      ,
              mdlShip     ,
              mdlRockA    ,
              mdlRockB    ,
              mdlRockC    ,
              mdlTriangle ,
              mdlStar     ,
              mdlHexagon  ;

/****************** Function Prototypes. ******************/
void Translate( signed char x, signed char y, Model * m );
Vertex Scale( Vertex v, float Scale );
Vertex Rotate( Vertex v, short Angle );
void Draw( Model * m );
Model * Copy( const Model * m );
float Sine( short Angle );
float Cosine( short Angle );
void DemiDraw( DemiModel * d );

#endif /* BLiT_Models */
