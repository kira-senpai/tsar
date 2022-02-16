#include "Master.hpp"
#include "../Misc/Debug.hpp"

#include <iostream>
#include <cstring>

bool Master::Init(int Port) {
    port = port;

    memset((char*)&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    servSocket = socket(servAddr.sin_family, SOCK_STREAM, 0);
    if (servSocket < 0)
        return false;

    if (bind(servSocket, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
        return false;

    return true;
}

void Master::Listen() {
    Debug::Log("Waiting For Clients");
}