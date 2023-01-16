#include <stdint.h>
#include "spi.h"

#define SPI_DEVICE "/dev/spidev0.1"

void write_reg(spi_t *spi, uint8_t address, uint8_t data)
{
  char tx_buf[2];
  char rx_buf[2];
  tx_buf[0] = address;
  tx_buf[1] = data;
  spi_exchange(spi, rx_buf, tx_buf, 2);
}

uint8_t read_reg(spi_t *spi, uint8_t address)
{
  char tx_buf[2];
  char rx_buf[2];
  tx_buf[0] = address | 0x80;
  spi_exchange(spi, rx_buf, tx_buf, 2);
  return rx_buf[1];
}

int main()
{
  spi_t spi;
  spi_init(&spi, SPI_DEVICE, SPI_MODE_3, 0, 1000000);
  write_reg(&spi, 0x7f, 0x01);
  printf("0x%x%x\n", read_reg(&spi, 0x01), read_reg(&spi, 0x00));
  return 0;
}
