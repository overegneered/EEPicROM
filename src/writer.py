#!/usr/bin/python3
import sys
import subprocess
from typing import List


def main(argv: List[str]) -> None:
    if len(argv) == 0:
        print("No binary file passed for flashing. Please supply one after the program name: writer.py <binary-file>")
        return

    print(f"Writing binary from {argv[0]} to ROM.txt... ", end="")
    rom = bytearray(0x8000)
    with open(argv[0], "rb") as rom_file:
        rom_section = bytearray(rom_file.read())
        rom[:len(rom_section)] = rom_section

    to_write = ""
    for i in range(0x800):
        hex_line = rom[i*0x10:i*0x10+0x10]
        line = ""
        for byte in hex_line:
            line += f"0x{byte:02x}, "
        to_write += line + '\n'

    with open("ROM.txt", 'w') as f:
        # cut the last 3 characters off - the final space, comma and newline
        f.write(to_write[:-3])

    print("done.")

    print("Building new UF2... ", end="")
    out = subprocess.run(["make", "-C", "build"], capture_output=True)
    if out.returncode == 0:
        print("done.")
    else:
        print("failed.\nMake error - please rerun make for details.")


if __name__ == '__main__':
    main(sys.argv[1:])