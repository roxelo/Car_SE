//#include <EEPROM.h>
#include <hw_eeprom.h>
#include <eeprom.h>

uint32_t address = 4;
uint32_t size_data = 4;
uint32_t *store;
uint32_t val = 2;
uint32_t read_val;

int i = 0;


void setup() {
    EEPROMInit();
    Serial.begin(9600);

}

void loop() {
  i++;
  if (i == 10) {
    EEPROMRead(&read_val, address, size_data);
    Serial.print("Val: "); Serial.println(read_val);
    
    store = &val;
    size_data = sizeof(val);
  
    //EEPROMProgram(store,address,size_data);

    EEPROMRead(&read_val, address, size_data);
    Serial.print("Val2: "); Serial.println(read_val);
  
    delay(1000);
  }
}
