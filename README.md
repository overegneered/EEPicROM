# EEPicROM
A Raspberry-Pi-Pico-based 32k AT28C256 EEPROM emulator, intended for a 6502 CPU running at 1 MHz.

![EEPicROM](/assets/EEPicROM_basic_setup.png)

> Note that EEPicROM has not yet been tested by an MPU, but initial benchmarking indicates that its main loop runs at 
> 7.7 MHz, and should therefore easily be able to handle an MPU at 1 MHz.

The schematic is as below:

![Schematic](/assets/schematic.png)