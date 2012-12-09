#ifndef _NEW_DEBUG_H
  #define _NEW_DEBUG_H
  #include <crtdbg.h>
  #ifdef _DEBUG
/*    void* operator new(size_t BlockSize, const char *File, int Line);*/
    #define NEW_DEBUG new(THIS_FILE, __LINE__)
    #define malloc(Size) _malloc_dbg(Size, _NORMAL_BLOCK, THIS_FILE, __LINE__);
  #endif
#endif

