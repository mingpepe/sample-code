#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdint.h>

#define BANK_ADDR 0x7f
#define SLAVE_ADDR 0x40

#define USE_LIB

uint8_t read_reg(int fd, uint8_t address)
{
#ifdef USE_LIB
    return i2c_smbus_read_byte_data(fd, address);
#else
    uint8_t buf = address;
    write(fd, &buf, 1);
    read(fd, &buf, 1);
    return buf;
#endif
}

void write_reg(int fd, uint8_t address, uint8_t value)
{
#ifdef USE_LIB
    i2c_smbus_write_byte_data(fd, address, value);
#else
    char buf[2];
    buf[0] = address;
    buf[1] = value;
    write(fd, buf, 2);
#endif
}

int main(int argc, char **argv)
{
    int adapter_nr = 1;
    char filename[20];

    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    int fd = open(filename, O_RDWR);
    if (!fd)
    {
        printf("Fail to open %s\n", filename);
        exit(1);
    }

    if (ioctl(fd, I2C_SLAVE, SLAVE_ADDR) < 0)
    {
        printf("Fail to set slave id\n");
        exit(1);
    }

    write_reg(fd, BANK_ADDR, 0x00);
    printf("0x%x%x\n", read_reg(fd, 1), read_reg(fd, 0));
    return 0;
}