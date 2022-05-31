CFLAGS = -Wall

# Should be equivalent to your list of C files, if you don't build selectively
ALL= workflow.c
SRC=$(wildcard noarch/*.c) $(ALL)
TEST_SRC=test.c $(wildcard tests/impls/*.c) $(ALL)

ACLI=arduino-cli
# BOARD?=esp32:esp32:ttgo-t1
# BOARD?=esp32:esp32:esp32:PSRAM=enabled
BOARD?=esp8266:esp8266:generic
# BOARD=arduino:avr:leonardo
BOARD_ARTIFACT?=$(shell sed s/:/./g <<< $(BOARD))
PORT?=/dev/cu.SLAB_USBtoUART
BIN_MOD?= # with_bootloader.
BIN_DIR?=ota/binaries
OTAHOST?=ota.pearl.st

INOS := $(wildcard projects/*)

export C_INCLUDE_PATH=../../creds/

buildlibs:
	gcc -c libs/constants/pins.h -o build/pins.o
	

test: $(TEST_SRC)
	@mkdir -p target
	gcc -o target/$@ $^ $(CFLAGS)
	./target/test

esp8266.out: $(SRC)
	@mkdir -p target
	# arduino-cli ...
	gcc -o $@ $^ $(CFLAGS)

clean: 
	rm -f test 
	rm -rf target
	rm -rf build

boards:
	$(ACLI) board list

all: $(INOS)
	for file in $^ ; do \
		echo "compiling" $${file}; \
		$(ACLI) compile --fqbn $(BOARD) --output-dir build/$(BOARD_ARTIFACT)/ $${file}; \
		touch $${file}; \
	done

babycam: $(wildcard projects/dropcam/*)
	$(ACLI) compile --fqbn $(BOARD) --output-dir build/dropcam/ projects/dropcam
	
build/$(BOARD_ARTIFACT)/$(PROJECT).ino.$(BIN_MOD)bin:$(wildcard projects/$(PROJECT)/*)
	@echo "$(BOARD) $(BOARD_ARTIFACT) $(PROJECT)"
	$(ACLI) compile --fqbn $(BOARD) --libraries /Users/trevorgrayson/Library/Arduino15/packages/esp32/hardware/esp32/1.0.6/libraries/WiFi/src --libraries creds --libraries libs/constants,libs,creds --output-dir build/$(BOARD_ARTIFACT)/ \
        projects/$(PROJECT)/

compile: build/$(BOARD_ARTIFACT)/$(PROJECT).ino.$(BIN_MOD)bin

publish: compile
	$(ACLI) upload -p $(PORT) --fqbn $(BOARD) -i build/$(BOARD_ARTIFACT)/$(PROJECT).ino.$(BIN_MOD)bin

deskdisplay:
	# BOARD?=esp32:esp32:esp32:PSRAM=enabled
	$(ACLI) compile --fqbn esp32:esp32:esp32:PSRAM=enabled --libraries creds --libraries libs/constants,libs,creds --output-dir build/deskdisplay/ \
        projects/deskdisplay/
	# $(ACLI) upload -p $(PORT) --fqbn esp32:esp32:esp32:PSRAM=enabled -i build/$(BOARD_ARTIFACT)/$(PROJECT).ino.$(BIN_MOD)bin

	
publishOTA: compile
	echo "copying to `binaries`"
	cp build/Heltec-esp8266.esp8266.generic/ota.ino.bin $(BIN_DIR)/a0:20:a6:27:0b:b2.bin
	# curl --data-binary @build/esp8266.esp8266.generic/ota.ino.bin  $(OTAHOST)/things/update/A0:20:A6:27:0B:B2
	curl --data-binary @build/Heltec-esp8266.esp8266.generic/ota.ino.bin  $(OTAHOST)/things/update/A0:20:A6:27:0B:B2

publishTest:
	curl -H 'X-Esp8266-Sketch-Md5: 242e80f46cc5c1f73bc4cf52cfc1e07f' -H 'X-Esp8266-Sta-Mac: A0:20:A6:27:0B:B2'  $(OTAHOST)/things/update

monitor:
	@echo "Ctrl a, Ctrl \ to disconnect"
	screen $(PORT) $(BAUD)

clean:
	find . -name '*.o' -delete
	find images -name '*.xbm' -delete
	rm -rf build
