#pragma once
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

nlohmann::json readConfig(const std::string& filename);