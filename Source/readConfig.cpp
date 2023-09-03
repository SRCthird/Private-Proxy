#include "../Headers/readConfig.h"

nlohmann::json readConfig(const std::string& filename) {
    std::ifstream infile(filename);
    nlohmann::json j;
    if (infile.is_open()) {
        try {
            infile >> j;
        }
        catch (const std::exception& e) {
            std::cerr << "Error reading config: " << e.what() << std::endl;
        }
        infile.close();
    }
    else {
        std::cerr << "Unable to open config file: " << filename << std::endl;
    }
    return j;
}