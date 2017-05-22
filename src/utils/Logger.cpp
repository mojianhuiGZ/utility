#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include "utils/Logger.h"

using utils::String;
using utils::Logger;
using utils::ILogFormatter;
using utils::ILogHandler;
using utils::NormalLogFormatter;
using utils::FileLogHandler;

///////////////////////////////////////////////////////////////////////////////
// ILogHandler
///////////////////////////////////////////////////////////////////////////////

ILogFormatter::~ILogFormatter() {}

///////////////////////////////////////////////////////////////////////////////
// NormalLogFormatter
///////////////////////////////////////////////////////////////////////////////

void NormalLogFormatter::format(String &buffer, uint32_t level, const char *tag, const char *format, va_list args) {
    buffer.append("%s: ", tag);
    buffer.append(format, args);
}

///////////////////////////////////////////////////////////////////////////////
// ILogHandler
///////////////////////////////////////////////////////////////////////////////

ILogHandler::~ILogHandler() {}

///////////////////////////////////////////////////////////////////////////////
// FileLogHandler
///////////////////////////////////////////////////////////////////////////////

FileLogHandler::FileLogHandler(uint32_t fd) {
    mFD = fd;
    mFilePath = nullptr;
    mFileMode = 0;
}

FileLogHandler::FileLogHandler(const char *filePath, uint32_t fileMode) {
    mFilePath = (char *) filePath;
    fileMode |= S_IRUSR | S_IWUSR;
    mFileMode = fileMode;
    // 设置O_APPEND的目的是避免多进程不同步
    mFD = open(mFilePath, O_WRONLY | O_CREAT | O_APPEND, mFileMode);
}

void FileLogHandler::handle(String &buffer) {
    if (mFD < 0) return;
    int n;
    do {
        n = write(mFD, buffer.toCStyle(), buffer.length()); // 如果磁盘满了数据会丢失
    } while (n < 0 && n == EINTR);
}

///////////////////////////////////////////////////////////////////////////////
// Logger
///////////////////////////////////////////////////////////////////////////////

Logger *Logger::mInstance = nullptr;

Logger *Logger::getInstance() {
    if (mInstance == nullptr) {
        mInstance = new Logger();
    }
    return mInstance;
}

Logger::Logger() : mFormatter(nullptr), mHandlers() {}

Logger::~Logger() {
    if (mFormatter != nullptr)
        delete mFormatter;
}

Logger *Logger::setFormatter(ILogFormatter *formatter) {
    if (formatter != nullptr) {
        if (mFormatter != nullptr)
            delete mFormatter;
        mFormatter = formatter;
    }
    return this;
}

Logger *Logger::setNormalFormatter() {
    return setFormatter(new NormalLogFormatter());
}

Logger *Logger::addHandler(ILogHandler *handler) {
    if (handler != nullptr) {
        mHandlers.pushBack(handler);
    }
    return this;
}

Logger *Logger::addFileHandler(uint32_t fd) {
    return addHandler(new FileLogHandler(fd));
}

Logger *Logger::addFileHandler(const char *filePath, uint32_t fileMode) {
    mHandlers.pushBack(new FileLogHandler(filePath, fileMode));
    return this;
}

void Logger::log(uint32_t level, const char *tag, const char *format, va_list args) {
    char buf[1000];
    String b(buf, sizeof(buf));
    DynamicList<ILogHandler *>::Iterator it(mHandlers);

    mFormatter->format(b, level, tag, format, args);
    for (it = mHandlers.begin(); !it.isNull(); it++) {
        ILogHandler *h = *it.getVal();
        h->handle(b);
    }
}

//void Logger::log(uint32_t level, const char *tag, const char *format, ...) {
//    va_list args;
//    va_start(args, format);
//    log(level, tag, format, args);
//    va_end(args);
//}

///////////////////////////////////////////////////////////////////////////////
// Others
///////////////////////////////////////////////////////////////////////////////

void LOG(uint32_t level, const char *tag, const char *format, va_list args) {
    utils::Logger::getInstance()->log(level, tag, format, args);
}

void LOG(uint32_t level, const char *tag, const char *format, ...) {
    va_list args;
    va_start(args, format);
    LOG(level, tag, format, args);
    va_end(args);
}

void LOGE(const char *tag, const char *format, ...) {
    va_list args;
    va_start(args, format);
    LOG(utils::LOG_ERROR, tag, format, args);
    va_end(args);
}

void LOGW(const char *tag, const char *format, ...) {
    va_list args;
    va_start(args, format);
    LOG(utils::LOG_WARN, tag, format, args);
    va_end(args);
}

void LOGI(const char *tag, const char *format, ...) {
    va_list args;
    va_start(args, format);
    LOG(utils::LOG_INFO, tag, format, args);
    va_end(args);
}

void LOGD(const char *tag, const char *format, ...) {
    va_list args;
    va_start(args, format);
    LOG(utils::LOG_DEBUG, tag, format, args);
    va_end(args);
}

void LOGV(const char *tag, const char *format, ...) {
    va_list args;
    va_start(args, format);
    LOG(utils::LOG_VERBOSE, tag, format, args);
    va_end(args);
}
