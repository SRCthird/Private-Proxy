﻿#define _CRT_SECURE_NO_WARNINGS
#include "Headers/Private-Proxy.h"
#include "Headers/callServer.h"
#include "Headers/checkStatus.h"
#include "Headers/getPort.h"
#include "Headers/stopApp.h"
#include "Headers/readConfig.h"
#include "Headers/createDefault.h"

void displayHelp() {
    std::cout << ""
        << "Usage: Private-Proxy [options]\n\n"
        << "Author: Stephen Chryn\n"
        << "Version: 1.0.0 \n\n"
        << "Options:\n"
        << "Program name  command     alias   description\n"
        << "Private-Proxy --start     (-s)    Start the program\n"
        << "Private-Proxy --stop      (-x)    Stop the program\n"
        << "Private-Proxy --on-start          Execute task in startup-mode\n"
        << "Private-Proxy --version   (-v)    Show the current version\n"
        << "Private-Proxy --help      (-h)    Show help menu\n";
}

int startServer(int port) {
    if (checkStatus("127.0.0.1", port) == 1) {
        std::cout << "Appication is already running on 127.0.0.1:" << port << std::endl;
        return 0;
    }
    else {
        std::cout << "Appication is not running on 127.0.0.1:" << port << std::endl;
        std::cout << "Attemplting to start server...\n";
        callServer();
        std::cout << "Appication has successfully shut down!\n";
    }
}

void AttachToConsole() {
    if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
        AllocConsole();
    }

    FILE* stream;
    freopen_s(&stream, "CONOUT$", "w", stdout);
    freopen_s(&stream, "CONOUT$", "w", stderr);
    std::cout << "Attached to console\n";
}

void DetachFromConsole() {
    FreeConsole();
}

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
) {

    int port = getPort();

    for (int i = 0; i < __argc; i++) {
        if (port == -1) {
            std::cout << "Failed to get port number from config file...\n";
            if (createDefault() == 1) {
                return 0;
            }
            std::cout << "Default config's created.\n";
        }

        std::vector<std::string> args(__argv, __argv + __argc);

        if (std::find(args.begin(), args.end(), "--start") != args.end()) {
            std::cout << "Attempting to start application...\n";
            startServer(port);
            return 0;
        }
        if (std::find(args.begin(), args.end(), "-s") != args.end()) {
            std::cout << "Attempting to start application...\n";
            startServer(port);
            return 0;
        }
        if (std::find(args.begin(), args.end(), "--stop") != args.end()) {
            std::cout << "Attemplting to stop appication...\n";
            if (stopApp() == 0) {
                std::cout << "Application has successfully shut down!\n";
            }
            return 0;
        }
        if (std::find(args.begin(), args.end(), "-x") != args.end()) {
            std::cout << "Attemplting to stop appication...\n";
            if (stopApp() == 0) {
                std::cout << "Application has successfully shut down!\n";
            }
            return 0;
        }
        if (std::find(args.begin(), args.end(), "--on-start") != args.end()) {

            std::ifstream input("C:/ProgramData/Private Proxy/config.json");

            nlohmann::json config = readConfig("C:/ProgramData/Private Proxy/config.json");
            if (config["on-start"] == true) {
            }
            else if (config["on-start"] == false) {
                std::cout << "On-Start in Config.json is set to false...\n";
                std::cout << "Applicagtion not starting.\n";
                return 0;
            }
            else {
                std::cout << "Error in: On-Start config. On-Start must be true or false.\n";
                std::cout << "Assuming On-Start to true...\n";
            }
            if (checkStatus("127.0.0.1", port) == 1) {
                std::cout << "Appication is already running on 127.0.0.1:" << port << std::endl;
            }
            else {
                std::cout << "Appication is not running on 127.0.0.1:" << port << std::endl;
                std::cout << "Attemplting to start server...\n";
                callServer();
                std::cout << "Appication has successfully shut down!\n";
            }
            std::ofstream outfile("config.json");
            if (outfile.is_open()) {
                outfile << config.dump(4);
                outfile.close();
            }
            return 0;
        }

        AttachToConsole();

        if (std::find(args.begin(), args.end(), "--help") != args.end()) {
            displayHelp();
            return 0;
        }
        if (std::find(args.begin(), args.end(), "-h") != args.end()) {
            displayHelp();
            return 0;
        }
        if (std::find(args.begin(), args.end(), "--version") != args.end()) {
            std::cout << "Version 1.0.0";
            return 0;
        }
        if (std::find(args.begin(), args.end(), "-v") != args.end()) {
            std::cout << "Version 1.0.0";
            return 0;
        }
    }

    std::cout << "No argument selected...\n\n";
    displayHelp();
	return 0;
}
