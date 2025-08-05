# avr-twi0-lib
A lightweight I2C library built on the TWI0 peripheral of the **ATmega328PB**. The library is written in C++ and tailored for bare-metal AVR applications. It can be adapted for other AVR microcontrollers with minimal changes.

---

## Features

- I2C Master communication
- START/STOP condition handling
- Read ACK/NACK support
- Multi-byte read capability
- Calibrated sensor data retrieval example
- Lightweight and register-level (no dependency on Arduino framework)

---

## Files

- `twi0.h` - Header file with declarations and configuration macros
- `twi0.cpp` - Implementation file with documented logic
- `examples/read_force_sensor/main.cpp` - Example application for reading sensor data
- `debugSerial/` - Custom serial debugging print functions

---

## Configuration

### Default Settings

```c
#define F_CPU 8000000UL
#define F_SCL 100000UL
#define TWBR_VALUE (((F_CPU / F_SCL) - 8) / (2 * 4))  // for 8MHz clock
```

###  For 16MHz Clock

```c
#define F_CPU 16000000UL
#define TWBR_VALUE (((F_CPU / F_SCL) - 16) / (2 * 4))
```

---

## Porting to Other AVRs

The library uses `TWCR0`, `TWDR0`, `TWBR0`, and `TWSR0` specific to **ATmega328PB**. To use it with other AVRs (like ATmega328P):

Replace register names (`TWCR0` → `TWCR`, `TWDR0` → `TWDR`, etc.)

Example for ATmega328P:

```c
#define TWBR_VALUE (((F_CPU / F_SCL) - 16) / (2 * 4))  // Use this for 16MHz
// Replace all TWI0 register names with standard TWI ones
```

