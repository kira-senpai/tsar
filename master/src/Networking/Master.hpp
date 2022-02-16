#ifndef _TRACKER_
#define _TRACKER_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Master {
private:
    int port;
    sockaddr_in servAddr;
    int servSocket;
public:
    bool Init(int);
    void Listen();
};

#endif