#include "GameDef.h"
#include <direct.h>
#include <iostream>
#include "Core.h"
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

//½Å±¾½Ó¿Ú
TLua_Funcs g_GameFunc[] = {
	{ "SayHello", LuaSayHello },
	{ "StopGame", LuaStopGame },
};

int g_GetGameFuncSize()
{
	return sizeof(g_GameFunc) / sizeof(TLua_Funcs);
}