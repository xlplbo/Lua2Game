#include <iostream>
#include <time.h>
#include "Core.h"
#include "LuaManager.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

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
	static size_t nCount = 0;
	if (nCount % 5 == 0)
	{
		size_t c = time(NULL);
		CLuaManager::GetInstance().ExecuteScript("\\script\\test.lua", "main", 1, "sdd", "luaer", c, c / 18);
		CLuaManager::GetInstance().ExecuteScript("\\script\\test1.lua", "test");
		printf("------------- %lds -----------\n", nCount);
	}
	++ nCount;
#ifdef _WIN32
	Sleep(1000);
#else
	sleep(1);
#endif
	return true;
}
