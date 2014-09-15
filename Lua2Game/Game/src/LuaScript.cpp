#include <iostream>
#include "LuaScript.h"

CLuaScript::CLuaScript()
{
	m_LuaState = luaL_newstate();
	if (!m_LuaState)
	{
		std::cout << "m_LuaState new state failed!" << std::endl;
		return;
	}
	RegisterLuaLib();//注册lua标准库
	RegisterFunctions(g_GameFunc);//注册c++脚本接口
	m_IsLoadScript = false;
}

CLuaScript::~CLuaScript()
{
	if (m_LuaState)
	{
		lua_close(m_LuaState);
		m_LuaState = NULL;
	}
	m_IsLoadScript = false;
}

void CLuaScript::RegisterLuaLib()
{
	if (!m_LuaState)
	{
		return;
	}
	luaL_openlibs(m_LuaState);
}

bool CLuaScript::RegisterFunctions(TLua_Funcs Funcs[], int n /*= 0*/)
{
	if (!m_LuaState)
	{
		return false;
	}
	if (n == 0)
		n = sizeof(Funcs) / sizeof(Funcs[0]);
	for (int i = 0; i < n; i++)
		lua_register(m_LuaState, Funcs[i].name, Funcs[i].func);
	return true;
}

bool CLuaScript::LoadScript(const char* szFileName)
{
	if (!szFileName || szFileName[0] == '\0')
	{
		std::cout << "Lua script file illegal!" << std::endl;
		return false;
	}
	if (!m_LuaState)
		return false;

	m_IsLoadScript = luaL_dofile(m_LuaState, szFileName);
	/*if (!m_IsLoadScript)
	{
		std::cout << "LUA_LOAD_ERROR:"<< lua_tostring(m_LuaState, -1) << std::endl;
		lua_pop(m_LuaState, 1);
	}*/
	return m_IsLoadScript;
}

bool CLuaScript::CallFunction(char* cFuncName, int nResults, char* cFormat, va_list vlist)
{
	if (!m_LuaState || !m_IsLoadScript)
		return false;

	double	nNumber		= 0;
	int		nInteger	= 0;
	char*	cString		= NULL;
	void*	pPoint		= NULL;
	int		i			= 0;
	int		nArgnum		= 0;
	lua_CFunction CFunc = NULL;

	lua_getglobal(m_LuaState, cFuncName); //在堆栈中加入需要调用的函数名

	while (cFormat[i] != '\0')
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
		std::cout << "LUA_CALL_FUNC_ERROR<" << cFuncName << ">:" << lua_tostring(m_LuaState, -1) << std::endl;
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