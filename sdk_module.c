/*
* Title - Redis - Writing your first helloworld redis module
* Developer - Suyog Kale
* Description - Your first helloworld redis module which echo user inputs
* Test - Include module in your redis server and go to redis-cli then enter sdk.module.helloworld $your input$
* Reference - https://redis.io/topics/modules-intro
*/

/*
Include C header file called redismodule.h, its an api defination file
*/
#include "redismodule.h"
/*
To create a new command, It needs the context, the command name, and the function pointer of the function implementing the command, 
which must have the following prototype:
Prototype - int mycommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc);
Here - Your First HelloWorld function which will parse an user entered input and echo back to the user
*/
int HelloWorld(RedisModuleCtx *ctx, RedisModuleString **argv,int argc) {
  //Return an error if sufficient inputs are not provided
  if (argc != 2) {
    return RedisModule_WrongArity(ctx);
  }
  //Ask Redis to automatically manage the resource and memory in our command handler, by simply calling RedisModule_AutoMemory(ctx).
  RedisModule_AutoMemory(ctx);
  //Echo the user input
  return RedisModule_ReplyWithString(ctx, argv[1]);
}

/*
The Init function announces the Redis core that the module has a given name, its version (that is reported by MODULE LIST), and that is willing to use a specific version of the API.
If the API version is wrong, the name is already taken, or there are other similar errors, the function will return REDISMODULE_ERR, and the module OnLoad function should return ASAP with an error.
Before the Init function is called, no other API function can be called, otherwise the module will segfault and the Redis instance will crash
*/
int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {

  //Define your module name and version
  if (RedisModule_Init(ctx, "sdk.module", 1, REDISMODULE_APIVER_1) == REDISMODULE_ERR)
    return REDISMODULE_ERR;
  /*
  RedisModule_CreateCommand() - to register commands into the Redis core
  Prototype - int RedisModule_CreateCommand(RedisModuleCtx *ctx, const char *name, RedisModuleCmdFunc cmdfunc, const char *strflags, int firstkey, int lastkey, int keystep);
  Here we define your own command and configure your command function to process
  "readonly" - Here you are not writing or modifiying and data, so configure readonly permissions
  */
  if (RedisModule_CreateCommand(ctx, "sdk.module.helloworld", HelloWorld, "readonly", 1, 1, 1) == REDISMODULE_ERR)
    return REDISMODULE_ERR;

  return REDISMODULE_OK;

}
