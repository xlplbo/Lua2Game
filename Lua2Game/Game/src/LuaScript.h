#ifndef __LUA_SCRIPT_H__
#define __LUA_SCRIPT_H__

#include <set>
#include "GameDef.h"

class CLuaScript
{
public:
	CLuaScript();
	~CLuaScript();

public:
	bool	LoadScript(const char* szFileName);
	bool	CallFunction(char* cFuncName, int nResults, char* cFormat, va_list vlist);
	bool	CallFunction(const char* cFuncName, int nResults, char* cFormat, ...);

private:
	void	RegisterLuaLib();
	bool	RegisterFunctions(TLua_Funcs Funcs[], int n);
	
private:
	lua_State*	m_LuaState;
	bool		m_IsLoadScript;

public:
	static bool	AddIncludeSet(unsigned nScriptId);
	static void	ClearIncludeSet();
	static bool AddGlobalSet(unsigned nScriptId);

private:
	static std::set<unsigned> m_IncludeSet;
	static std::set<unsigned> m_GlobalSet;
};


#endif