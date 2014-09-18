#include "LuaManager.h"

CLuaManager::CLuaManager()
{
	UnInitialize();
}

CLuaManager::~CLuaManager()
{
	UnInitialize();
}

CLuaManager& CLuaManager::GetInstance()
{
	static CLuaManager ins;
	return ins;
}

void CLuaManager::UnInitialize()
{
	for (MAP_LUASCRIPT_IT it = m_ScriptMap.begin(); it != m_ScriptMap.end(); ++it)
	{
		if (it->second)
		{
			delete it->second;
			it->second = NULL;
		}
	}
	m_ScriptMap.clear();
	ClearIncludeSet();
}

CLuaScript* CLuaManager::GetScript(const char* szPath)
{
	CLuaScript* pLuaScript	= NULL;
	unsigned nScriptId		= 0;

	if (!szPath || szPath[0] == '\0')
		return NULL;

	nScriptId = g_FileNameHash(szPath);
	pLuaScript = GetScript(nScriptId);
	if (pLuaScript)
		return pLuaScript;
	
	pLuaScript = new CLuaScript;
	if (!pLuaScript || !pLuaScript->Initialize())
		goto POINT;

	ClearIncludeSet();
	if (!pLuaScript->LoadScript(szPath))
		goto POINT;

	if (!m_ScriptMap.insert(MAP_LUASCRIPT::value_type(nScriptId, pLuaScript)).second)
		goto POINT;

	return pLuaScript;

POINT:
	delete pLuaScript;
	return NULL;
}

CLuaScript* CLuaManager::GetScript(unsigned nScriptId)
{
	MAP_LUASCRIPT_IT it = m_ScriptMap.find(nScriptId);
	if (it != m_ScriptMap.end() && it->second)
		return it->second;
	return NULL;
}

bool CLuaManager::ExecuteScript(const char* szPath, const char* szFuncName, int nResults, char* cFormat, ...)
{
	CLuaScript* pLuaScript = GetScript(szPath);
	if (!pLuaScript)
		return false;
	
	bool bResult = false;
	va_list vlist;
	va_start(vlist, cFormat);
	bResult = pLuaScript->CallFunction((char*)szFuncName, nResults, cFormat, vlist);
	va_end(vlist);

	if (!bResult)
	{
		printf("Execute script [%s] [%s] failed!\n", szPath, szFuncName);
	}

	return bResult;
}

bool CLuaManager::AddIncludeSet(unsigned nScriptId)
{
	return m_IncludeSet.insert(nScriptId).second;
}

void CLuaManager::ClearIncludeSet()
{
	m_IncludeSet.clear();
}