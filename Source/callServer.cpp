#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <nlohmann/json.hpp>
#include "../Headers/callServer.h"
#include "../Headers/useProxy.h"
#include "../Headers/readConfig.h"
#include "../Headers/getPort.h"

int callServer() {
	std::cout << "Creating web-server...\n";

	SOCKET wsocket;
	SOCKET new_wsocket;
	WSADATA wsaData;
	struct sockaddr_in server;
	int server_len;
	int BUFFER_SIZE = 30720;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Error initializing server...\n";
	}

	wsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (wsocket == INVALID_SOCKET) {
		std::cout << "Error creating socket...\n";
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(getPort());
	server_len = sizeof(server);

	if (bind(wsocket, (SOCKADDR*)&server, server_len) != 0) {
		std::cout << "Could not bind socket...\n";
	}

	if (listen(wsocket, 20) != 0) {
		std::cout << "Could not listen to socket...\n";
	}

	std::cout << "Listening on: 127.0.0.1:" << getPort() << std::endl;

	int bytes = 0;
	while (true) {
		new_wsocket = accept(wsocket, (SOCKADDR*)&server, &server_len);
		if (new_wsocket == INVALID_SOCKET) {
			std::cout << "Could not accept data...\n";
			continue;
		}

		char* buff = new char[BUFFER_SIZE]();
		bytes = recv(new_wsocket, buff, BUFFER_SIZE, 0);
		if (bytes < 0) {
			std::cout << "Could not read client request...\n";
			closesocket(new_wsocket);
			delete[] buff;
			continue;
		}

		std::string request(buff, bytes);
		std::string response;
		std::string serverMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";

		if (request.find("GET /?url=") != std::string::npos) {
			size_t start = request.find("url=") + 4;
			size_t end = request.find(' ', start);
			std::string url = request.substr(start, end - start);
			useProxy(url);
			response = "<html><body><script>window.close();</script></body></html>";

		} else if (request.find("GET /admin/shutdown ") != std::string::npos) {
			response = "<html><body><p>Server is shutting down...</p><script>window.close();</script></body></html>";
			serverMessage.append(std::to_string(response.size()));
			serverMessage.append("\n\n");
			serverMessage.append(response);

			send(new_wsocket, serverMessage.c_str(), serverMessage.size(), 0);

			closesocket(new_wsocket);
			closesocket(wsocket);
			WSACleanup();
			return 0;

		} else if (request.find("GET /admin/?on-start=") != std::string::npos) {
			size_t start = request.find("on-start=") + 9;
			size_t end = request.find(' ', start);
			std::string onstart = request.substr(start, end - start);

			std::ifstream input("C:/ProgramData/Private Proxy/config.json");

			nlohmann::json config = readConfig("C:/ProgramData/Private Proxy/config.json");
			if (onstart == "true") {
				config["on-start"] = true;
				response = "<html><body>On-Start set to true...<script>window.close();</script></body></html>";
			}
			else if (onstart == "false") {
				config["on-start"] = false;
				response = "<html><body>On-Start set to false...<script>window.close();</script></body></html>";
			}
			else {
				response = "Invalid Request: \"on-start\" but be true or false.";
			}
			std::ofstream outfile("C:/ProgramData/Private Proxy/config.json");
			if (outfile.is_open()) {
				outfile << config.dump(4);
				outfile.close();
			}
			else {
				std::cout << "Unable to open config file for writing.\n";
			}

		} else {
			response = "Bad Request: Missing \"url\", or \"on-start\" query parameter.";
		}

		serverMessage.append(std::to_string(response.size()));
		serverMessage.append("\n\n");
		serverMessage.append(response);

		int bytesSent = 0;
		int totalBytesSent = 0;
		while (totalBytesSent < serverMessage.size()) {
			bytesSent = send(new_wsocket, serverMessage.c_str(), serverMessage.size(), 0);
			if (bytesSent < 0) {
				std::cout << "Could not send response...\n";
				break;
			}
			totalBytesSent += bytesSent;
		}
		std::cout << "Sent response to client!\n";

		closesocket(new_wsocket);

		delete[] buff;
	}

	closesocket(wsocket);
	WSACleanup();

	return 0;
}