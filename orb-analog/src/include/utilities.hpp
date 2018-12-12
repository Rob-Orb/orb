#ifndef UTILITIES_HPP
#define UTILITIES_HPP

uint8_t getPin(uint8_t pin){
	uint8_t byte = 0xB0;
	byte |= pin >> 1;
	byte |= (pin%2) << 3;
	return byte;
}

#endif
