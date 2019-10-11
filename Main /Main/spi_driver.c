#include <avr/io.h>
#include "spi_driver.h"

//#define SPI_SS PB4
// #define SPI_MOSI PB5
// #define SPI_MISO PB6
// #define SPI_SCK PB7

#define SPI_INT PD2

/*THIS IS FROM THE DATASHEET P160 */

void SPI_Init(){
  //Set SPI_SS, SPI_MOSI, and SPI_SCK as outputs
  DDRB |= (1 << SPI_SS) | (1 << SPI_MOSI) | (1 << SPI_SCK);
  DDRB &= ~(1 << SPI_MISO);
  //PORTB |= (1 << SPI_INT);

  // Enabling SPI in master mode and set clock rate fosc/16
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);

  //Set SPI_SS high ??
  //PORTB |= (1 << SPI_SS);
 
}


void SPI_send(char data){
	//PORTB &= ~(1 << SPI_SS);

  /* Start transmission */
  SPDR = data;

  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)));

	//PORTB |= (1 << SPI_SS);
}


char SPI_read (){
  //send a dummy bite
	SPI_send(0);
  /* Wait for reception complete */
  while(!(SPSR & (1<<SPIF)));
  /* Return data register */
  return SPDR;
}
