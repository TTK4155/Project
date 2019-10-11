/*
 * spi_driver.h
 *
 * Created: 03/10/2019 14:52:50
 *  Author: tedes
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#define SPI_SS PB4
#define SPI_MOSI PB5
#define SPI_MISO PB6
#define SPI_SCK PB7


void SPI_Init();
void SPI_send(char data);
char SPI_read ();



#endif /* SPI_DRIVER_H_ */