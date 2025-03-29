#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <nlohmann/json.hpp>  // JSON library (install with `sudo apt install nlohmann-json3-dev`)

using namespace boost::asio;
using namespace boost::beast;
using namespace boost::beast::websocket;
using tcp = ip::tcp;
using json = nlohmann::json;

void handle_client(tcp::socket socket) {
    try {
        websocket::stream<tcp::socket> ws(std::move(socket));
        ws.accept();

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate real-time updates

            // Simulated path (could come from an algorithm)
            json path_data = {{"path", {{50, 50}, {200, 100}, {350, 200}, {500, 350}}}};

            // Send JSON data to the WebSocket client
            ws.write(net::buffer(path_data.dump()));
        }
    } catch (const std::exception &e) {
        std::cerr << "Client error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        net::io_context ioc;
        tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));

        std::cout << "WebSocket server running on ws://localhost:8080" << std::endl;

        while (true) {
            tcp::socket socket(ioc);
            acceptor.accept(socket);
            std::thread(handle_client, std::move(socket)).detach();  // Handle each client in a new thread
        }
    } catch (const std::exception &e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }

    return 0;
}
