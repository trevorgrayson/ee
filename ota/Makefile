package:
	docker build . -t tgrayson/ota

serve:
	python3 -s -m server

test:
	python3 -m pytest tests

clean:
	find . -name *.pyc -delete

.PHONY: server
