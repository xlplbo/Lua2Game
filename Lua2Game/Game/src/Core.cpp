#include <iostream>
#include <time.h>
#include "Core.h"
#include "LuaManager.h"

CCore g_Core;

CCore::CCore()
{
	m_bIsRuning = true;
}

CCore::~CCore()
{

}

bool CCore::Initialize()
{
	//do something
	return true;
}

void CCore::Uninitialize()
{
	//do something
}

void CCore::SetRunState(bool bRunning)
{
	m_bIsRuning = bRunning;
}

bool CCore::Breathe()
{
	if (!m_bIsRuning)
		return false;
	static size_t c = 0;
	size_t now = time(NULL);
	if (now - c > 5)
	{
		c = now;
		CLuaManager::GetInstance().ExecuteScript("\\script\\test.lua", "main", 1, "sdd", "luaer", c, c / 18);
		CLuaManager::GetInstance().ExecuteScript("\\script\\test1.lua", "test", 0, "");
	}
	return true;
}