#include "e2promvars.h"

void eeprom_setup(const _setup_rec * data, uint16_t size)
{
	_setup_rec rec;
	for (_pointer ptr = (_pointer)data; ptr < ((_pointer)data) + size; ptr += sizeof(_setup_rec))
	{
		eeprom_read_block((_pointer)&rec, ptr, sizeof(rec));
		*(rec.addr) = rec.value;
	};
}
