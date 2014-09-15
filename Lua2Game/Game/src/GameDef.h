#ifndef __GAME_DEF_H__
#define __GAME_DEF_H__

extern "C"{
#include "../../LuaDll/src/lapi.h"
#include "../../LuaDll/src/lua.h"
#include "../../LuaDll/src/lauxlib.h"
#include "../../LuaDll/src/lualib.h"
}

extern void g_GetRootPath(char * szRootpath, int nSize);
static bool g_bRunning = true;

struct TLua_Funcs
{
	const char *name;
	lua_CFunction func;
};

extern TLua_Funcs g_GameFunc[];
#endif