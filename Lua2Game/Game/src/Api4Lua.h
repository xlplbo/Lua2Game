#ifndef __API_4_LUA__
#define __API_4_LUA__

extern "C"{
#include "../../LuaDll/src/lua.h"
#include "../../LuaDll/src/lauxlib.h"
#include "../../LuaDll/src/lualib.h"
}


struct TLua_Funcs
{
	const char *name;
	lua_CFunction func;
};

extern TLua_Funcs g_GameFunc[];
extern int g_GetGameFuncSize();

#endif