/*----------------------------------------------------------------
// Copyright 2021
// All rights reserved.
//
// author: 404558965@qq.com (xiaoquanjie)
//----------------------------------------------------------------*/

#pragma once

#include "common/async/redis/async_redis.h"
#include <map>

namespace co_async {
namespace redis {

int getWaitTime();

void setWaitTime(int wait_time);

int execute(const std::string& uri, 
    const async::redis::BaseRedisCmd& cmd, 
    async::redis::async_redis_cb cb);

// 无需返回值
int execute(const std::string& uri, 
    const async::redis::BaseRedisCmd& cmd);

int execute(const std::string& uri, 
    const async::redis::BaseRedisCmd& cmd, 
    long long& result);

int execute(const std::string& uri, 
    const async::redis::BaseRedisCmd& cmd, 
    std::string& result);

int execute(const std::string& uri, 
    const async::redis::BaseRedisCmd& cmd, 
    bool& result);

// get array
template<typename T>
int execute(const std::string& uri, 
    const async::redis::BaseRedisCmd& cmd, 
    T& result);

// get map
template<typename T1, typename T2>
int execute(const std::string& uri, 
    const async::redis::BaseRedisCmd& cmd, 
    std::map<T1, T2>& result);

// get scan result
template<typename T>
int execute(const std::string& uri, 
    const async::redis::BaseRedisCmd& cmd, 
    long long& cursor, 
    T& result);

} // redis
} // co_async