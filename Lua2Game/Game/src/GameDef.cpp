#include "GameDef.h"
#include <direct.h>

void g_GetRootPath(char * szRootpath, int nSize)
{
	getcwd(szRootpath, nSize);
}