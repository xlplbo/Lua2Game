#include "Core.h"
#include <time.h>
#include <iostream>
using namespace std;

CCore g_Core;

CCore::CCore()
{
	m_Script = NULL;
	m_bIsRuning = true;
}

CCore::~CCore()
{
	if (m_Script)
	{
		delete m_Script;
		m_Script = NULL;
	}
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
	if (now - c > 3)
	{
		c = now;
		if (!m_Script)
		{
			m_Script = new CLuaScript;
		}		
		if (m_Script)
		{
			m_Script->LoadScript("\\script\\test.lua");
			m_Script->CallFunction("main", 1, "sdd", "luaer", c, c / 18);
		}
		else
		{
			std::cout << "new CLuaScript failed!" << std::endl;
			m_bIsRuning = false;
		}
	}
	return true;
}