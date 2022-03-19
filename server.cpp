#include "server.h"
int socket_desc, new_socket, c;
struct sockaddr_in server, client;

void server_setup(){

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    assert(socket_desc != -1);

    //Prepare
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    //Bind port
    assert(bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) >= 0);
    std::cout << "Server started\n" << std::flush;

    GPIO::setup();
}

void server_get_new_connection(){
    //Listen
    listen(socket_desc, 3);

    //Accept
    std::cout << "Waiting for a user to connect...\n" << std::flush;
    size_t c = sizeof(struct sockaddr_in);
    new_socket = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c);
    assert(new_socket >= 0);

    std::cout << "Connection accepted! IP: " << inet_ntoa(client.sin_addr) << std::endl;
    if (strcmp(inet_ntoa(client.sin_addr), "192.168.1.215") == 0) {

        GPIO::set_port(21, GPIO::PORT_INPUT);
        if (GPIO::read_bit(21)) {
            GPIO::clear_bit(21);
        }
        else {
            GPIO::set_port(21, GPIO::PORT_OUTPUT);
            GPIO::set_bit(21);
        }

    }
}
