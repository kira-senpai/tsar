#include "Peer.hpp"
#include "Network.hpp"
#include "../Misc/Debug.hpp"

#include <chrono>
#include <algorithm>

using namespace std::chrono;

//Probably Secure Enough
void Peer::GenPrivateKey() {
    auto now = system_clock::now();
    auto time = duration_cast<nanoseconds>(now.time_since_epoch()) % 1000;

    string num = "";
    for (int i = 0; i < 64; i ++)
        num += to_string(rand() % 10000);

    privateKeyHex = SHA256().ToSha256(to_string(time.count()) + num);
}

bool Peer::Init() {

    bool isPrivValid = false;

    for (int i = 0; i < 10; i++) {
        GenPrivateKey();
        if (secp256k1_ec_seckey_verify(secp256k1Context, privateKeyHex))
            isPrivValid = true;

        if (isPrivValid)
            break;
    }

    if (!isPrivValid)
        return false;
        
    secp256k1Context = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);

    if (!secp256k1_ec_pubkey_create(secp256k1Context, &pubKey, privateKeyHex) == 1)
        return false;

    switch (Network::Init()) {
        case -1:
            Debug::Alert("Failed To Create Socket");
            return false;
        case -2:
            Debug::Alert("Failed To Bind Socket");
            return false;
    }

    switch (Network::Listen()) {
        case -1:
            Debug::Alert("Failed To Listen");
            return false;
        case -2:
            Debug::Alert("Network hasn't been Initialized or failed");
            return false;
    }

    Network::AcceptAsync();

    return true;
}

void Peer::SearchLocal() {
    for (auto ip : Network::GetIP4()) {
        if (find(blacklist.begin(), blacklist.end(), ip) != blacklist.end())
            continue;
        
        blacklist.push_back(ip);
        
        string newip  = ip.substr(0, ip.find_last_of('.')) + ".";

        //for (auto i = 0; i < 255; i++)
            
    }
}