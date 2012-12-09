#include "Global.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

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

#define POOL_SIZE   4
#define PUDDLE_SIZE 4

staticAllocator( Alloc, POOL_SIZE, PUDDLE_SIZE );
Allocator * pAlloc;

char * p[POOL_SIZE];

void Write( )
{
  unsigned c;
  char str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  str[PUDDLE_SIZE - 1] = 0;
  /* Write to the whole range. */
  c = 0;
  while( c < POOL_SIZE )
  {
    memcpy( p[c],
            str,
            PUDDLE_SIZE );
    ++c;
  }
}

void FreeRange( unsigned Size )
{
  unsigned c = 0;
  while( c < Size )
  {
    AllocatorFree( pAlloc, p[c] );
    p[c] = 0;
    ++c;
  }
}

void Test1()
{
  unsigned c;

  /* Allocate the whole range. */
  c = 0;
  while( c < POOL_SIZE )
  {
    p[c] = AllocatorAllocate( pAlloc );
    ++c;
  }
  
  Write( POOL_SIZE );

  /* Print out the range. */
  c = 0;
  while( c < POOL_SIZE )
  {
    printf( "%s\n", p[c] );
    ++c;
  }

  /* Free the whole range. */
  FreeRange( POOL_SIZE );
}
//
//unsigned AllocateRand( )
//{
//  const unsigned TotalMemorySize = MallocBlockSize * MallocBlockQuantity;
//  unsigned c;
//  unsigned Size;
//  unsigned Accum;
//  c = 0;
//  Accum = 0;
//  for(;;)
//  {
//    Size = rand() % TotalMemorySize + 1;
//    if( (((Size / MallocBlockSize) * MallocBlockSize + (Size % MallocBlockSize != 0) * MallocBlockSize) + Accum) <= TotalMemorySize )
//    {
//      Accum += (Size / MallocBlockSize) * MallocBlockSize + (Size % MallocBlockSize != 0) * MallocBlockSize;
//      p[c] = Malloc( Size );
//      ++c;
//    }
//    else
//      return c;
//  }
//}
//
//void Test2( unsigned seed )
//{
//  unsigned c; 
//  srand( seed );
//
//  c = 0;
//  while( c < 100 )
//  {
//    /* Allocate randomly sized blocks until depleted. */
//    unsigned Size = AllocateRand();
//
//    /* Write to them. */
//    Write( Size );
//
//    /* Free. */
//    FreeRange( Size );
//
//    ++c;
//  }  
//}
//
//void Test3()
//{
//  unsigned c;
//  c = 0;
//  while( c < 2000 )
//  {
//    Test2( c + rand() );
//    ++c;
//  }
//}
//  void * InitMalloc();
int main()
{
  FILE * Re;
  #ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
  #endif

  ///*Re = freopen( "C:\\user\\CS 280\\asn6\\out.txt", "w", stdout );*/
  srand( 100 );

  pAlloc = &Alloc._Allocator;
  ctorAllocator( pAlloc, pAlloc->Pool );
  Test1();
  //Test2( rand() );
  //Test3();

  //free(p);

  return 0;
}
