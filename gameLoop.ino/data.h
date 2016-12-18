#ifndef DATA_H
#define DATA_H

uint32_t address = 4; //storing address has to be a multiple of 4
uint32_t size_data = 4; //Right now using int so 4
uint32_t *store;
uint32_t val = 2; //To store data, it needs to be a uint32_t
uint32_t read_val; 


int highscore;

/*-----------Read EEPROM---------//

EEPROMRead(&read_val, address, size_data);

//------------------------------*/

/*-----------Write EEPROM---------//

EEPROMProgram(store,address,size_data); 

//------------------------------*/

#endif
