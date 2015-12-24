.PHONY: all test

CC         = gcc
CFLAGS     = -c -Wall -I. -I..
LDFLAGS    =
SOURCES    = test.c testMath.c ../math.c
OBJECTS    = $(addprefix build/test/,$(SOURCES:.c=.o))
EXECUTABLE = build/utils-test

all: $(SOURCES) $(EXECUTABLE)

test: all
	./build/utils-test

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

build/test/%.o: %.c
	@mkdir -p build/test
	$(CC) $(CFLAGS) $< -o $@
