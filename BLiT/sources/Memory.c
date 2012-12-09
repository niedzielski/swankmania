/*******************************************************************************
BLiT
Stephen Niedzielski [sniedzie@digipen.edu]
Created:  Monday, November 26, 2007 [Stephen Niedzielski]
Modified: Monday, November 26, 2007 [Stephen Niedzielski]
*******************************************************************************/

/****************** Includes. ******************/
#include "Global.h"
#include <math.h>

#ifdef _MSC_VER
  #include <stdlib.h>
  #include "LeakCheck.h"
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/****************** Implementations. ******************/
void ctorAllocator( Allocator * a, Puddle * Pool )
{
  char * p;
  char * pEnd;
  assert( a );
  assert( Pool ); /* FAIL: No memory allocated. */
  a->Pool = Pool;

  p = (char *)a->Pool;
  pEnd = (char *)a->Pool + a->PoolSize * a->PuddleSize;
  while( p < pEnd )
  {
    ((Puddle *)p)->Next =   a->Head;
    a->Head             =   ((Puddle *)p);
    p                   +=  a->PuddleSize;
  }
}

void * AllocatorAllocate( Allocator * a )
{
  Puddle * p;
  assert( a );
  assert( a->Head ); /* FAIL: Out of memory. */
  p = a->Head;
  a->Head = a->Head->Next;
  return p;
}

void AllocatorFree( Allocator * a, void * p )
{
  assert( a );
  if( !p )
    return;

  ((Puddle *)p)->Next = a->Head;
  a->Head = p;
}
