#ifndef _UTILS_ERRORS_H
#define _UTILS_ERRORS_H

#include <cstdint>
#include <cerrno>
#include "config.h"

namespace utils {

    typedef int32_t status_t;

    enum {
        OK = 0,
        NO_ERROR = 0,
        UNKNOWN_ERROR = INT32_MIN,
        NO_MEMORY = -ENOMEM,
        PERMISSION_DENIED = -EPERM,
        BAD_VALUE = -EINVAL,
    };

}

#endif //_UTILS_ERRORS_H
