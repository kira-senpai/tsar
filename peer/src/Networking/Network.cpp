#include "Network.hpp"
#include <cstring>
#include <unistd.h>
#include <poll.h>
#include <ifaddrs.h>
#include <arpa/inet.h>

sockaddr_in Network::peerAddr;
int Network::peerSock = -1;
int Network::peerBind = -1;
bool Network::isRunning = false;
thread Network::acceptThread;

vector<string> Network::GetIP4() {
    struct ifaddrs * ifAddrStruct=NULL;
    getifaddrs(&ifAddrStruct);

    vector<string> data = vector<string>();

    for (struct ifaddrs* ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET)
            continue;
 
        char addressBuffer[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &((struct sockaddr_in*)ifa->ifa_addr)->sin_addr, addressBuffer, INET_ADDRSTRLEN);
        data.push_back(addressBuffer);
    }

    return data;
}

int Network::Init() {
    memset(&peerAddr, 0, sizeof(peerAddr));
    peerAddr.sin_family = AF_INET;
    peerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    peerAddr.sin_port = htons(PORT);

    peerSock = socket(AF_INET, SOCK_STREAM, 0);

    if (peerSock < 0)
        return -1;

    peerBind = bind(peerSock, (struct sockaddr*)&peerAddr, sizeof(peerAddr));
    
    if (peerBind < 0)
        return -2;

    return 1;
}

int Network::Listen() {
    if (peerSock < 0 || peerBind < 0)
        return -2;

    isRunning = true;

    return listen(peerSock, 15);
}

void Network::Accept() {
    pollfd fd;
    memset(&fd, 0, sizeof(fd));
    fd.fd = peerSock;
    fd.events = POLLIN;

    while (isRunning) {
        int rc = poll(&fd, 1, 1000); //wait 1 seconds
        
        if (isRunning)
            return;

        if (rc == 0 || fd.revents != POLLIN)
            continue;

        sockaddr_in newSockAddr;
        socklen_t newSockAddrSize = sizeof(newSockAddr);
        int cli = accept(peerSock, (sockaddr*)&newSockAddr, &newSockAddrSize);
    }
}

void Network::AcceptAsync() {
    acceptThread = thread(Accept);
}

void Network::Clean() {
    isRunning = false;
    this_thread::sleep_for(chrono::milliseconds(1000));

    close(peerSock);
    acceptThread.detach();
    acceptThread.~thread();
}