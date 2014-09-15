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

private:
	CLuaScript* m_Script;
};

extern CCore g_Core;

#endif