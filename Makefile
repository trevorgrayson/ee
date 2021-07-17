CFLAGS = -Wall

# Should be equivalent to your list of C files, if you don't build selectively
ALL= workflow.c
SRC=$(wildcard noarch/*.c) $(ALL)
TEST_SRC=test.c $(wildcard tests/impls/*.c) $(ALL)

ACLI=arduino-cli
BOARD?=esp32:esp32:ttgo-t1
# BOARD?=Heltec-esp8266:esp8266:generic
# BOARD=arduino:avr:leonardo
BOARD_ARTIFACT?=$(shell sed s/:/./g <<< $(BOARD))
PORT?=/dev/cu.SLAB_USBtoUART
BIN_MOD?="" # with_bootloader.

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

build/$(BOARD_ARTIFACT)/$(PROJECT).ino.$(BIN_MOD)bin:$(wildcard projects/$(PROJECT)/*)
	@echo "$(BOARD) $(BOARD_ARTIFACT) $(PROJECT)"
	$(ACLI) compile --fqbn $(BOARD) --output-dir build/$(BOARD_ARTIFACT)/ \
        projects/$(PROJECT)/

compile: build/$(BOARD_ARTIFACT)/$(PROJECT).ino.$(BIN_MOD)bin

publish: compile
	$(ACLI) upload -p $(PORT) --fqbn $(BOARD) -i build/$(BOARD_ARTIFACT)/$(PROJECT).ino.$(BIN_MOD)bin
