#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include "gpio.h"
#include "server.h"
int main()
{
    
    server_setup();

    while (true) {
        server_get_new_connection();

    }
    return 0;
}