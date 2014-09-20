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
		delete it->second.pLuaScript;
	}
	m_ScriptMap.clear();
	ClearIncludeSet();
}

CLuaScript* CLuaManager::GetScript(const char* szPath)
{
	if (!szPath || szPath[0] == '\0')
		return NULL;

	TScriptNode tScriptNode = {0};
	CLuaScript* pLuaScript	= NULL;
	unsigned nScriptId		= g_FileNameHash(szPath);
	MAP_LUASCRIPT_IT it		= m_ScriptMap.find(nScriptId);
	if (it != m_ScriptMap.end())
	{
		pLuaScript = it->second.pLuaScript;
		if (it->second.bNeedReload) /*need to reload*/
		{
			delete pLuaScript;
			m_ScriptMap.erase(it);
			goto POINT1;
		}
		return pLuaScript; /*is exsit*/
	}
	
POINT1: /*new lua_state*/
	pLuaScript = new CLuaScript;
	if (!pLuaScript || !pLuaScript->Initialize())
		goto POINT2;

	ClearIncludeSet();
	AddIncludeSet(nScriptId);
	if (!pLuaScript->LoadScript(szPath))
		goto POINT2;

	tScriptNode.pLuaScript = pLuaScript;
	tScriptNode.bNeedReload = false;
	if (!m_ScriptMap.insert(MAP_LUASCRIPT::value_type(nScriptId, tScriptNode)).second)
		goto POINT2;

	return pLuaScript;

POINT2: /*init failed*/
	delete pLuaScript;
	return NULL;
}

bool CLuaManager::ExecuteScript(const char* szPath, const char* szFuncName, int nResults /*= 0*/, char* cFormat /*= NULL*/, ...)
{
	if (!szPath || szPath[0] == '\0' || !szFuncName || szFuncName[0] == '\0')
	{
		printf("Param ERROR : %s : %s\n", szPath ? szPath : NULL, szFuncName ? szFuncName : NULL);
		return false;
	}
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

void CLuaManager::ReloadAllScript()
{
	int nCount = 0;
	for (MAP_LUASCRIPT_IT it = m_ScriptMap.begin(); it != m_ScriptMap.end(); ++it)
	{
		if (it->second.pLuaScript)
		{
			it->second.bNeedReload = true;
			nCount++;
		}
	}
	printf("Reload All Script Count = %d!\n", nCount);
}