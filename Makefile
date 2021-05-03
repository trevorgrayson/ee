CFLAGS = -Wall

# Should be equivalent to your list of C files, if you don't build selectively
ALL= workflow.c
SRC=$(wildcard noarch/*.c) $(ALL)
TEST_SRC=test.c $(wildcard tests/impls/*.c) $(ALL)

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
