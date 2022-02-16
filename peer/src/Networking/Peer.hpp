#ifndef _PEER_
#define _PEER_

#include "../Crypto/Crypto.hpp"
#include <vector>

class Peer {
private:
    vector<string> blacklist = vector<string>({"::1", "127.0.0.1", "127.0.1.1"});
    secp256k1_context* secp256k1Context;
    uint8_t* privateKeyHex;
    secp256k1_pubkey pubKey;
public:

    //Initialization Stuff
    void GenPrivateKey();
    bool Init();

    //Group Stuff
    void SearchLocal();
};

#endif