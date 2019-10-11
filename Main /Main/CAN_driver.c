/* This is the CAN-controller */

#include "mcp2515_driver.h"
#include "CAN_driver.h"
#include <stdio.h>
#include <avr/delay.h>

void CAN_init(){

  MCP2515_init();

  //Enable LOOPBACK mode
	MCP2515_Bit_Modify(MCP_CANCTRL, 0b11100000, MODE_LOOPBACK);
	//MCP2515_write(MCP_CANCTRL, MODE_LOOPBACK);
	MCP2515_Bit_Modify(MCP_RXB0CTRL, 0b01100000, 0b01100000);
	
	//printf("MCP_CANCTRL %x", MCP2515_read(MCP_CANCTRL) & 0b11100000);

  uint8_t status = MCP2515_read(MCP_CANSTAT);
  printf("STATUS %d \n", status);
  
  
  MCP2515_Bit_Modify(MCP_CANINTE, 0b01, 0b01);
  //MCP2515_write(MCP_CANINTF, 0);
  //MCP2515_Bit_Modify(MCP_CANINTF, 0x01, 0);

}


void CAN_message_send(CAN_message* message){

  //Set the message id
  MCP2515_write(MCP_TXB0SIDH, (message->id >> 3));
  MCP2515_write(MCP_TXB0SIDL, (message->id << 5));

  //Set data length and use data frame (RTR = 0)
	MCP2515_write(MCP_TXB0DLC, (0x0F) & (message->length));

  //Set data bytes (max. 8 bytes)
	for (int i = 0; i < message->length; i++) {
			MCP2515_write(MCP_TXB0D0 + i, message->data[i]);
	}
	
	/*printf("Sending ID low %x \n\r", MCP2515_read(MCP_TXB0SIDL));
	printf("Sending ID high %x \n\r", MCP2515_read(MCP_TXB0SIDH));
	printf("Sending data length %x \n\r", MCP2515_read(MCP_TXB0DLC));
	printf("Sending first data %x \n\r", MCP2515_read(MCP_TXB0D0));*/


	//Request to send via TX0
	MCP2515_RTS(0);
}


CAN_message CAN_data_receive(){
 // printf("CANINTF: %d\n\r", MCP2515_read(MCP_CANINTF) & 0b1);
	
	if ((MCP2515_read(MCP_CANINTF) & 0b01) == 1){
	
	  CAN_message message;
	  //Get message id
	  message.id  = (MCP2515_read(MCP_RXB0SIDH) << 3) | (MCP2515_read(MCP_RXB0SIDL) >> 5);

	  //Get message length
	  message.length = (0x0F) & (MCP2515_read(MCP_RXB0DLC));

	  //Get message data
	  for(int i = 0; i < message.length; i++) {
  		message.data[i] = MCP2515_read(MCP_RXB0D0 + i);
		 //printf("message sended %d", message.data[i] );
	  }
	  printf("message received: %d\n\r", message.data[0] );
	  printf("data length received: %d\n\r", MCP2515_read(MCP_RXB0DLC) );
		
	  MCP2515_Bit_Modify(MCP_CANINTF, 0x01, 0x00);
	  return message;
	}
	else
		printf ("No valid message. CANINTF flag low! \n\r");
}







/*
int CAN_transmit_complete(){
  //Check if TX buffer is not pending transmission (TXREQ = 0)
  if ((MCP_TXB0CTRL & (1 << 3)){
    return 0;
  }else{
    return 1;
  }
}*/
