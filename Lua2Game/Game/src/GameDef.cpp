#include "GameDef.h"
#include <direct.h>
#include <iostream>
using namespace std;

void g_GetRootPath(char * szRootpath, int nSize)
{
	getcwd(szRootpath, nSize);
}

int LuaSayHello(lua_State* L)
{
	cout << "Hello Everyone!" << endl;
	return 0;
}

int LuaStopGame(lua_State* L)
{
	cout << "Lua call function(StopGame())" << endl;
	cout << "Game is over!" << endl;
	return 0;
}

//½Å±¾½Ó¿Ú
TLua_Funcs g_GameFunc[] = {
	{ "SayHello", LuaSayHello },
	{ "StopGame", LuaStopGame },
};