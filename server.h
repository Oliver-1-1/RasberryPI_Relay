#pragma once
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include "gpio.h"

extern int socket_desc, new_socket;
extern struct sockaddr_in server, client;
void server_setup();
void server_get_new_connection();
