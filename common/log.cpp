/*----------------------------------------------------------------
// Copyright 2022
// All rights reserved.
//
// author: 404558965@qq.com (xiaoquanjie)
//----------------------------------------------------------------*/

#include "common/log.h"
#include <stdarg.h>
#include <mutex>
#include <thread>
#include <sstream>
#include <time.h>
#include <iomanip>
//#include <chrono>

std::string curThreadId() {
    std::stringstream ss;
    ss << std::this_thread::get_id();
    return ss.str();
}

// 日志输出接口，是线程安全的
std::function<void(const char*)> gLogCb = [](const char* data) {
    static std::mutex sMutex;
    sMutex.lock();
    auto tp = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(localtime(&t), "%Y-%m-%d %H-%M-%S");
    printf("[%s] [%s] %s\n", curThreadId().c_str(), ss.str().c_str(), data);
    sMutex.unlock();
};

void log(const char* format, ...) {
    if (!gLogCb) {
        return;
    }

    char buf[1024] = { 0 };
    va_list ap;
    va_start(ap, format);
    vsprintf(buf, format, ap);
    gLogCb(buf);
}

void setSafeLogFunc(std::function<void(const char*)> cb) {
    gLogCb = cb;
}