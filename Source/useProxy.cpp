#include "../Headers/useProxy.h"

int useProxy(std::string url) {

    std::string command = "start msedge --inprivate " + url;
    int returnCode = system(command.c_str());

    if (returnCode != 0) {
        std::cerr << "Failed to execute command. Return code: " << returnCode << std::endl;
    }
    else {
        std::cout << "command executed successfully.\n";
    }

    return 0;
}