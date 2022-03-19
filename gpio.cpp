#include "gpio.h"
static volatile unsigned int* peri_address;
static bool is_setup_done = false;

#define GPIO_OFFSET 0x02000000
#define PERI_BASE   0xFE000000
#define BLOCK_SIZE 	(4*1024)

static void map_peripheral(){
    // Open /dev/mem
    int32_t fd;
    assert((fd = open("/dev/gpiomem", O_RDWR | O_SYNC | O_CLOEXEC)) >= 0);

    void* map = mmap(NULL, BLOCK_SIZE,PROT_READ | PROT_WRITE,MAP_SHARED,fd, PERI_BASE + GPIO_OFFSET);
    assert(map != MAP_FAILED);

    peri_address = (volatile unsigned int*)map;
}

namespace GPIO {
    void set_port(uint8_t port, PORT_MODE mode) {

        assert(mode == PORT_INPUT || mode == PORT_OUTPUT);
        assert(port >= 0 && port <= 30); //The need to check if port is >= 0 is probably reduntant since its unsigned
        assert(is_setup_done);
        volatile uint32_t* addr = peri_address + port / 10; // Get address offset. 0-9 = no offset, 10-19 = offset by 1 byte etc
        uint32_t bit_offset = ((uint32_t)port % 10) * 3;
        *addr &= ~(7 << bit_offset); // Restore evert bit to 0;

        if (mode == PORT_OUTPUT) {
            *addr |= 1 << bit_offset;
        }
        if (mode == PORT_INPUT) {
            *addr &= ~(7 << bit_offset);
        }

    }

    void set_bit(uint8_t port) {
        assert(is_setup_done);
        *(peri_address + 0x7) = 1 << port;
    }

    int32_t read_bit(uint8_t port){
        assert(is_setup_done);
        int32_t value = *(peri_address + 0xD) &= (1 << port);
        return value;
    }

    void clear_bit(uint8_t port) {
        assert(is_setup_done);
        *(peri_address + 0xA) = 1 << port;
    }

    void setup() {
        map_peripheral();
        is_setup_done = true;
    }
}