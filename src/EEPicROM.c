#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

// #define EEPICROM_LOGGING

const uint8_t ROM[0x8000] = {
#include "ROM.txt"
};


const uint DATA[8]     = { 0, 1, 2, 3, 4, 5, 6, 7 };
const uint ADDRESS[15] = { 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 };
const uint LED_BUILTIN = 25;
const uint TXS_OE      = 26;
const uint CE          = 27;
const uint OE          = 28;

//                                 2222222221111111111
//                                 87654321098765432109876543210
const uint32_t MASK_DATA       = 0b00000000000000000000011111111;
const uint32_t MASK_ADDRESS    = 0b00000011111111111111100000000;
const uint32_t MASK_ENABLE_OUT = 0b00110000000000000000000000000; // note: this includes the on-board LED so it can show the enable status of the EEPicROM
const uint32_t MASK_ENABLE_IN  = 0b11000000000000000000000000000;
//                                  0110000000000000000000000000
const uint32_t MASK_OUTPUTS   = MASK_DATA | MASK_ENABLE_OUT;


void binary_declarations();
void initialise_gpio();


int main() {
   binary_declarations();
	stdio_init_all();
   initialise_gpio();

	// allocate memory to the heap and initialise with values from flash
	uint8_t* memory = (uint8_t*) malloc(0x8000);
	for (int i = 0; i < 0x8000; i++)
		memory[i] = ROM[i];

   uint32_t gpio;
   uint16_t address;
   uint8_t  data;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
	while (true) {
#ifdef EEPICROM_LOGGING
      time_t start = time_us_64();
#endif
      gpio = gpio_get_all();
      address = (gpio & MASK_ADDRESS) >> 8;

      // disable the level shifters if either Output Enable or Chip Enable goes high
      if (gpio & MASK_ENABLE_IN) {
         gpio = 0;
      }
      else {
         gpio = MASK_ENABLE_OUT | memory[address];
      }

      gpio_put_masked(MASK_OUTPUTS, gpio);
#ifdef EEPICROM_LOGGING
      time_t end = time_us_64();
      time_t duration = end - start;
      printf("GPIO raw: %08lx\taddress: %04x\tdata: %02x\t\tTime taken: %lld us\n",
             gpio,
             address,
             gpio & MASK_DATA,
             duration);
#endif
   }
#pragma clang diagnostic pop

	free(memory);
}


void initialise_gpio() {
   gpio_init(LED_BUILTIN);
   gpio_set_dir(LED_BUILTIN, GPIO_OUT);
   gpio_init(OE);
   gpio_set_dir(OE, GPIO_IN);
   gpio_init(CE);
   gpio_set_dir(CE, GPIO_IN);
   for (int i = 0; i < 15; i++) {
      gpio_init(ADDRESS[i]);
      gpio_set_dir(ADDRESS[i], GPIO_IN);
   }
   for (int i = 0; i < 8; i++) {
      gpio_init(DATA[i]);
      gpio_set_dir(DATA[i], GPIO_OUT);
   }
   gpio_init(TXS_OE);
   gpio_set_dir(TXS_OE, GPIO_OUT);
}

void binary_declarations() {
// Declarations for the binary
#ifdef EEPICROM_LOGGING
	bi_decl(bi_program_description("EEPicROM v1.0 (logging enabled)"));
#else
   bi_decl(bi_program_description("EEPicROM v1.0 (logging disabled)"));
#endif
   bi_decl(bi_1pin_with_name(ADDRESS[0], "a0"));
	bi_decl(bi_1pin_with_name(ADDRESS[1], "a1"));
	bi_decl(bi_1pin_with_name(ADDRESS[2], "a2"));
	bi_decl(bi_1pin_with_name(ADDRESS[3], "a3"));
	bi_decl(bi_1pin_with_name(ADDRESS[4], "a4"));
	bi_decl(bi_1pin_with_name(ADDRESS[5], "a5"));
	bi_decl(bi_1pin_with_name(ADDRESS[6], "a6"));
	bi_decl(bi_1pin_with_name(ADDRESS[7], "a7"));
	bi_decl(bi_1pin_with_name(ADDRESS[8], "a8"));
	bi_decl(bi_1pin_with_name(ADDRESS[9], "a9"));
	bi_decl(bi_1pin_with_name(ADDRESS[10], "a10"));
	bi_decl(bi_1pin_with_name(ADDRESS[11], "a11"));
	bi_decl(bi_1pin_with_name(ADDRESS[12], "a12"));
	bi_decl(bi_1pin_with_name(ADDRESS[13], "a13"));
	bi_decl(bi_1pin_with_name(ADDRESS[14], "a14"));
   bi_decl(bi_1pin_with_name(DATA[0], "d0"));
	bi_decl(bi_1pin_with_name(DATA[1], "d1"));
	bi_decl(bi_1pin_with_name(DATA[2], "d2"));
	bi_decl(bi_1pin_with_name(DATA[3], "d3"));
	bi_decl(bi_1pin_with_name(DATA[4], "d4"));
	bi_decl(bi_1pin_with_name(DATA[5], "d5"));
	bi_decl(bi_1pin_with_name(DATA[6], "d6"));
	bi_decl(bi_1pin_with_name(DATA[7], "d7"));
	bi_decl(bi_1pin_with_name(TXS_OE, "Level shifter Output Enable (out)"));
	bi_decl(bi_1pin_with_name(LED_BUILTIN, "On-board LED"));
	bi_decl(bi_1pin_with_name(OE, "Output Enable"));
	bi_decl(bi_1pin_with_name(CE, "Chip Enable"));
}
