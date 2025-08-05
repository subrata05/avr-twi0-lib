/*
 * twi0.h
 *
 * Created: 05-08-2025 10:48:48
 *  Author: Subrata
 */ 


#ifndef TWI0_H_
#define TWI0_H_

#define F_SCL 100000UL
#define F_CPU 8000000UL
#define TWBR_VALUE (((F_CPU / F_SCL) - 8) / (2 * 4))

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void TWI0_Init(void);
uint8_t TWI0_Start(void);
uint8_t TWI0_Set_Slave_Address(uint8_t slave_address);
uint8_t TWI0_Read_ACK(uint8_t* data);
uint8_t TWI0_Read_NACK(uint8_t* data);
void TWI0_Stop(void);
uint8_t TWI0_Read_Bytes(uint8_t slave_address, uint8_t* data, uint8_t length);
double getForce(uint8_t i2c_slave_addr);

#endif /* TWI0_H_ */
