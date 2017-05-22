/*
 * 静态字符串。
 * 由字符串数据和其长度组成。兼容C字符串（以\0结尾）。
 * 不能动态分配空间，可作为动态字符串的基类。
 */
#ifndef _UTILS_STRING_H
#define _UTILS_STRING_H

#include <cstring>
#include <cstdint>
#include <cstdarg>
#include <cstdio>

namespace utils {
    class String {
    public:
        String(char *data, const uint32_t capacity) {
            mCapacity = capacity;
            mLen = 0;
            mBuffer = data;
            terminate();
        }
        String& operator=(const String& str) {
            strncpy(mBuffer, str.mBuffer, mCapacity);
            mLen = (str.mLen >= mCapacity)? (mCapacity - 1): str.mLen;
            terminate();
            return *this;
        }
        String& operator=(const char *s) {
            strncpy(mBuffer, s, mCapacity);
            terminateAtBufferEnd();
            mLen = strlen(mBuffer);
            return *this;
        }
        bool operator==(const String& str) {
            return (mLen == str.mLen) && ((mLen == 0) || (strncmp(mBuffer, str.mBuffer, mLen) == 0));
        }
        bool operator==(const char *s) {
            return (strcmp(mBuffer, s) == 0);
        }
        bool operator!=(const String& str) {
            return (mLen != str.mLen) || ((mLen != 0) && (strncmp(mBuffer, str.mBuffer, mLen) != 0));
        }
        bool operator!=(const char *s) {
            return (strcmp(mBuffer, s) != 0);
        }
        bool isStartWith(const String& str) {
            if ((str.mLen == 0) || (mLen < str.mLen))
                return false;
            return (strncmp(mBuffer, str.mBuffer, str.mLen) == 0);
        }
        bool isStartWith(const char *s) {
            return (strncmp(mBuffer, s, strlen(s)) == 0);
        }
        bool isEndWith(const String& str) {
            if ((str.mLen == 0) || (mLen < str.mLen))
                return false;
            return (strncmp(mBuffer + mLen - str.mLen, str.mBuffer, str.mLen) == 0);
        }
        uint32_t append(const String& str) {
            if (str.mLen == 0) return 0;
            uint32_t oldLen = mLen;
            strncpy(mBuffer + mLen, str.mBuffer, mCapacity - mLen);
            if (mLen + str.mLen >= mCapacity) {
                // TODO: log it as info!
                mLen = mCapacity - 1;
            } else {
                mLen = mLen + str.mLen;
            }
            terminate();
            return mLen - oldLen;
        }
        uint32_t append(const char *format, va_list args) {
            int oldLen = mLen;
            int nChars = vsnprintf(mBuffer + mLen, mCapacity - mLen, format, args);
            if (nChars < 0) {
                // TODO: log it as warning!
                terminate();
            } else if (static_cast<uint32_t >(nChars) >= mCapacity - mLen) {
                // TODO: log it as info!
                terminateAtBufferEnd();
                mLen = mCapacity - 1;
            } else {
                mLen += nChars;
            }
            return mLen - oldLen;
        }
        uint32_t append(const char *format, ...) {
            va_list args;
            va_start(args, format);
            uint32_t nChars = append(format, args);
            va_end(args);
            return nChars;
        }
        char *toCStyle() const { return mBuffer; }
        uint32_t length() { return mLen; }
        uint32_t capacity() { return mCapacity; }
        ~String() {}
    private:
        const char *LOG_TAG = "String";
        uint32_t mCapacity;
        uint32_t mLen;
        char *mBuffer;

        void terminate() { mBuffer[mLen] = '\0'; }
        void terminateAtBufferEnd() { mBuffer[mCapacity - 1] = '\0'; }
    };
}

#endif //_UTILS_STRING_H
