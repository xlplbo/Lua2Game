#ifndef __LUA_SCRIPT_H__
#define __LUA_SCRIPT_H__

#include "Global.h"
#include "Api4Lua.h"

class CLuaScript
{
public:
	CLuaScript();
	~CLuaScript();

public:
	bool	Initialize();
	bool	LoadScript(const char* szFileName);
	bool	CallFunction(char* cFuncName, int nResults, char* cFormat, va_list vlist);
	bool	CallFunction(const char* cFuncName, int nResults, char* cFormat, ...);

private:
	void	RegisterLuaLib();
	void	RegisterFunctions(TLua_Funcs Funcs[], int n);
	
private:
	lua_State*	m_LuaState;
};


#endif