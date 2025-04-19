#include <boost/asio.hpp>
#include <iostream>
#include <string_view>

using namespace boost::asio;

int main()
{
    // Creates the Server's endpoint
    ip::address_v4 ipv4 { boost::asio::ip::make_address_v4("127.0.0.1") };
    ip::port_type portNumber { 8080 };
    ip::tcp::endpoint endpoint { ipv4, portNumber };

    io_context ioContext {};
    
    // This object needs to be created to listen for new connections.
    ip::tcp::acceptor myAcceptor { ioContext, endpoint };
    myAcceptor.set_option(ip::tcp::acceptor::reuse_address(true));
    myAcceptor.listen();

    boost::system::error_code errorCode {};

    // Buffer that will be sent to clients
    std::array<char, 64> message { "HTTP/1.1 200 OK\r\n\r\nHello HTTP World!" };
    mutable_buffer mb { buffer(message) };

    while (true) {
        // This socket represents the next client's connection
        ip::tcp::socket clientSocket { ioContext };

        myAcceptor.accept(clientSocket, errorCode);

        if (errorCode) {
            std::cerr << errorCode.message() << std::endl;
            continue;
        }

        streambuf requestBuffer {};
        
        read_until(clientSocket, requestBuffer, "\r\n\r\n", errorCode);

        if (errorCode) {
            std::cerr << errorCode.message() << std::endl;
            continue;
        }

        // I should parse the HTTP Request
        
        const_buffer bufferData = requestBuffer.data();
        auto bufferSize = requestBuffer.size();

        const char* p1 = static_cast<const char*>(bufferData.data());


        std::string_view sv { p1, bufferSize };

        std::cout << sv << std::endl;

        // size_t s = 0;
        // const_buffers_type bufs = data();
        // const_buffers_type::const_iterator i = bufs.begin();
        // while (i != bufs.end())
        // {
        //   const_buffer buf(*i++);
        //   s += buf.size();
        // }



        
    }
    
    return 0;
}