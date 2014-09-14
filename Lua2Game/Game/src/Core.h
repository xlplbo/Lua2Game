#ifndef __CORE_H__
#define __CORE_H__

#include "GameDef.h"

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

};

extern CCore g_Core;

#endif