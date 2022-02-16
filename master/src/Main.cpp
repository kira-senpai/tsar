#include "Networking/Master.hpp"
#include "Misc/Debug.hpp"

#define PORT 8080

int main() {
    const char* text="\
    ████████╗███████╗ █████╗ ██████╗ \n\
    ╚══██╔══╝██╔════╝██╔══██╗██╔══██╗ \n\
       ██║   ███████╗███████║██████╔╝ \n\
       ██║   ╚════██║██╔══██║██╔══██╗ \n\
       ██║   ███████║██║  ██║██║  ██║ \n\
       ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ \n";

    printf(text);

    Master t = Master();
    Debug::Log("Initializing Master");
    if (!t.Init(PORT))
        Debug::Error("Failed To Initialize Master");

    t.Listen();
    
    return 0;
}