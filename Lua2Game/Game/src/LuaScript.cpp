#include <iostream>
#include "LuaScript.h"
#include <direct.h>

CLuaScript::CLuaScript():
m_LuaState(NULL)
{
}

CLuaScript::~CLuaScript()
{
	if (m_LuaState)
	{
		lua_close(m_LuaState);
		m_LuaState = NULL;
	}
}

bool CLuaScript::Initialize()
{
	m_LuaState = luaL_newstate();
	if (!m_LuaState)
	{
		printf("m_LuaState new state failed!\n");
		return false;
	}
	RegisterLuaLib();//注册lua标准库
	RegisterFunctions(g_GameFunc, g_GetGameFuncSize());//注册c\c++脚本接口
	return true;
}


void CLuaScript::RegisterLuaLib()
{
	if (!m_LuaState)
		return;
	luaL_openlibs(m_LuaState);
}

void CLuaScript::RegisterFunctions(TLua_Funcs Funcs[], int n)
{
	if (!m_LuaState)
		return;
	for (int i = 0; i < n; i++)
		lua_register(m_LuaState, Funcs[i].name, Funcs[i].func);
}

bool CLuaScript::LoadScript(const char* szFileName)
{
	if (!szFileName || szFileName[0] == '\0')
	{
		printf("Lua script file illegal!\n");
		return false;
	}
	if (!m_LuaState)
		return false;

	char szPath[128] = "";
	getcwd(szPath, sizeof(szPath));
	strncat(szPath, szFileName, strlen(szFileName));
	bool bRet = (luaL_dofile(m_LuaState, szPath) == LUA_OK);
	if (!bRet)
	{
		printf("LUA_LOAD_ERROR [%s] %s\n", szPath, lua_tostring(m_LuaState, -1));
		lua_pop(m_LuaState, 1);
	}
	return bRet;
}

bool CLuaScript::CallFunction(char* cFuncName, int nResults, char* cFormat, va_list vlist)
{
	if (!m_LuaState)
		return false;

	double	nNumber		= 0;
	int		nInteger	= 0;
	char*	cString		= NULL;
	void*	pPoint		= NULL;
	int		i			= 0;
	int		nArgnum		= 0;
	lua_CFunction CFunc = NULL;

	lua_getglobal(m_LuaState, cFuncName); //在堆栈中加入需要调用的函数名

	while (cFormat && cFormat[i] != '\0')
	{
		switch (cFormat[i])
		{
		case 'n'://输入的数据是double形 NUMBER，Lua来说是Double型
		{
			nNumber = va_arg(vlist, double);
			lua_pushnumber(m_LuaState, nNumber);
			nArgnum++;
		}
		break;

		case 'd'://输入的数据为整形
		{
			nInteger = va_arg(vlist, int);
			lua_pushinteger(m_LuaState, nInteger);
			nArgnum++;
		}
		break;

		case 's'://字符串型
		{
			cString = va_arg(vlist, char *);
			lua_pushstring(m_LuaState, cString);
			nArgnum++;
		}
		break;

		case 'N'://NULL
		{
			lua_pushnil(m_LuaState);
			nArgnum++;
		}
		break;

		case 'f'://输入的是CFun形，即内部函数形
		{
			CFunc = va_arg(vlist, lua_CFunction);
			lua_pushcfunction(m_LuaState, CFunc);
			nArgnum++;
		}
		break;

		case 'v'://输入的是堆栈中Index为nIndex的数据类型
		{
			nNumber = va_arg(vlist, int);
			int nIndex1 = (int)nNumber;
			lua_pushvalue(m_LuaState, nIndex1);
			nArgnum++;
		}
		break;
		
		}

		i++;
	}

	int nRetcode = lua_pcall(m_LuaState, nArgnum, nResults, 0);

	if (nRetcode != 0)
	{
		printf("LUA_CALL_FUNC_ERROR [%s] %s\n", cFuncName, lua_tostring(m_LuaState, -1));
		lua_pop(m_LuaState, 1);
		return false;
	}

	return	true;
}


bool CLuaScript::CallFunction(const char* cFuncName, int nResults, char* cFormat, ...)
{
	bool bResult = false;
	va_list vlist;
	va_start(vlist, cFormat);
	bResult = CallFunction((char*)cFuncName, nResults, cFormat, vlist);
	va_end(vlist);
	return bResult;
}
