#ifndef _UTILS_SOCKETLISTENER_H
#define _UTILS_SOCKETLISTENER_H

namespace utils {
    class SocketListener {
    public:
        SocketListener(const char *socketName, bool listen);
        SocketListener(int socketFd, bool listen);
        virtual ~SocketListener();
        int startListener();
        int startListener(int backlog);
        int stopListener();
    private:
    };
}

#endif //_UTILS_SOCKETLISTENER_H
