#ifdef _MSC_VER
	#include "NewDebug.h"
	#ifdef _DEBUG
	/*WARNING: no matching operator delete found; memory will not be freed if initialization throws an exception*/
	#pragma warning(disable: 4291) 
	#define new NEW_DEBUG
	#endif
#endif
