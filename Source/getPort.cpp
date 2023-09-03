#include "../Headers/getPort.h"

int getPort() {
    std::ifstream configFile("Resources/config.json");
    if (!configFile.is_open()) {
        std::cerr << "Failed to open config.json" << std::endl;
        return -1;
    }

    nlohmann::json config;
    try {
        configFile >> config;
    }
    catch (nlohmann::json::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return -1;
    }

    if (config.contains("port") && config["port"].is_number()) {
        return config["port"].get<int>();
    }
    else {
        std::cerr << "Port not found or is not a number in config.json" << std::endl;
        return -1;
    }
}