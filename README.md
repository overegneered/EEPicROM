# EEPicROM
A Raspberry-Pi-Pico-based 32k AT28C256 EEPROM emulator, intended for a 6502 CPU running at 1 MHz.

> Note that EEPicROM has not yet been tested by an MPU, but initial benchmarking indicates that its main loop runs at
> 7.7 MHz, and should therefore easily be able to handle an MPU at 1 MHz.


# Schematic
![Schematic](/assets/schematic.png)


# Usage
First, you need to actually build it, both hardware and software.

## Loading a new ROM
- Write the ROM to the EEPicROM source using the `writer.py` script like so: `python3 /src/writer.py <rom-file>`. This will also attempt to rebuild the project, and expects build files to be under `/src/build/`
- Plug the Pico in (if hasn't been already) and hold down the external button. Then, depress the BOOTSEL button on the Pico and release the external button, and then release the BOOTSEL button.
- Copy the `/src/build/EEPicROM.uf2` file over to the Pico, which should've mounted itself as a mass storage device called `RPI-RP2` as a result of the above step.

## A few notes
- EEPicROM is designed to work both with the Pico drawing power from a connected USB cable or +5V from the circuit it is connected to, and can handle the USB being plugged/unplugged when also receiving power from 5V.
- The on-board LED is switched with the output enable signal to the level shifters - that is, when the LED is illuminated, EEPicROM is enabled, and vice versa.

# EEPicROM in action (sorta)
![EEPicROM](/assets/EEPicROM_basic_setup.png)