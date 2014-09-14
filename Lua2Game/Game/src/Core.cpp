#include "Core.h"
#include "GameDef.h"

CCore g_Core;

CCore::CCore()
{

}

CCore::~CCore()
{

}

bool CCore::Initialize()
{
	char szRootPath[128] = "";
	g_GetRootPath(szRootPath, sizeof(szRootPath	));
	if (m_Script.LoadScript(szRootPath, SCRIPT_ROOT_PATH))
		return true;
	return false;
}

void CCore::Uninitialize()
{

}

bool CCore::Breathe()
{
	return true;
}