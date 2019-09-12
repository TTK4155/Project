/*
 * IncFile1.h
 *
 * Created: 05/09/2019 14:07:38
 *  Author: tedes
 */ 


#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

// defining the function
void My_serial_Init( unsigned int);

int My_serial_Transmit( unsigned char);

int My_serial_Receive( void );




#endif /* COMMUNICATION_H_ */