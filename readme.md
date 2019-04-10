Title - Redis - Writing your first helloworld redis module

Description - Your first helloworld redis module which echo user inputs

*Steps to Install*

Step 1 - Compile the code
- Create redis-module-helloworld directory
- Copy the code files in redis-module-helloworld directory
- Execute following command to compile (install gcc compiler if not exists)
- gcc -fPIC -shared -std=gnu99 -o sdk_module.o sdk_module.c

Step 2 - Include Module to redis (we will use redis-cli, there are other was to to include modules)
- Make sure you redis server is running (>= redis 5.x)
- Go to redis-cli
- Execute MODULE LOAD /path/to/sdk_module.so

Step 3 - Test module
- Go to redis-cli and execute your command
- 127.0.0.1:6379> sdk.module.helloworld "your input string"
- "your input string"
127.0.0.1:6379> 

* Reference - https://redis.io/topics/modules-intro
