#ifndef __LUA_SCRIPT_H__
#define __LUA_SCRIPT_H__

#include <map>
#include "GameDef.h"

class CScriptNode
{
public:
	CScriptNode();
	~CScriptNode();

private:

};

class CLuaScript
{
public:
	CLuaScript();
	~CLuaScript();

public:
	bool LoadScript(const char* szRootPath, const char* szFilePath);

private:
	std::map<size_t, CScriptNode> m_ScriptTree;
};


#endif