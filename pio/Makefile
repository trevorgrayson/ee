PYTHON?=python3
PIO?=~/.platformio/penv/bin/platformio

get-platformio.py: 	
	curl -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
	$(PYTHON) get-platformio.py

core:
	$(PIO) check core

ports:
	 pio device list
