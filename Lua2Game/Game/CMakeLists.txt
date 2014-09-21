cmake_minimum_required (VERSION 2.6)
project (game)
ADD_EXECUTABLE(game 
	src/main.cpp 
	src/Api4Lua.cpp 
	src/Core.cpp 
	src/Global.cpp 
	src/LuaManager.cpp 
	src/LuaScript.cpp
)
INCLUDE_DIRECTORIES(include/lua)
TARGET_LINK_LIBRARIES(game /usr/local/lib/liblua.a)
