#include "../Headers/stopApp.h"

int stopApp() {
    int port = getPort();

    std::string addr = "http://127.0.0.1:" + std::to_string(port);
    httplib::Client client(addr);

    auto res = client.Get("/admin/shutdown");
    if (res && res->status == 200) {
        std::cout << res->body << std::endl;
    }
    else {
        std::cerr << "Failed to fetch the URL." << std::endl;
    }

    return 0;
}