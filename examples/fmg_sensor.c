#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "twi0.h"

uint8_t slave_address = 0x28;

double getForce(uint8_t i2c_slave_addr);

int main(void) {
    TWI0_Init();       
    while (1) {
        double force = getForce(slave_address);
        // process the force data accordingly
        _delay_ms(100);
    }
}

double getForce(uint8_t i2c_slave_addr) {
	const double slope = 0.0028597;
	const double intercept = -9.5477024;
	uint8_t byteArr[4] = {0};
	uint16_t adcValue = 0;
	double force = 0.0;
	
	uint8_t status = TWI0_Read_Bytes(i2c_slave_addr, byteArr, 4);
	if (status != 0) {
		return 0.0;
	}
	
	adcValue = ((uint16_t)(byteArr[0] & 0x3F) << 8) | (byteArr[1] & 0xFF);
	force = (double)adcValue * slope + intercept;
	
	return force;
}
