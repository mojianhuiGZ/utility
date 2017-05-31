//
// Created by root on 17-6-1.
//

#ifndef TTXNET_CONDITION_H
#define TTXNET_CONDITION_H

class Condition {
    Condition();
    ~Condition();
    wait(Mutex& mutex);
    waitRelative(Mutex& mutex, uint32_t reltime);
    void signal();
    void signal(WakeUpType type) {

    }
    void broadcast();
};


#endif //TTXNET_CONDITION_H
