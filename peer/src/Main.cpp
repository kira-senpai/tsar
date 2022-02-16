#include "Misc/Debug.hpp"
#include "Networking/Peer.hpp"
#include "Networking/Network.hpp"

int main() {
    Peer peer = Peer();
  
    if (!peer.Init())
        Debug::Error("Failed To Initialize Tzar");

    Debug::Log("Tzar Initialized");

    peer.SearchLocal();

    Network::Clean();
    return 0;
}