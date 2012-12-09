/*******************************************************************************
BLiT
Stephen Niedzielski [sniedzie@digipen.edu]
Created:  Sunday, November 25, 2007 [Stephen Niedzielski]
Modified: Sunday, November 25, 2007 [Stephen Niedzielski]
*******************************************************************************/


#ifndef BLiT_DL_List
#define BLiT_DL_List


/****************** Interfaces. ******************/
typedef void (* FreeProc)(void * Data);
/* typedef void (* AllocProc)(unsigned Size); */

/* Note: "typedef struct Name ..." and "struct Name * ..." allow for
   struct members of type pointer to Name. */
typedef struct DL_ListNode
{
  void *                Data;
  struct DL_ListNode *  Prev,
                     *  Next;
} DL_ListNode;
typedef DL_ListNode DLL_Node;

typedef struct DL_List
{
  DLL_Node *          Head,
           *          Tail;
  struct Allocator *  NodeAllocator;
  FreeProc            FreeData;
} DL_List;

void ctorDL_List( DL_List * l, struct Allocator * NodeAllocator, FreeProc Free );
void dtorDL_List( DL_List * l );
void DLL_PushFront( DL_List * l, void * Data );
void DLL_PushBack( DL_List * l, void * Data );
void DLL_PopFront( DL_List * l );
void DLL_PopBack( DL_List * l );
void DLL_Insert( DL_List * l, DLL_Node * Prev, void * Data );
void DLL_Remove( DL_List * l, DLL_Node * n );
void DLL_Clear( DL_List * l );


#endif /* BLiT_DL_List */
