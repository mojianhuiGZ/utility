//#include "utils/SocketListener.h"
//
//#define LOG_TAG "SocketListener"
//
//using namespace utils;
//
//SocketListener::SocketListener(const char *socketName, bool listen) {
//    init(socketName, -1, listen, false);
//}
//
//SocketListener::SocketListener(int socketFd, bool listen) {
//    init(NULL, socketFd, listen, false);
//}
//
//SocketListener::SocketListener(const char *socketName, bool listen, bool useCmdNum) {
//    init(socketName, -1, listen, useCmdNum);
//}
//
//void SocketListener::init(const char *socketName, int socketFd, bool listen, bool useCmdNum) {
//    mListen = listen;
//    mSocketName = socketName;
//    mSock = socketFd;
//    mUseCmdNum = useCmdNum;
//    pthread_mutex_init(&mClientsLock, NULL);
//    mClients = new SocketClientCollection();
//}
//
//SocketListener::~SocketListener() {
//    if (mSocketName && mSock > -1)
//        close(mSock);
//
//    if (mCtrlPipe[0] != -1) {
//        close(mCtrlPipe[0]);
//        close(mCtrlPipe[1]);
//    }
//    SocketClientCollection::iterator it;
//    for (it = mClients->begin(); it != mClients->end();) {
//        (*it)->decRef();
//        it = mClients->erase(it);
//    }
//    delete mClients;
//}
//
