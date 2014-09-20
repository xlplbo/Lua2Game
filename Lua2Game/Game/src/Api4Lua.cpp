#include <direct.h>
#include <iostream>
#include "Api4lua.h"
#include "Global.h"
#include "Core.h"
#include "LuaManager.h"

int LuaInclude(lua_State* L)
{
	const char* szFileName	= NULL;
	char szPath[128]		= "";
	unsigned nScriptId		= 0;

	if (lua_gettop(L) < 1)
		goto POINT;
	if (!lua_isstring(L, 1))
		goto POINT;
	
	szFileName = lua_tostring(L, 1);
	if (!szFileName || szFileName[0] == '\0')
		goto POINT;

	nScriptId = g_FileNameHash(szFileName);
	if (!CLuaManager::GetInstance().AddIncludeSet(nScriptId))
		goto POINT;

	//printf("Include('%s')\n", szFileName);

	getcwd(szPath, sizeof(szPath));
	strncat(szPath, szFileName, strlen(szFileName));
	if (luaL_dofile(L, szPath) != LUA_OK)
	{
		printf("LUA_LOAD_ERROR: %s\n", lua_tostring(L, -1));
		lua_pop(L, 1);
		goto POINT;
	}

	lua_pushnumber(L, 1);
	return 1;
POINT:
	lua_pushnil(L);
	return 0;
}

int LuaReloadAllScript(lua_State* L)
{
	//释放所有的lua_State
	//脚本调用是异步的，有可能导致lua_State已释放，仍然使用！！！
	//这个问题已解决
	CLuaManager::GetInstance().ReloadAllScript();
	return 0;
}

int LuaSayHello(lua_State* L)
{
	printf("Lua call c/c++:SayHello()\n");
	printf("Hello Everyone!\n");
	if (lua_gettop(L) < 3)
		return 0;
	const char* szName = lua_tostring(L, 1);
	int nParam1 = lua_tonumber(L, 2);
	int nParam2 = lua_tonumber(L, 3);
	printf("My name is %d\n", szName);
	lua_pushnumber(L, nParam1 / nParam2);
	return 1;
}

int LuaStopGame(lua_State* L)
{
	printf("Lua call c/c++:StopGame()\n");
	printf("Game is over!\n");
	g_Core.SetRunState(false);
	return 0;
}

//脚本接口
TLua_Funcs g_GameFunc[] = {
	{ "Include",				LuaInclude },
	{ "ReloadAllScript",		LuaReloadAllScript},
	{ "SayHello",				LuaSayHello },
	{ "StopGame",				LuaStopGame },
};

int g_GetGameFuncSize()
{
	return sizeof(g_GameFunc) / sizeof(TLua_Funcs);
}

