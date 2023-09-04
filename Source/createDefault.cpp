#include "../Headers/createDefault.h"

namespace fs = std::filesystem;

int createDefault() {
    std::cout << "Creating default configuration file...\n";

    fs::create_directories("./Resources");

    std::string filePath = "Resources/config.json";

    std::ofstream configFile(filePath);
    
    if (configFile.is_open()) {
        configFile << "{\n";
        configFile << "    \"port\": 42310,\n";
        configFile << "    \"on-start\": true\n";
        configFile << "}\n";
        
        configFile.close();
        std::cout << "Default config file created at " << filePath << std::endl;
    } else {
        std::cerr << "Error: Could not create the default config file...";
        return 1;
    }
    return 0;
}