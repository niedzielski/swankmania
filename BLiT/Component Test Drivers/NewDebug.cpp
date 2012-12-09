#ifdef _MSC_VER
  #pragma warning(disable: 4514) // Suppress 'unreferenced inline function has been removed'
  #ifdef _DEBUG
    #include <crtdbg.h>/*
		void* operator new(size_t Size, const char * FileName, int Line)
		{
  		return ::operator new(Size, _NORMAL_BLOCK, FileName, Line);
		}*/
  #endif
#endif
