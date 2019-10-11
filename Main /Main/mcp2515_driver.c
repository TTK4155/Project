
#include <avr/io.h>
#include "spi_driver.h"
#include "mcp2515_driver.h"




uint8_t MCP2515_init() {
  
  SPI_Init(); // Initialize SPI
  MCP2515_reset(); // Send reset-command
 // MCP2515_write (MCP_CANCTRL, MODE_CONFIG);


  // Self-test
  uint8_t value = MCP2515_read(MCP_CANSTAT);
  //printf ( "value is: %d \n", value);
  if ((value & MODE_MASK) != MODE_CONFIG) {
    printf("MCP2515 is NOT in configuration mode after reset!\n");
    return 1;
  }
  // More initialization
  return 0;
}

uint8_t MCP2515_read(uint8_t address) {

	//printf("function: MCP2515_READ \n");
  uint8_t result;
  //PORTB &= ~(1 << CAN_CS); // Select CAN-controller

  PORTB &= ~(1 << SPI_SS); // Select CAN-controller

  SPI_send(MCP_READ); // Send read instruction
  SPI_send(address); // Send address
  result = SPI_read(); // Read result

  //PORTB |= (1 << CAN_CS); // Deselect CAN-controller return result;

  PORTB |= (1 << SPI_SS); // Deselect CAN-controller return result;

	//printf("MCP2515_READ result: %d \n", result);
  return result;
}

void MCP2515_reset(){
	//printf("function: RESET \n");
  PORTB &= ~(1 << SPI_SS); // Select CAN-controller
  SPI_send(MCP_RESET);  //send reset command
  PORTB |= (1 << SPI_SS); // Deselect CAN-controller return result;
  //printf("function: END RESET \n");
  
}

void MCP2515_write(uint8_t address, uint8_t value){
  PORTB &= ~(1 << SPI_SS); // Select CAN-controller

  SPI_send(MCP_WRITE);  //Send write command
  SPI_send(address);    //Send the address
  SPI_send(value);      //Send the value

  PORTB |= (1 << SPI_SS); // Deselect CAN-controller return result;
}


void MCP2515_RTS (int cmnd){


	PORTB &= ~(1 << SPI_SS); // Select CAN-controller

	//Checking if the last bits equal 1, 2 or 4
	if(cmnd == 0){
		SPI_send(MCP_RTS_TX0);
		}else if(cmnd == 1){
		SPI_send(MCP_RTS_TX1);
		}else if(cmnd == 2){
		SPI_send(MCP_RTS_TX2);
	}

	//something is missing here...?
	// If the lowbit is 0x00 then the command should be ignored,
	//but what if the command is not 0x01, 0x02, 0x04 or 0x00, should something else happen then?

	PORTB |= (1 << SPI_SS); // Deselect CAN-controller return result;
} 

uint8_t MCP2515_read_status(){
  uint8_t result;

  PORTB &= ~(1 << SPI_SS); // Select CAN-controller

  SPI_send(MCP_READ_STATUS);  //Send the command to read the status
  result = SPI_read();         //reading the status

  PORTB |= (1 << SPI_SS
  ); // Deselect CAN-controller return result;

  return result;

}

/*
The mask byte determines which bits in the register will be allowed to change.
if mask = 1 --> allow change, mask = 0 -> no change
*/
void MCP2515_Bit_Modify(uint8_t address, uint8_t mask, uint8_t data){

  PORTB &= ~(1 << SPI_SS); // Select CAN-controller

  SPI_send(MCP_BITMOD);  //Send the command to modify bit
  SPI_send(address);     //Send the address
  SPI_send(mask);        //Send the mask
  SPI_send(data);        //Send the data

  PORTB |= (1 << SPI_SS); // Deselect CAN-controller return result;

}
