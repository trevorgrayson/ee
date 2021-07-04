PORT?=/dev/cu.SLAB_USBtoUART
BOARD?=esp32:esp32:ttgo-t1
# ARTIFACT?=build/esp32.esp32.esp32/deskdevice.ino.bin
ACLI=arduino-cli

publish: compile
	$(ACLI) upload -p $(PORT) --fqbn $(BOARD)
	# esptool.py --port $(PORT) write_flash -e 0x1000 $(ARTIFACT)

compile:
	$(ACLI) compile --fqbn $(BOARD)
