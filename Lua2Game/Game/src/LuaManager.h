#ifndef __LUA_MANAGER_H__
#define __LUA_MANAGER_H__

#include <map>
#include <set>
#include "LuaScript.h"

class CLuaManager
{
private:
	CLuaManager();
	~CLuaManager();

public:
	static CLuaManager& GetInstance();
	void		UnInitialize();
	CLuaScript*	GetScript(const char* szPath);
	CLuaScript*	GetScript(unsigned nScriptId);
	bool		ExecuteScript(const char* szPath, const char*szFuncName, int nResults, char* cFormat, ...);
	bool		AddIncludeSet(unsigned nScriptId);
	void		ClearIncludeSet();

private:
	typedef std::map<unsigned, CLuaScript*>	MAP_LUASCRIPT;
	typedef std::map<unsigned, CLuaScript*>::iterator MAP_LUASCRIPT_IT;
	MAP_LUASCRIPT m_ScriptMap;
	std::set<unsigned> m_IncludeSet;
};


#endif