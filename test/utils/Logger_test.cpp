#include "gtest/gtest.h"
#include "utils/Logger.h"

#define LOG_TAG "LOGTEST"

using utils::Logger;

TEST(Logger, a) {
    Logger::getInstance()
            ->setNormalFormatter()
            ->addFileHandler(STDOUT_FILENO);
    LOGI(LOG_TAG, "3 + 2 = %d\n", 3 + 2);
    LOGI(LOG_TAG, "%s\n", "hello");
    LOGI(LOG_TAG, "hello world!\n");
}
