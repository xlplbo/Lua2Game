#ifndef __GAME_DEF_H__
#define __GAME_DEF_H__

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
extern unsigned g_FileNameHash(const char* pString);

#endif