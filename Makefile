PYTHON?=python3
VENV?=venv
PROJECT?=projects/espwatch
PIO?=$(PYTHON) -m platformio

export PYTHONPATH = .:$(VENV)

run: compile
	$(PIO) run -d $(PROJECT)

upload: 
	$(PIO) run -d $(PROJECT) --target upload

requirements.txt:
	touch requirements.txt

compile: $(VENV)
$(VENV): requirements.txt
	mkdir -p $(VENV)
	$(PYTHON) -m pip -V || curl https://bootstrap.pypa.io/get-pip.py | $(PYTHON)
	$(PYTHON) -m pip install -q -t $(VENV) -r requirements.txt
	touch $(VENV)

clean:
	find . -name "*.pyc" -delete
	rm -rf `find . -name __pycache__`
	rm -rf $(VENV)

.PHONY: test
