# Config just variables
CC=gcc
CFLAGS=-Wall -g
LFLAGS=-lm
TARGET=out
# variables tha auto detect source .c files
C_SRCS := \
	$(wildcard *.c) \
	$(wildcard src/*.c) \
	$(wildcard src/**/*.c)
	# variables tha auto detect source .h files
HDRS := \
	$(wildcard *.h) \
	$(wildcard src/*.h) \
	$(wildcard src/**/*.h)
# add comments
OBJS := $(patsubst %.c, bin/%.o, $(wildcard *.c))
OBJS += $(filter %.o, $(patsubst src/%.c, bin/%.o, $(C_SRCS)))
# defult target
all: build
	@echo "All Done"
# Links all built targets
build: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)
# Catch root directory files
bin/%.o: %.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
# catch all nested directory files
bin/%.o: src/%.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
# cleans prevoius builds
clean:
	rm -f $(TARGET)
	rm -rf bin
#runs the targeted code with command args
run: build
	./$(TARGET) output.txt
# target used to debug to detect location of source files
which:
	@echo "FOUND SOURCES: ${C_SRCS}"
	@echo "FOUND HEADERS: ${HDRS}"
	@echo "TARGET OBJS: ${OBJS}"
