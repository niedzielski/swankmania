/*******************************************************************************
BLiT
Stephen Niedzielski [sniedzie@digipen.edu]
Created:  Sunday, November 25, 2007 [Stephen Niedzielski]
Modified: Sunday, November 25, 2007 [Stephen Niedzielski]
*******************************************************************************/


/****************** Includes. ******************/
#include "Global.h"

#ifdef _MSC_VER
  #include <stdlib.h>
  #include "LeakCheck.h"
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif


/****************** Local function prototypes. ******************/
static void Detach( DL_List * l, const DLL_Node * n );
static void Attach( DL_List * l, DLL_Node * n, DLL_Node * Prev );


/****************** Implementations. ******************/
void ctorDL_List( DL_List * l, Allocator * NodeAllocator, FreeProc FreeData )
{
  assert( l );
  assert( NodeAllocator );
  assert( FreeData );
  l->Head = 0;
  l->Tail = 0;
  l->NodeAllocator = NodeAllocator;
  l->FreeData = FreeData;
}

void dtorDL_List( DL_List * l )
{
  DLL_Clear( l );  
}

void DLL_PushFront( DL_List * l, void * Data )
{
  DLL_Insert( l, 0, Data );
}

void DLL_PushBack( DL_List * l, void * Data )
{
  assert( l );
  DLL_Insert( l, l->Tail, Data );
}

void DLL_PopBack( DL_List * l )
{
  DLL_Node * n;
  assert( l );
  n = l->Tail;

  DLL_Remove( l, n );
}

void DLL_PopFront( DL_List * l )
{
  DLL_Node * n;
  assert( l );
  n = l->Head;

  DLL_Remove( l, n );
}

void DLL_Insert( DL_List * l, DLL_Node * Prev, void * Data )
{
  DLL_Node * n;
  assert( l );
  n = AllocatorAllocate( l->NodeAllocator );
  assert( n );
  n->Data = Data;
  Attach( l, n, Prev );
}

void DLL_Remove( DL_List * l, DLL_Node * n )
{
  assert( l );
  assert( n );
  
  Detach( l, n );

  /* Free the data, free the node. */
  l->FreeData( n->Data );
  AllocatorFree( l->NodeAllocator, n );  
}

void DLL_Clear( DL_List * l )
{
  DLL_Node * Next;
  assert( l );
  while( l->Head )
  {
    Next = l->Head->Next;

    /* Free the data, free the node. */
    l->FreeData( l->Head->Data );
    AllocatorFree( l->NodeAllocator, l->Head );

    l->Head = Next;
  }
}

static void Detach( DL_List * l, const DLL_Node * n )
{
  assert( l );
  assert( n );
  if( n->Prev )
    n->Prev->Next = n->Next;
  else
    l->Head = n->Next;
  
  if( n->Next )
    n->Next->Prev = n->Prev;
  else
    l->Tail = n->Prev;
}

/* Attaches node n after node Prev. */
static void Attach( DL_List * l, DLL_Node * n, DLL_Node * Prev )
{
  assert( l );
  assert( n );
  /* n. */
  if( Prev )
    n->Next = Prev->Next;
  else
    n->Next = 0;
  n->Prev = Prev;
  
  /* Neighbors. */
  if( Prev )
    Prev->Next = n;
  if( n->Next )
    n->Next->Prev = n;

  /* Head / tail. */
  if( !Prev )
    l->Head = n;
  if( Prev == l->Tail )
    l->Tail = n;
}
