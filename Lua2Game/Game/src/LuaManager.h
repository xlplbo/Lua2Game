#ifndef __LUA_MANAGER_H__
#define __LUA_MANAGER_H__

#include <map>
#include <set>
#include "LuaScript.h"

class CLuaManager
{
	struct TScriptNode
	{
		CLuaScript* pLuaScript;
		bool		bNeedReload;
	};
private:
	CLuaManager();
	~CLuaManager();

public:
	static CLuaManager& GetInstance();
	void			UnInitialize();
	CLuaScript*		GetScript(const char* szPath);
	bool			ExecuteScript(const char* szPath, const char*szFuncName, int nResults, char* cFormat, ...);
	bool			AddIncludeSet(unsigned nScriptId);
	void			ClearIncludeSet();
	void			ReloadAlScript();

private:
	typedef std::map<unsigned, TScriptNode>	MAP_LUASCRIPT;
	typedef std::map<unsigned, TScriptNode>::iterator MAP_LUASCRIPT_IT;
	MAP_LUASCRIPT		m_ScriptMap;
	std::set<unsigned>	m_IncludeSet;
};


#endif