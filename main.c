#include "lib/lua/src/lua.h"
#include "lib/lua/src/lualib.h"
#include "lib/lua/src/lauxlib.h"

int call_lua_add(lua_State *L) {
  // 获取add函数
  lua_getglobal(L, "add");
  // 第一个操作数入栈
  lua_pushnumber(L, 123);
  // 第二个操作数入栈
  lua_pushnumber(L, 456);

  if (lua_isfunction(L, -1) == LUA_OK) {
    // 调用函数，2个参数，1个返回值
    if (lua_pcall(L, 2, 1, 0) == LUA_OK) {
      // 获取栈顶元素（结果）
      int sum = (int) lua_tonumber(L, -1);
      // 栈顶元素出栈
      lua_pop(L, lua_gettop(L));
      return sum;
    }
  }

  return 0;
}

void call_lua_hello(lua_State *L) {
  lua_getglobal(L, "hello");
  if (lua_isfunction(L, -1)) {
    if (lua_pcall(L, 0, 1, 0) == LUA_OK) {
      lua_pop(L, lua_gettop(L));
    }
  }
}

int main(int argc, char **argv) {
  // 初始化Lua解释器
  lua_State *L = luaL_newstate();
  // 载入Lua所有函数库
  luaL_openlibs(L);

  // 执行文件中的代码
  if (luaL_dofile(L, "script.lua") == LUA_OK) {
    call_lua_hello(L);
    printf("%d\n", call_lua_add(L));
  }

  // 释放
  lua_close(L);
  return 0;
}
