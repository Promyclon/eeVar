#ifndef _E2PROMVARS_
#define _E2PROMVARS_

#include <avr/eeprom.h>

#define EEPROM_NAME(x)       eeprom_ ## x
#define EEPROM_ADDRESS(x)    ((&EEPROM_NAME(x)))
#define EEPROM_READ(x)       eeprom_read_block(&x, EEPROM_ADDRESS(x), sizeof(x))
#define EEPROM_WRITE(x)      eeprom_write_block(&x, EEPROM_ADDRESS(x), sizeof(x))

// can define var/eeprom var pair, defining an initial value: EEPROM_VAR (int a) = 0;
#define EEPROM_VAR(var_type, var_name)       \
	var_type var_name;                   \
	var_type EEPROM_NAME(var_name) EEMEM 

#define VAR_FN(var_name) var_name ## Init

// defines SRAM/EEPROM var pair with loading EEPROM into SRAM code just before main() call
#define EEPROM_AUTO_VAR(var_type, var_name, var_value)       \
	EEPROM_VAR(var_type, var_name) = var_value;          \
	void VAR_FN(var_name) (void) __attribute__ ((naked)) \
    __attribute__ ((section (".init8")));                    \
	void VAR_FN(var_name) (void){EEPROM_READ(var_name);} \

#define EEPROM_SETUP(a,b) {addr:(uint8_t*)&(a), value:(b)}

typedef struct { 
		uint8_t	*addr;   
		uint8_t	value;   
} _setup_rec;

typedef char* _pointer;

// define device configuration: EEPROM_CONFIG(name)={EEPROM_SETUP(port, value), ...};
#define EEPROM_CONFIG(name) _setup_rec name[] EEMEM

#define EEPROM_CONFIG_ADR(name) &name[0]

#define EEPROM_CONFIG_END(name) (EEPROM_CONFIG_ADR(name) + sizeof(name))

#define EEPROM_CONFIGURE(name) eeprom_setup(&name[0], sizeof(name))

void eeprom_setup(const _setup_rec * data, uint16_t size);

#endif
