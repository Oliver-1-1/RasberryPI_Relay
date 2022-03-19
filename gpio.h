#pragma once
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <assert.h>
#include <unistd.h>

namespace GPIO {
    typedef enum {
        PORT_INPUT,
        PORT_OUTPUT
    } PORT_MODE;

    void   setup();
    void   set_port(uint8_t port, PORT_MODE mode);
    void   clear_bit(uint8_t port);
    void   set_bit(uint8_t port);
    int32_t read_bit(uint8_t port);
}