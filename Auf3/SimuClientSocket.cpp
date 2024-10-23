#include "SimuClientSocket.h"
#include <iostream>

SimuClientSocket::SimuClientSocket() : socket(io_context) {}

bool SimuClientSocket::Create() { return true; }

bool SimuClientSocket::Connect(std::string address, std::string port) {
  tcp::resolver resolver(this->io_context);
  auto endpoints = resolver.resolve(address, port);
  boost::system::error_code ec;
  boost::asio::connect(this->socket, endpoints,
                       ec); // @suppress("Invalid arguments")
  return (!ec);
}
void SimuClientSocket::Send(std::stringstream &msg) {
#if DEBUG
  std::cout << "Socket DEBUG:: sending Message: " << msg.str() << std::endl;
#endif
  boost::system::error_code ec;
  boost::asio::write(this->socket,
                     boost::asio::buffer(msg.str().c_str(), msg.str().size()),
                     ec);
  if (ec) {
    std::cout << "Error sending message: " << ec.message() << std::endl;
  }
}

void SimuClientSocket::Close() { this->socket.close(); }
