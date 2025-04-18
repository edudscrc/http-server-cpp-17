#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

int main()
{
    /*
        1)

        - Create socket
        - Bind socket to a network address (127.0.0.1) and a port number (8080)
        - Put the socket into listening mode, making it ready to accept incoming connection requests from clients.
    */

    io_context ioExecutor {};
    
    // Creates a TCP socket
    ip::tcp::socket tcpSocket { ioExecutor };

    // Creates the Server's endpoint
    ip::address_v4 ipv4 { boost::asio::ip::make_address_v4("127.0.0.1") };
    ip::port_type portNumber { 8080 };
    ip::tcp::endpoint endpoint { ipv4, portNumber };


    char str[] { "Hello HTTP World!" };
    char* ptr1 = str;
    mutable_buffer mb { ptr1, std::strlen(str) + 1 };
    
    ip::tcp::acceptor myAcceptor { ioExecutor, endpoint };

    std::cout << "Listening...\n";
    myAcceptor.listen();
    
    std::cout << "Accepting...\n";
    myAcceptor.accept(tcpSocket);

    std::cout << "Sending...\n";
    tcpSocket.send(mb);

    std::cout << "Closing...\n";
    tcpSocket.close();

    // tcpSocket.receive(mb);

    // tcpSocket.send()
    // tcpSocket.receive()
    // tcpSocket.read_some()
    

    // tcpSocket.connect()


    
    return 0;
}