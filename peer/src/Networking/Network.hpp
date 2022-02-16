#ifndef _NETWORK_
#define _NETWORK_

#define PORT 6969

#include <netinet/in.h>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

using namespace std;

class Network {
private:
    static sockaddr_in peerAddr;
    static int peerSock;
    static int peerBind;
    static bool isRunning;
    static thread acceptThread;
public:

    static vector<string> GetIP4();

    /**
     * Initialize Network
     * @return 1 if successfull, -1 if failed to create socket or -2 if failed to bind socket
     */
    static int Init();

    /**
     * Starts listening to other peers
     * @return 0 if successfull, -2 if Init failed or hasn't been executed -1 if failed to listen
     */
    static int Listen();

    /**
     * @brief Start Accepting Requests
     */
    static void Accept();

    /**
     * @brief Create a thread where it will start accepting connection requests
     */
    static void AcceptAsync();

    /**
     * @brief Clean everything
     */
    static void Clean();
};

#endif