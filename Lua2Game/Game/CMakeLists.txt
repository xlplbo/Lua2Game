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
#find_path(header lua.h)
#if(header)
#include_directories(${header})
#endif(header)
#LINK_DIRECTORIES(/home/liubo5/Desktop/Lua2Game/Lua2Game/build/LuaDll)
TARGET_LINK_LIBRARIES(game lualib)

