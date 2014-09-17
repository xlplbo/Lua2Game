#include "GameDef.h"
#include <direct.h>
#include <iostream>
#include "Core.h"
#include "LuaScript.h"
using namespace std;


int LuaSayHello(lua_State* L)
{
	cout << "Lua call c/c++:SayHello()" << endl;
	cout << "Hello Everyone!" << endl;
	if (lua_gettop(L) < 3)
		return 0;
	const char* szName = lua_tostring(L, 1);
	int nParam1 = lua_tonumber(L, 2);
	int nParam2 = lua_tonumber(L, 3);
	cout << "My name is " << szName << endl;
	lua_pushnumber(L, nParam1 / nParam2);
	return 1;
}

int LuaStopGame(lua_State* L)
{
	cout << "Lua call c/c++:StopGame()" << endl;
	cout << "Game is over!" << endl;
	g_Core.SetRunState(false);
	return 0;
}

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
		goto POINT;;
	
	nScriptId = g_FileNameHash(szFileName);
	if (!CLuaScript::AddIncludeSet(nScriptId))
		goto POINT;

	getcwd(szPath, sizeof(szPath));
	strncat(szPath, szFileName, strlen(szFileName));
	if (luaL_dofile(L, szPath) != LUA_OK)
	{
		cout << "<LUA_LOAD_ERROR>" << lua_tostring(L, -1) << endl;
		lua_pop(L, 1);
		goto POINT;
	}

	lua_pushnumber(L, 1);
	return 1;
POINT:
	lua_pushnil(L);
	return 0;
}

//½Å±¾½Ó¿Ú
TLua_Funcs g_GameFunc[] = {
	{ "Include",	LuaInclude },
	{ "SayHello",	LuaSayHello },
	{ "StopGame",	LuaStopGame },
};

int g_GetGameFuncSize()
{
	return sizeof(g_GameFunc) / sizeof(TLua_Funcs);
}

unsigned g_FileNameHash(const char* pString)
{
	unsigned int Id = 0;
	char c = 0;
	for (int i = 0; pString[i]; i++)
	{
		c = pString[i];
		if (c >= 'A' && c <= 'Z')
			c += 0x20;
		else if (c == '/')
			c = '\\';
		Id = (Id + (i + 1) * c) % 0x8000000b * 0xffffffef;
	}
	return (Id ^ 0x12345678);
}