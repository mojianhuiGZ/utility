#ifndef TTXNET_THREAD_H
#define TTXNET_THREAD_H

namespace utils {
    class Thread {
    public:
        Thread();
        ~Thread();
        run();
        requestExit();
        readyToRun();
        requestExitAndWait();
        join();
        isRunning();

    private:

    };
}

#endif //TTXNET_THREAD_H
