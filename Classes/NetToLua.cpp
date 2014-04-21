/*
** Lua binding: net
** Generated automatically by tolua++-1.0.92 on 02/21/14 13:55:50.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
#include "tolua_fix.h"
#include "Net.h"

/* Exported function */
TOLUA_API int  tolua_net_open (lua_State* tolua_S);


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Net");
 tolua_usertype(tolua_S,"Node");
}

/* method: getInstance of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_getInstance00
static int tolua_net_Net_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Net* tolua_ret = (Net*)  Net::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Net");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connect of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_connect00
static int tolua_net_Net_connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Net* self = (Net*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  int port = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'connect'", NULL);
#endif
  {
   self->connect(ip,port);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addListener of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_addListener00
static int tolua_net_Net_addListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Net* self = (Net*)  tolua_tousertype(tolua_S,1,0);
  const char* event = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addListener'", NULL);
#endif
  {
   self->addListener(event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeListener of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_removeListener00
static int tolua_net_Net_removeListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Net* self = (Net*)  tolua_tousertype(tolua_S,1,0);
  const char* event = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeListener'", NULL);
#endif
  {
   self->removeListener(event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pomeloNotify of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_pomeloNotify00
static int tolua_net_Net_pomeloNotify00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Net* self = (Net*)  tolua_tousertype(tolua_S,1,0);
  const char* route = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* str = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pomeloNotify'", NULL);
#endif
  {
   self->pomeloNotify(route,str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pomeloNotify'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pomeloRequest of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_pomeloRequest00
static int tolua_net_Net_pomeloRequest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Net* self = (Net*)  tolua_tousertype(tolua_S,1,0);
  const char* route = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* str = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pomeloRequest'", NULL);
#endif
  {
   self->pomeloRequest(route,str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pomeloRequest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: httpRequest of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_httpRequest00
static int tolua_net_Net_httpRequest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     //!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Net* self = (Net*)  tolua_tousertype(tolua_S,1,0);
  std::string url = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  //int cbFunc = ((int)  tolua_tonumber(tolua_S,3,0));
  LUA_FUNCTION cbFunc = (  toluafix_ref_function(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'httpRequest'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->httpRequest(url,cbFunc);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)url);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'httpRequest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerOnMsgLuaCallBack of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_registerOnMsgLuaCallBack00
static int tolua_net_Net_registerOnMsgLuaCallBack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Net",0,&tolua_err) ||
     //!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
  	 !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Net* self = (Net*)  tolua_tousertype(tolua_S,1,0);
  //int luaCallback = ((int)  tolua_tonumber(tolua_S,2,0));
  LUA_FUNCTION luaCallback = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerOnMsgLuaCallBack'", NULL);
#endif
  {
   self->registerOnMsgLuaCallBack(luaCallback);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerOnMsgLuaCallBack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_net_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Net","Net","Node",NULL);
  tolua_beginmodule(tolua_S,"Net");
   tolua_function(tolua_S,"getInstance",tolua_net_Net_getInstance00);
   tolua_function(tolua_S,"connect",tolua_net_Net_connect00);
   tolua_function(tolua_S,"addListener",tolua_net_Net_addListener00);
   tolua_function(tolua_S,"removeListener",tolua_net_Net_removeListener00);
   tolua_function(tolua_S,"pomeloNotify",tolua_net_Net_pomeloNotify00);
   tolua_function(tolua_S,"pomeloRequest",tolua_net_Net_pomeloRequest00);
   tolua_function(tolua_S,"httpRequest",tolua_net_Net_httpRequest00);
   tolua_function(tolua_S,"registerOnMsgLuaCallBack",tolua_net_Net_registerOnMsgLuaCallBack00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_net (lua_State* tolua_S) {
 return tolua_net_open(tolua_S);
};
#endif