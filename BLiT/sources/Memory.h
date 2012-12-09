/*******************************************************************************
BLiT
Stephen Niedzielski [sniedzie@digipen.edu]
Created:  Monday, November 26, 2007 [Stephen Niedzielski]
Modified: Monday, November 26, 2007 [Stephen Niedzielski]
*******************************************************************************/

#ifndef BLiT_Memory
#define BLiT_Memory

/****************** Interfaces. ******************/
typedef struct Puddle
{
  struct Puddle * Next;
} Puddle;

typedef struct Allocator
{
  Puddle * Head;
  Puddle * Pool;
  const unsigned PoolSize   ,
                 PuddleSize ;
} Allocator;

/* Note that Head must be the first element in this structure to guarantee that
   the address of the structure is the address of Head. */
#define staticAllocator( Name, PoolSize, PuddleSize )\
  struct\
  {\
    Allocator Allocator;\
    Puddle Pool[PoolSize * PuddleSize];\
  } _##Name = { 0, _##Name.Pool, PoolSize, PuddleSize };\
  Allocator * Name = &_##Name.Allocator

void ctorAllocator( Allocator * a, Puddle * Pool );
void dtorAllocator( Allocator * a );
void * AllocatorAllocate( Allocator * a );
void AllocatorFree( Allocator * a, void * p );


#endif /* BLiT_Memory */
