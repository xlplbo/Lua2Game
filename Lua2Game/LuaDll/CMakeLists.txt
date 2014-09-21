cmake_minimum_required (VERSION 2.6)
project (lua)

# 1. lua static library
add_library (lualib STATIC 
src/lapi.c      src/lcorolib.c  src/ldump.c   src/llex.c      src/lopcodes.c  src/lstrlib.c  src/lundump.c
src/lauxlib.c   src/lctype.c    src/lfunc.c   src/lmathlib.c  src/loslib.c    src/ltable.c   src/lvm.c
src/lbaselib.c  src/ldblib.c    src/lgc.c     src/lmem.c      src/lparser.c   src/ltablib.c  src/lzio.c
src/lbitlib.c   src/ldebug.c    src/linit.c   src/loadlib.c   src/lstate.c    src/ltm.c
src/lcode.c     src/ldo.c       src/liolib.c  src/lobject.c   src/lstring.c   src/lua.c)
# rename the library output name
set_target_properties(lualib PROPERTIES OUTPUT_NAME "lua")

# 2. lua So library
add_library (luaso SHARED 
src/lapi.c      src/lcorolib.c  src/ldump.c   src/llex.c      src/lopcodes.c  src/lstrlib.c  src/lundump.c
src/lauxlib.c   src/lctype.c    src/lfunc.c   src/lmathlib.c  src/loslib.c    src/ltable.c   src/lvm.c
src/lbaselib.c  src/ldblib.c    src/lgc.c     src/lmem.c      src/lparser.c   src/ltablib.c  src/lzio.c
src/lbitlib.c   src/ldebug.c    src/linit.c   src/loadlib.c   src/lstate.c    src/ltm.c
src/lcode.c     src/ldo.c       src/liolib.c  src/lobject.c   src/lstring.c   src/lua.c)

# rename the library output name
set_target_properties(luaso PROPERTIES OUTPUT_NAME "lua")

# 3. lua interpreter
link_directories (${LUA_BINARY_DIR})
add_executable (lua src/lua.c)
target_link_libraries (lua lualib)
target_link_libraries (lua m)

# 4. lua compiler
#link_directories (${LUA_BINARY_DIR})
#add_executable (luac luac.c)
#target_link_libraries (luac lualib)

# 5. install
install(TARGETS 
	lualib 
	luaso
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
install(FILES 
	src/lua.h 
	DESTINATION include/lua
)
