#ifndef __CORE_H__
#define __CORE_H__

#include "GameDef.h"
#include "LuaScript.h"

class CCore
{
public:
	CCore();
	~CCore();

public:
	bool	Initialize();
	void	Uninitialize();
	bool	Breathe();
	void	SetRunState(bool bRunning);

private:
	CLuaScript* m_Script;
	bool		m_bIsRuning;
};

extern CCore g_Core;

#endif