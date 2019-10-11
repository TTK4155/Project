/*CAN controller header*/

#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H


typedef struct{
  unsigned int id;
  int8_t length;
  uint8_t data[8];
} CAN_message;


//This may change ....
void CAN_init(void);
void CAN_message_send(CAN_message*);
//void CAN_error();
//int CAN_transmit_complete();
CAN_message CAN_data_receive();
//void CAN_init_vect();


#endif
