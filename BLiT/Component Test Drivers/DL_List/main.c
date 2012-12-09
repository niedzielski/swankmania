#include "Global.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/******************************************************************************/
#ifdef _MSC_VER
  #pragma warning(disable: 4996) /* Suppress deprecation warnings. */
#endif

#include <stdio.h> /* freopen */

/* C */
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

/* C++ */
#include <stdlib.h>
#include "LeakCheck.h"
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
/******************************************************************************/


char * Data0[] =
{
  "ABCD",
  "EFGH",
  "IJKL",
  "LMNO",
  "PQRS",
  "TUVW",
  "XYZ"
};

void DLL_Print( const DL_List * l )
{
  const DLL_Node * n;
  assert( l );
  n = l->Head;
  while( n )
  {
    printf("%s\n", n->Data);
    n = n->Next;
  }
}

void NoFree( void * Data )
{
  (void)Data;
}

staticAllocator( DLL_Allocator, sizeof(Data0) / sizeof(char *), sizeof(DLL_Node) );
Allocator * pDLL_Allocator;

int main()
{
  FILE * Re;
  unsigned c;
  DL_List l;

  #ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
  #endif

  //Re = freopen( "C:\\user\\CS 280\\asn6\\out.txt", "w", stdout );

  pDLL_Allocator = &DLL_Allocator.Allocator;
  ctorAllocator( pDLL_Allocator, pDLL_Allocator->Pool );
  ctorDL_List( &l, pDLL_Allocator, NoFree );

  c = 0;
  while( c < (sizeof(Data0) / sizeof( char * )) )
  {
    DLL_PushBack( &l, Data0[c] );
    ++c;
  }

  DLL_Print( &l );

  dtorDL_List( &l );

  return 0;
}
