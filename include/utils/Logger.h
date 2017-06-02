/*
 * VERBOSE: 开发阶段的详细信息，不应该被编译进产品
 * DEBUG: 调试信息，编译进产品，但可以被关闭
 * INFO: 运行时的状态信息，当出现问题时能提供帮助
 * WARN: 警告系统出现了异常，即将出现错误
 * ERROR: 系统出现了错误
 */
#ifndef _UTILS_LOG_H
#define _UTILS_LOG_H

#include <cstdarg>
#include "utils/String.h"
#include "utils/List.h"
#include "DynamicList.h"

namespace utils {

    enum {
        LOG_ERROR = 0,
        LOG_WARN,
        LOG_INFO,
        LOG_DEBUG,
        LOG_VERBOSE,
    };

    class ILogFormatter {
    public:
        virtual ~ILogFormatter() = 0;

        virtual void format(String &buffer,
                            uint32_t level, const char *tag, const char *format, va_list args) = 0;
    };

    class NormalLogFormatter : public ILogFormatter {
    public:
        void format(String &buffer,
                    uint32_t level, const char *tag, const char *format, va_list args);
    };

    class ILogHandler {
    public:
        virtual ~ILogHandler() = 0;

        virtual void handle(String &buffer) = 0;
    };

    class FileLogHandler : public ILogHandler {
    public:
        void handle(String &buffer);

        FileLogHandler(uint32_t fd);

        FileLogHandler(const char *filePath, uint32_t fileMode);

    private:
        char *mFilePath;
        uint32_t mFileMode;
        int mFD;
    };

    class Logger {
    public:
        static Logger *getInstance();

        ~Logger();

        void log(uint32_t level, const char *tag, const char *format, va_list args);

        Logger *setNormalFormatter();

        Logger *addFileHandler(uint32_t fd);

        Logger *addFileHandler(const char *filePath, uint32_t fileMode);

    private:
        static Logger *mInstance;
        ILogFormatter *mFormatter;
        DynamicList<ILogHandler *> mHandlers;

        Logger();

        Logger *setFormatter(ILogFormatter *formatter);

        Logger *addHandler(ILogHandler *handler);
    };

}

void LOG(uint32_t level, const char *tag, const char *format, ...);

void LOGE(const char *tag, const char *format, ...);

void LOGW(const char *tag, const char *format, ...);

void LOGI(const char *tag, const char *format, ...);

void LOGD(const char *tag, const char *format, ...);

void LOGV(const char *tag, const char *format, ...);

#endif //_UTILS_LOG_H
