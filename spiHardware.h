#ifndef SPIHARDWARE_H
#define SPIHARDWARE_H

#include <avr/io.h>

#define SPI_PORT     (PORTC)
#define SPI_CS_PORT  (PORTC)
#define SPI_DEV      (SPIC)
#define SPI_MISO     PIN6_bm
#define SPI_MOSI     PIN5_bm
#define SPI_SCK      PIN7_bm

#define SPI_CS       PIN4_bm



#endif // SPIHARDWARE_H
