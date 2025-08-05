/*
 * twi0.cpp
 *
 * Created: 05-08-2025
 * Author: Subrata
 *
 * Description:
 * This file provides the implementation of basic I2C communication
 * using TWI0 peripheral on ATmega328PB.
 */

#include "twi0.h"

/* Initialize TWI0 with prescaler and bit rate */
void TWI0_Init(void) {
	TWSR0 = (0<<TWPS1) | (1<<TWPS0);          // Prescaler = 4
	TWBR0 = TWBR_VALUE;                       // Bit rate register value based on F_CPU and F_SCL
	TWCR0 = (1<<TWEN);                        // Enable TWI0
	DDRC &= ~((1<<PINC4) | (1<<PINC5));       // Set PC4 (SDA), PC5 (SCL) as input
	PORTC |= (1<<PINC4) | (1<<PINC5);         // Enable pull-up resistors
}

/* Send START condition */
uint8_t TWI0_Start(void) {
	TWCR0 = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR0 & (1<<TWINT)));
	if ((TWSR0 & 0xF8) != 0x08) return 1;     // START not transmitted
	return 0;
}

/* Send slave address + Read bit */
uint8_t TWI0_Set_Slave_Address(uint8_t slave_address) {
	TWDR0 = (slave_address << 1) | 0x01;
	TWCR0 = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR0 & (1<<TWINT)));
	if ((TWSR0 & 0xF8) != 0x40) return 1;     // SLA+R not acknowledged
	return 0;
}

/* Read data with ACK */
uint8_t TWI0_Read_ACK(uint8_t* data) {
	TWCR0 = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (!(TWCR0 & (1<<TWINT)));
	if ((TWSR0 & 0xF8) != 0x50) return 1;
	*data = TWDR0;
	return 0;
}

/* Read data with NACK */
uint8_t TWI0_Read_NACK(uint8_t* data) {
	TWCR0 = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR0 & (1<<TWINT)));
	if ((TWSR0 & 0xF8) != 0x58) return 1;
	*data = TWDR0;
	return 0;
}

/* Send STOP condition */
void TWI0_Stop(void) {
	TWCR0 = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	while (TWCR0 & (1<<TWSTO));
}

/* Read a block of bytes from slave */
uint8_t TWI0_Read_Bytes(uint8_t slave_address, uint8_t* data, uint8_t length) {
	if (TWI0_Start()) { TWI0_Stop(); return 1; }
	if (TWI0_Set_Slave_Address(slave_address)) { TWI0_Stop(); return 2; }

	for (uint8_t i = 0; i < length - 1; i++) {
		if (TWI0_Read_ACK(&data[i])) { TWI0_Stop(); return 3; }
	}
	if (TWI0_Read_NACK(&data[length - 1])) { TWI0_Stop(); return 4; }

	TWI0_Stop();
	return 0;
}
